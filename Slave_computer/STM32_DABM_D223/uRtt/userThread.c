#include "main.h"

////************************//////////
////************************//////////
////************************//////////
////************************//////////

void adcFunc_task_entry(void *parameter)
{
	while(1)
	{
		adcFunction_thread();
		rt_thread_delay(1);
	}
}

//初始化线程函数
void rt_adcFunc_init(void)
{
	rt_thread_t adcFunc_thread = RT_NULL;
	adcFunc_thread  = rt_thread_create(
	"adcFunc",
	adcFunc_task_entry,
	RT_NULL,
	2000,
	0,
	100);
	
	if(adcFunc_thread != RT_NULL)
	{
		//开启线程调度
		rt_thread_startup(adcFunc_thread);
	}							
}

////************************//////////
////************************//////////
////************************//////////
////************************//////////

void msgProcess_task_entry(void *parameter)
{

		while(1)
		{
			usbMsg_thread_task();

			rt_thread_delay(2);
		}
}


//初始化线程函数
void rt_msgProcess_init(void)
{
	rt_thread_t msgProcess_thread = RT_NULL;
	rt_thread_delay(10);
	msgProcess_thread  = rt_thread_create(
	"msgProcess",
	msgProcess_task_entry,
	RT_NULL,
	2000,
	1,
	100);
	
	if(msgProcess_thread != RT_NULL)
	{
		//开启线程调度
		rt_thread_startup(msgProcess_thread);
		
	}
									
}
