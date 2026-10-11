# DABM-D223 简易采集版 (STM32 + FPGA)

把原来功能繁杂的数据采集卡固件精简成一套最小可用的“采集 + 串口收发”流程：

- **STM32** 从 FPGA 连续读取 **8 路 ADC 原始值**，通过 USB 虚拟串口发给上位机；
- **上位机** 只需下发 **4 路 DAC 设定电压(mV)**，STM32 立即输出对应的直流电压；
- 上下位机使用一个**极简二进制帧**协议，不再有 cmdId 表、CRC、记录仪、示波器、标定等逻辑。

## 数据流

```
        QSPI cmd 0x80 (17B, 8ch x s16 + DIN)
AD7606 ──► FPGA ────────────────────────────────► STM32 (TIM13, 1kHz)
                                                     │
                                      USB CDC 虚拟串口 (AA 55 01 10 + 16B)
                                                     ▼
                                                  上位机
                                                     │
                                     USB CDC (AA 55 02 08 + 8B)
                                                     ▼
FPGA DAC ◄── SPI2 ── STM32 (TIM14, 直流输出)
```

## 通信协议

帧格式：

```
AA 55 | cmd | len | payload... | crcH crcL
```

> `crcH crcL`：CRC16（复用固件 `crc16.c` 的 `getCrc16WithTail`），
> 覆盖 `AA 55 cmd len payload` 全部字节，**大端**附加；收帧侧用 `checkCrc16WithTail` 校验。

| 方向           | cmd    | 名称     | payload                                                      |
| -------------- | ------ | -------- | ------------------------------------------------------------ |
| STM32 → 上位机 | `0x01` | ADC_DATA | 8 × int16 小端 (8 路 ADC 原始值)                             |
| 上位机 → STM32 | `0x02` | DAC_SET  | 4 × uint16 小端 (DAC 电压 mV, 0~5000)                        |
| 上位机 → STM32 | `0x00` | START    | 空 (通知 STM32 开始上传 ADC；STM32 收到任意帧即置位上传标志) |

> STM32 在收到上位机任意数据之前不会上传（`_usbMsg.usbWorkFlag` 机制），
> 所以上位机连接后先发一帧 `START` 即可开始接收 ADC 数据。

## 关键文件改动

| 文件                    | 说明                                                            |
| ----------------------- | --------------------------------------------------------------- |
| `uAPP/msgStruct.h/.c`   | **重写**：只保留简易协议定义、下发 DAC、上传 ADC、收包解析      |
| `uAPP/adcFunction.h/.c` | **重写**：采集线程周期性调用 `fun_sendAdcData()` 上传 ADC       |
| `uAPP/usbMsg.c`         | 收包改为调用 `fun_msgParseRxBuf()` 按帧解析                     |
| `uDRV/userQspiAdc.h/.c` | **重写**：TIM13 里用 `QSPI_ReadDatas_DMA(0x80,...)` 读 8 路 ADC |
| `uDRV/regFPGA.c`        | 删除对已移除的 `_adcFunctionParam.sramBufCnt` 的引用            |
| `Core/Src/main.c`       | 启动时把 FPGA 配置为 **FIFO 实时读取模式**（workMode=3）        |
| `_backup_original/`     | 被重写文件的原始版本（保留备查，不参与编译）                    |

未改动的部分（保持不变，仍参与编译）：

- 外设初始化：`main.c`、CubeMX 生成的 `Core/` 代码；
- 驱动：`userQspi.c/h`、`userSpi.c/h`、`regFPGA.c`（SPI 寄存器读写）、`usbMsg.c`（USB CDC 收发）、`USB_DEVICE/`；
- DAC 输出：`ddsDAC.c/h`（复用其“直流输出”模式，`_ddsDacWorkMode_Dc`）；
- `dio.c`、`nvmData.c`(FRAM)、`fram.c`、`crc16.c`：保留；其中 `crc16.c` 重新被协议用于帧校验（`getCrc16WithTail` / `checkCrc16WithTail`）。

## 注意事项

1. **FPGA 必须以 FIFO 读模式工作**：`main.c` 启动时写入寄存器
   `REG_A2F_SRAM_WORK_MODE = 3`、通道使能 `0xFF`、采样周期等，使 FPGA 的
   `reg_adcBuf` 持续更新，STM32 才能通过 QSPI cmd `0x80` 读到最新 8 路 ADC。
2. **ADC 读取时基** 固定为 1kHz（`adc_dac_paramCalcThread()`，TIM13）。
3. **DAC 输出** 复用 DDS 的直流模式：设置 `_framDatas._ddsDacParam[ch].volt`
   (mV) 并把 `_ddsDac.ddsDacWorkMode[ch]` 设为 `_ddsDacWorkMode_Dc`；
   实际电压由 TIM14 (`ddsDac_tim_task`) 输出。
4. DAC 通道编号与上位机 payload 顺序一一对应（0~3）。

## 上位机

见 `../../host_cpp/`（C++ 简易串口程序，Windows）：

```bat
cd host_cpp
g++ -std=c++17 -O2 main.cpp -o host.exe
host.exe COM5 set 1000 2000 3000 4000   :: 一次性下发 4 路 DAC
host.exe COM5                            :: 监控模式, 打印 ADC 并可随时下发
```
