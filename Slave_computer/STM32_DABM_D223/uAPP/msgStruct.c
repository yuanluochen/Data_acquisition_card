#include "main.h"
#include "msgStruct.h"

/*
 * 简易协议实现, 只保留两条命令:
 *   上行 ADC_DATA : STM32 -> 上位机, 8 路 ADC 原始值
 *   下行 DAC_SET  : 上位机 -> STM32, 4 路 DAC 设定电压(mV)
 */

/* 把当前 8 路 ADC 原始值发送给上位机 */
void fun_sendAdcData(void)
{
  u8 frame[4 + SIMPLE_ADC_CH_NUM * 2 + SIMPLE_MSG_CRC_LEN];

  frame[0] = SIMPLE_MSG_HEAD0;
  frame[1] = SIMPLE_MSG_HEAD1;
  frame[2] = SIMPLE_CMD_ADC_DATA;
  frame[3] = SIMPLE_ADC_CH_NUM * 2;

  for (u8 i = 0; i < SIMPLE_ADC_CH_NUM; i++)
  {
    s16 v = _uadc.adc[i];
    frame[4 + i * 2] = (u8)(v & 0xFF);
    frame[4 + i * 2 + 1] = (u8)((v >> 8) & 0xFF);
  }

  u16 crc = getCrc16WithTail(frame, sizeof(frame));
  frame[sizeof(frame) - 2] = (u8)(crc >> 8);
  frame[sizeof(frame) - 1] = (u8)(crc & 0xFF);

  usb_sendMsg(frame, sizeof(frame));
}

/* 设置 4 路 DAC 电压输出, 复用 ddsDac 的直流输出模式 */
static void simple_setDac(u8 *payload)
{
  for (u8 i = 0; i < SIMPLE_DAC_CH_NUM; i++)
  {
    u16 mv = (u16)payload[i * 2] | ((u16)payload[i * 2 + 1] << 8);
    if (mv > 5000)
      mv = 5000;

    _framDatas._ddsDacParam[i].volt = mv;           /* 设定电压(mV) */
    _ddsDac.ddsDacWorkMode[i] = _ddsDacWorkMode_Dc; /* 直流输出 */
  }
}

/* 处理一帧收到的数据 */
void fun_msgProcess_task(u8 *data, u16 len)
{
  if (len < 4 + SIMPLE_MSG_CRC_LEN)
    return;
  if (data[0] != SIMPLE_MSG_HEAD0 || data[1] != SIMPLE_MSG_HEAD1)
    return;

  u8 cmd = data[2];
  u8 plen = data[3];
  if ((u16)(4 + plen + SIMPLE_MSG_CRC_LEN) != len)
    return;
  if (!checkCrc16WithTail(data, len))
    return;

  switch (cmd)
  {
  case SIMPLE_CMD_START:
    /* USB 工作标志已由 usbMsg 线程置位, 无需额外处理 */
    break;

  case SIMPLE_CMD_DAC_SET:
    if (plen >= SIMPLE_DAC_CH_NUM * 2)
      simple_setDac(&data[4]);
    break;

  default:
    break;
  }

  HAL_GPIO_TogglePin(LED_USB_GPIO_Port, LED_USB_Pin);
}

/* 解析接收缓冲中的全部帧 */
void fun_msgParseRxBuf(u8 *buf, u16 len)
{
  u16 idx = 0;

  while ((u16)(idx + 4 + SIMPLE_MSG_CRC_LEN) <= len)
  {
    if (buf[idx] == SIMPLE_MSG_HEAD0 && buf[idx + 1] == SIMPLE_MSG_HEAD1)
    {
      u8 plen = buf[idx + 3];
      u16 frameLen = 4 + plen + SIMPLE_MSG_CRC_LEN;
      if ((u16)idx + frameLen > len)
        break; /* 半帧, 等待后续数据 */

      fun_msgProcess_task(&buf[idx], frameLen);
      idx += frameLen;
    }
    else
    {
      idx++;
    }
  }
}
