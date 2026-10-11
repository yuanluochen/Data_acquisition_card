#ifndef SERIAL_IO_H
#define SERIAL_IO_H

#include <cstdint>

/*
 * STM32 简易协议 (与固件 msgStruct.h 一致)
 * 帧格式: AA 55 | cmd | len | payload | crcH crcL
 *   CRC16 (与固件 crc16.c 一致), 覆盖 AA 55 cmd len payload, 大端附加
 */

#define MSG_HEAD0 0xAA
#define MSG_HEAD1 0x55

#define MSG_CMD_START 0x00    /* 下行: 开始上传 */
#define MSG_CMD_ADC_DATA 0x01 /* 上行: 8 路 ADC 原始值 (8 x int16 小端) */
#define MSG_CMD_DAC_SET 0x02  /* 下行: 4 路 DAC 电压 (4 x uint16 小端, mV) */

/* 串口 */
bool serialOpen(const char *port, unsigned baud = 115200);
void serialClose(void);

/* 发送一帧 (自动附加 CRC16) */
bool serialSend(uint8_t cmd, const uint8_t *payload = nullptr, uint8_t len = 0);

/* 接收一帧 (已通过 CRC 校验), 阻塞至多 timeoutMs (<0 表示一直阻塞)
 * 返回: 1=收到一帧, 0=超时, -1=串口错误
 * payload 缓冲建议 >=255 字节; 传 nullptr 则不拷贝负载 */
int serialRecv(uint8_t *cmd, uint8_t *payload, uint8_t *len, int timeoutMs = 1000);

void dac_set_val(uint16_t mv[4]);

#endif /* SERIAL_IO_H */
