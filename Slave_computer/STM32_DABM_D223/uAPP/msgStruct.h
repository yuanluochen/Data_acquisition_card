#ifndef __MSGSTRUCT_H_
#define __MSGSTRUCT_H_

#include "main.h"

/*
 * 简易上下位机二进制协议
 * ----------------------------------------------------------
 * 帧格式:
 *   [0] 0xAA        帧头1
 *   [1] 0x55        帧头2
 *   [2] cmd         命令字
 *   [3] len         负载长度(字节)
 *   [4..4+len-1]    payload 负载
 *   [4+len]         crc 高字节 (CRC16, 与 crc16.c 的 getCrc16WithTail 一致)
 *   [5+len]         crc 低字节
 *   注: CRC 覆盖 [0 .. 3+len] 全部字节
 * ----------------------------------------------------------
 * 上行 (STM32 -> 上位机):
 *   cmd = 0x01 (ADC_DATA)
 *   payload = 8 路 ADC 原始值, 每路 2 字节小端 (s16)
 * ----------------------------------------------------------
 * 下行 (上位机 -> STM32):
 *   cmd = 0x02 (DAC_SET)
 *   payload = 4 路 DAC 设定电压, 每路 2 字节小端 (u16, 单位 mV, 0~5000)
 */

#define SIMPLE_MSG_HEAD0 0xAAu
#define SIMPLE_MSG_HEAD1 0x55u

#define SIMPLE_CMD_START 0x00u    /* 下行: 开始上传 (STM32 收到任意帧即进入上传状态) */
#define SIMPLE_CMD_ADC_DATA 0x01u /* 上行: 8 路 ADC 原始值 */
#define SIMPLE_CMD_DAC_SET 0x02u  /* 下行: 4 路 DAC 设定电压 */

#define SIMPLE_ADC_CH_NUM 8u
#define SIMPLE_DAC_CH_NUM 4u

#define SIMPLE_MSG_CRC_LEN 2u /* 帧尾 CRC16 字节数 */

/* 处理一帧收到的数据 */
void fun_msgProcess_task(u8 *data, u16 len);

/* 把当前 8 路 ADC 原始值发送给上位机 */
void fun_sendAdcData(void);

/* 解析 USB 接收缓冲中的全部帧 */
void fun_msgParseRxBuf(u8 *buf, u16 len);

#endif
