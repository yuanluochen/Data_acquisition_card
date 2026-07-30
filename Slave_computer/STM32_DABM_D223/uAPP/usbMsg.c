#include "main.h"

#pragma pack(1)
usbMsg _usbMsg;

void usbMsg_timer_task()
{
		if(_usbMsg.usbRxMsgProcessFlag == usbFlag_busy)
		{
			_usbMsg.usbRxFinishTick++;
		}
 }


void usbMsg_thread_task()
{
	if(_usbMsg.usbRxFinishTick > 1)
	{	
			_usbMsg.usbWorkFlag = 1;
			fun_msgProcess_task(_usbMsg.usbRxBuf);

			_usbMsg.usbRxIndex = 0;			//接收缓冲区索引清零
			_usbMsg.usbRxMsgProcessFlag = usbFlag_idle;		//将串口数据处理状态标记为空闲 重新中断接收新的字符串
			_usbMsg.usbRxFinishTick = 0;
	}
}

#define USB_ONCE_LEN	(1000)
void usb_sendMsg(u8* sendbuf,u16 len)
{
	if(_usbMsg.usbWorkFlag == 0)return;
		static const uint32_t timeout_cnt_num = 1000000;
		
		u16 txLen = len;
		uint32_t timeout_cnt = 0;
		while(txLen>0)
		{
			if(txLen>=USB_ONCE_LEN)
			{
				while(0 != CDC_Transmit_HS(sendbuf,USB_ONCE_LEN))
				{
					if(timeout_cnt++ > timeout_cnt_num)
					{
						_usbMsg.usbWorkFlag = 0;
						break;
					}
				};
				sendbuf+=USB_ONCE_LEN;
				txLen-=USB_ONCE_LEN;
			}
			else
			{
				while(0 != CDC_Transmit_HS(sendbuf,txLen))
				{
					if(timeout_cnt++ > timeout_cnt_num)
					{
						_usbMsg.usbWorkFlag = 0;
						break;
					}
				};
				txLen = 0;
			}
		}
}
