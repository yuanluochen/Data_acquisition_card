 #ifndef __USB_MSG_H_
#define __USB_MSG_H_

#include "main.h"
#pragma pack(1)

#define USB_TX_BUF_LEN			22000
#define USB_RX_BUF_LEN			22000

typedef struct{
	u16 usbRxFinishTick;
	u8 usbRxMsgProcessFlag;
	u16 usbRxIndex;
	u8 usbRxBuf[USB_RX_BUF_LEN];
	u8 usbWorkFlag;
}usbMsg;

extern usbMsg _usbMsg;

void usbMsg_timer_task(void);
void usbMsg_thread_task(void);

uint8_t CDC_Transmit_HS(uint8_t* Buf, uint16_t Len);
void usb_sendMsg(u8* sendbuf,u16 len);

enum _usbFlag
{
    usbFlag_idle = 0,
    usbFlag_busy = 1,
};



#endif


