// host_cpp/main.cpp
// ---------------------------------------------------------------------------
// STM32 简易协议的串口收发函数 (只有收发, 无其它逻辑)
//   帧格式: AA 55 | cmd | len | payload | crcH crcL
//   CRC16 与 STM32 固件 crc16.c 的 getCrc16WithTail 完全一致
//   用法: #include "serial_io.h", 在你自己的 main 里调用即可
// ---------------------------------------------------------------------------

#include "serial_io_dabm.h"

#include <windows.h>

#include <cstring>
#include <string>



static HANDLE g_hCom = INVALID_HANDLE_VALUE;

// ---------------- CRC16 (与固件 crc16.c 一致) ----------------
static uint8_t s_tableH[256];
static uint8_t s_tableL[256];

static void crcInit(void)
{
  for (int i = 0; i < 256; ++i)
  {
    uint16_t c = (uint16_t)i;
    for (int j = 0; j < 8; ++j)
      c = (c & 1) ? (uint16_t)((c >> 1) ^ 0xA001) : (uint16_t)(c >> 1);

    s_tableH[i] = (uint8_t)(c & 0xFF); // 固件 tableH = 标准表低字节
    s_tableL[i] = (uint8_t)(c >> 8);   // 固件 tableL = 标准表高字节
  }
}

static uint16_t crc16(const uint8_t *msg, size_t len)
{
  static bool inited = false;
  if (!inited)
  {
    crcInit();
    inited = true;
  }

  uint8_t crcL = 0xFF, crcH = 0xFF;
  while (len--)
  {
    uint8_t idx = (uint8_t)(crcH ^ *msg++);
    crcH = (uint8_t)(crcL ^ s_tableH[idx]);
    crcL = (uint8_t)(s_tableL[idx]);
  }
  return (uint16_t)((crcH << 8) | crcL);
}

// ---------------- 打开 / 关闭 ----------------
bool serialOpen(const char *port, unsigned baud)
{
  std::string path = std::string("\\\\.\\") + port; // 支持 COM10 及以上
  g_hCom = CreateFileA(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr,
                       OPEN_EXISTING, 0, nullptr);
  if (g_hCom == INVALID_HANDLE_VALUE)
    return false;

  DCB dcb{};
  dcb.DCBlength = sizeof(DCB);
  if (!GetCommState(g_hCom, &dcb))
    return false;
  dcb.BaudRate = baud; // USB CDC 下波特率无实际意义
  dcb.ByteSize = 8;
  dcb.Parity = NOPARITY;
  dcb.StopBits = ONESTOPBIT;
  dcb.fBinary = TRUE;
  dcb.fDtrControl = DTR_CONTROL_ENABLE;
  dcb.fRtsControl = RTS_CONTROL_ENABLE;
  if (!SetCommState(g_hCom, &dcb))
    return false;

  COMMTIMEOUTS to{};
  to.ReadIntervalTimeout = 20;
  to.ReadTotalTimeoutConstant = 50;
  to.ReadTotalTimeoutMultiplier = 0;
  to.WriteTotalTimeoutConstant = 1000;
  SetCommTimeouts(g_hCom, &to);

  SetupComm(g_hCom, 4096, 4096);
  PurgeComm(g_hCom, PURGE_RXCLEAR | PURGE_TXCLEAR);
  return true;
}

void serialClose(void)
{
  if (g_hCom != INVALID_HANDLE_VALUE)
  {
    CloseHandle(g_hCom);
    g_hCom = INVALID_HANDLE_VALUE;
  }
}

// ---------------- 发送 -----------------
bool serialSend(uint8_t cmd, const uint8_t *payload, uint8_t len)
{
  if (g_hCom == INVALID_HANDLE_VALUE)
    return false;

  uint8_t buf[4 + 255 + 2];
  size_t n = 4 + len;

  buf[0] = MSG_HEAD0;
  buf[1] = MSG_HEAD1;
  buf[2] = cmd;
  buf[3] = len;
  if (len && payload)
    memcpy(buf + 4, payload, len);

  uint16_t crc = crc16(buf, n);
  buf[n] = (uint8_t)(crc >> 8);
  buf[n + 1] = (uint8_t)(crc & 0xFF);

  DWORD written = 0;
  return WriteFile(g_hCom, buf, (DWORD)(n + 2), &written, nullptr) &&
         written == (DWORD)(n + 2);
}

// ---------------- 接收 -----------------
int serialRecv(uint8_t *cmd, uint8_t *payload, uint8_t *len, int timeoutMs)
{
  if (g_hCom == INVALID_HANDLE_VALUE)
    return -1;

  static uint8_t buf[2048];
  static size_t bufLen = 0;

  // 从缓冲里找一帧完整且 CRC 正确的报文
  auto parse = [&](void) -> bool
  {
    size_t skip = 0;
    while (bufLen >= 6 && skip + 6 <= bufLen)
    {
      if (buf[skip] == MSG_HEAD0 && buf[skip + 1] == MSG_HEAD1)
      {
        uint8_t plen = buf[skip + 3];
        size_t frameLen = 4u + plen + 2u;
        if (skip + frameLen > bufLen)
          return false; // 半帧, 等后续数据

        uint16_t crc = (uint16_t)((buf[skip + frameLen - 2] << 8) | buf[skip + frameLen - 1]);
        if (crc == crc16(&buf[skip], frameLen - 2))
        {
          if (cmd)
            *cmd = buf[skip + 2];
          if (len)
            *len = plen;
          if (plen && payload)
            memcpy(payload, &buf[skip + 4], plen);

          memmove(buf, buf + skip + frameLen, bufLen - (skip + frameLen));
          bufLen -= (skip + frameLen);
          return true;
        }
        skip++; // CRC 错, 继续往后找
      }
      else
      {
        skip++;
      }
    }

    if (skip > 0) // 丢掉已扫描的无效字节
    {
      memmove(buf, buf + skip, bufLen - skip);
      bufLen -= skip;
    }
    return false;
  };

  if (parse())
    return 1; // 残留数据里已有完整帧

  DWORD start = GetTickCount();
  for (;;)
  {
    if (bufLen < sizeof(buf))
    {
      DWORD n = 0;
      if (ReadFile(g_hCom, buf + bufLen, (DWORD)(sizeof(buf) - bufLen), &n, nullptr) && n > 0)
        bufLen += n;
    }

    if (parse())
      return 1;

    if (timeoutMs >= 0 && (int)(GetTickCount() - start) >= timeoutMs)
      return 0;

    Sleep(1);
  }
}
/**
 * dac 设定函数
 * mv 单位mv 范围0~5000
 */
void dac_set_val(uint16_t mv[4]){
  
  uint8_t dac[8];
  for (int i = 0; i < 4; ++i)
  {
    //限幅
    if (mv[i] < 0){
      mv[i] = 0;
    }
    if (mv[i] > 5000){
      mv[i] = 5000;
    }
    //数值设定
    dac[i * 2] = mv[i] & 0xFF;
    dac[i * 2 + 1] = mv[i] >> 8;
  }
  serialSend(MSG_CMD_DAC_SET, dac, 8);
}