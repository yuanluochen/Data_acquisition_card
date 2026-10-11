#include "main.h"

/*
 * 简易采集实现:
 *   - ADC 的读取在 TIM13 中断 (qspiAdcTimTask) 里完成, 结果放在 _uadc.adc[]
 *   - 这里只负责把最新数据周期性推送给上位机
 */

/* 系统时基任务 (TIM12) */
void adcFunction_tim_task(void)
{
  /* 简易版本无需处理 */
}

/* 采集线程 */
void adcFunction_thread(void)
{
  /* USB 未连接时不发送 */
  if (_usbMsg.usbWorkFlag == 0)
    return;

  fun_sendAdcData();

  rt_thread_delay(1);
}
