# 上位机收发函数 (C++)

只提供串口**收发函数**，无命令行/逻辑，供你自己的上位机工程调用。

## 帧协议（与 STM32 `msgStruct.h` 一致）

```
AA 55 | cmd | len | payload... | crcH crcL
```

- `crcH crcL`：CRC16（与固件 `crc16.c` 的 `getCrc16WithTail` 一致），
  覆盖 `AA 55 cmd len payload` 全部字节，**大端**附加。

| 方向           | cmd    | 含义     | payload                      |
| -------------- | ------ | -------- | ---------------------------- |
| 上位机 → STM32 | `0x00` | START    | 空（先发它才会开始上传 ADC） |
| STM32 → 上位机 | `0x01` | ADC 数据 | 8 × int16 小端               |
| 上位机 → STM32 | `0x02` | DAC 设定 | 4 × uint16 小端 (mV, 0~5000) |

## 接口（`serial_io_dabm.h`）

```cpp
bool serialOpen(const char *port, unsigned baud = 115200);
void serialClose(void);

// 发送一帧, 自动加 CRC
bool serialSend(uint8_t cmd, const uint8_t *payload = nullptr, uint8_t len = 0);

// 接收一帧(已校验 CRC), 阻塞至多 timeoutMs(<0 一直等)
// 返回 1=收到一帧, 0=超时, -1=串口错误
int  serialRecv(uint8_t *cmd, uint8_t *payload, uint8_t *len, int timeoutMs = 1000);
```

## 用法示例

```cpp
#include "serial_io_dabm.h"
#include <iostream>
// AD7606 16 位双极性, 二进制补码: 0x0000 对应 0V
// RANGE = 0 -> ±5V (固件 AD_RANGE 默认),  RANGE = 1 -> ±10V

static constexpr double kAdcRangeVolt = 10.0; // ±10V (RANGE=1); 若硬件是 ±5V 改成 5.0
static constexpr int kAdcChNum = 8;

static inline double adcCodeToVolt(int16_t code)
{
  return (double)code * kAdcRangeVolt / 32768.0;
}
int main()
{
  if (!serialOpen("COM5"))
    return -1;

  serialSend(MSG_CMD_START); // 通知 STM32 开始上传
  double adc[8];
  // 下发 4 路 DAC: 1000 2000 3000 4000 mV
  uint8_t dac[8];
  uint16_t mv[4] = {1234, 2345, 3567, 4789};
  while (1){

    for (int i = 0; i < 4; ++i)
    {
      dac[i * 2] = mv[i] & 0xFF;
      dac[i * 2 + 1] = mv[i] >> 8;
    }
    serialSend(MSG_CMD_DAC_SET, dac, 8);

    // 收 ADC
    uint8_t cmd, len, pl[255];
    while (serialRecv(&cmd, pl, &len, 1000) == 1)
    {
      if (cmd == MSG_CMD_ADC_DATA && len >= 16)
      {
        for (int i = 0; i < 8; ++i){
          int16_t code = (int16_t)((uint16_t)pl[i * 2] | ((uint16_t)pl[i * 2 + 1] << 8));
          adc[i] = adcCodeToVolt(code);
        }
          
        for (int i = 0; i < 8; i++){
          std::cout << "id" << i << "=" << adc[i] << std::endl;
        }
      }
      
      
    }
  }
  

  serialClose();
  return 0;
}

```

## 编译

直接用源文件（含你自己的 main）：

```bat
g++ -std=c++17 -O2 your_main.cpp serial_io_dabm.cpp -o host.exe
```

或 CMake 生成静态库 `serial_io_dabm` 后链接（`target_link_libraries(your_app PRIVATE serial_io_dabm)`）。
