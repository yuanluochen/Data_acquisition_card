#include "main.h"
#pragma pack(1)

dioWorkParam _dioParam;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim8;

u16 motorAccDiv = 0;//预分频系数

void dio_tim_task()
{
  HAL_GPIO_WritePin(DOUT_1_GPIO_Port,DOUT_1_Pin,_dioParam.dout[0]);
  HAL_GPIO_WritePin(DOUT_2_GPIO_Port,DOUT_2_Pin,_dioParam.dout[1]);

	
//	_dioParam.din[0] = !HAL_GPIO_ReadPin(DIN_1_GPIO_Port,DIN_1_Pin);
//	_dioParam.din[1] = !HAL_GPIO_ReadPin(DIN_2_GPIO_Port,DIN_2_Pin);
//	_dioParam.din[2] = !HAL_GPIO_ReadPin(DIN_3_GPIO_Port,DIN_3_Pin);
//	_dioParam.din[3] = !HAL_GPIO_ReadPin(DIN_4_GPIO_Port,DIN_4_Pin);
//	_dioParam.din[4] = !HAL_GPIO_ReadPin(DIN_5_GPIO_Port,DIN_5_Pin);
//	_dioParam.din[5] = !HAL_GPIO_ReadPin(DIN_6_GPIO_Port,DIN_6_Pin);
//	_dioParam.din[6] = !HAL_GPIO_ReadPin(DIN_7_GPIO_Port,DIN_7_Pin);
//	_dioParam.din[7] = !HAL_GPIO_ReadPin(DIN_8_GPIO_Port,DIN_8_Pin);
												
	HAL_GPIO_WritePin( AD_RANGE_GPIO_Port, AD_RANGE_Pin, _framDatas._adcParam.adcRange&1);

		motorAccDiv++;
		if(motorAccDiv > 100)
		{
				motorAccDiv = 0;
			
				for(u8 ch=0;ch<6;ch++)
				{
					if(_dioParam.pwmEnable[ch] == 0)
					{
						_dioParam.presentFreq[ch] =  10;
						_dioParam.findDecPulseFlag[ch] = 1;
					}
					else if(_dioParam.pwmPulseNum[ch] != 0)
					{
						//计算减速时间需要的脉冲
						//如果脉冲数过半, 速度还没到最大, 则开始减速
						if(_dioParam.findDecPulseFlag[ch] == 1)
						{
							if(_dioParam.presentFreq[ch] >= _framDatas._pwmDatas[ch].pwmFreq )
							{
								_dioParam.pwmCalcDecPulse[ch] = _dioParam.pwmPulseNum[ch] - _dioParam.pwmPulseTick[ch];
								_dioParam.findDecPulseFlag[ch] = 0;
							}
							else
							{
								_dioParam.pwmCalcDecPulse[ch] = _dioParam.pwmPulseNum[ch] / 2;
							}
						}
						
						//计算加减速
						if(_dioParam.pwmPulseTick[ch] < _dioParam.pwmCalcDecPulse[ch])
						{
								if(_dioParam.presentFreq[ch] > _framDatas._pwmDatas[ch].pwmAccUnit)
								{
									_dioParam.presentFreq[ch] -= _framDatas._pwmDatas[ch].pwmAccUnit;
								}
								else
								{
									_dioParam.presentFreq[ch] =  10;
								}
								_dioParam.presentFreq[ch] = _dioParam.presentFreq[ch] < 10 ? 10 : _dioParam.presentFreq[ch];
						}
						else	
						{
								_dioParam.presentFreq[ch] += _framDatas._pwmDatas[ch].pwmAccUnit;
								_dioParam.presentFreq[ch] = _dioParam.presentFreq[ch] > _framDatas._pwmDatas[ch].pwmFreq 
																						? _framDatas._pwmDatas[ch].pwmFreq : _dioParam.presentFreq[ch];
						}
					}
					else
					{
						//非脉冲技术模式 直接赋值设定频率
						_dioParam.presentFreq[ch] = _framDatas._pwmDatas[ch].pwmFreq;
						_dioParam.presentFreq[ch] = _dioParam.presentFreq[ch] > 5000 ? 5000:_dioParam.presentFreq[ch];
						_dioParam.presentFreq[ch] = _dioParam.presentFreq[ch] < 1 ? 1 : _dioParam.presentFreq[ch];

					}
				}
		}
}


             
void pwm_task_thread()
{
    //2和5是32位定时器,134是16位
	  htim1.Instance->CNT = htim1.Instance->CNT > 65535 ? 0 : htim1.Instance->CNT;
    htim2.Instance->CNT = htim2.Instance->CNT > 65535 ? 0 : htim2.Instance->CNT;
    htim3.Instance->CNT = htim3.Instance->CNT > 65535 ? 0 : htim3.Instance->CNT;
    htim4.Instance->CNT = htim4.Instance->CNT > 65535 ? 0 : htim4.Instance->CNT;
    htim5.Instance->CNT = htim5.Instance->CNT > 65535 ? 0 : htim5.Instance->CNT;
    htim8.Instance->CNT = htim8.Instance->CNT > 65535 ? 0 : htim8.Instance->CNT;

}


static	u32 pwm_tim_sys_clk = 84000000;
u8 pwmEnable_his[6];
u8 pwmEnableClearEnableFlag[6];
void fun_calcPwmParam(u8 ch,TIM_HandleTypeDef *_pTim) 
{
		ch-=1;
		
		if(_dioParam.pwmEnable[ch] & ! pwmEnable_his[ch])
		{
			_dioParam.pwmPulseTick[ch] = _dioParam.pwmPulseNum[ch];
			pwmEnableClearEnableFlag[ch] = 1;
			_pTim->Instance->CNT = 0;
		}
		
		
		if(_dioParam.pwmEnable[ch] == 0)
		{
				_dioParam.arr[ch] = 49999;
				_dioParam.psc[ch]  = 100;
				_dioParam.duty[ch] = 0;
		}

		//捕获tim使能上升沿, 更新脉冲数,_dioParam.pwmPulseNum[ch]为0时脉冲不计数
		else if(_dioParam.pwmPulseTick[ch]||(_dioParam.pwmPulseNum[ch] == 0))
		{
				_dioParam.pwmPulseTick[ch] -= _dioParam.pwmPulseTick[ch] == 0 ? 0 : 1;
			
				//计算arr(pcs预设为0)
				_dioParam.arr[ch] = pwm_tim_sys_clk / _dioParam.presentFreq[ch];
			
				//根据arr计算psc, 将arr取余
				_dioParam.psc[ch]  = _dioParam.arr[ch] / 0x10000;
			
				_dioParam.arr[ch] = _dioParam.arr[ch] / (_dioParam.psc[ch] + 1);

				_dioParam.duty[ch] = (_framDatas._pwmDatas[ch].pwmDuty * _dioParam.arr[ch]) / 1000;
				
		}
		else
		{
				//任务结束清除pwm使能
					if(pwmEnableClearEnableFlag[ch])
					{
						_dioParam.pwmEnable[ch] = 0;
						pwmEnableClearEnableFlag[ch] = 0;
					}
					
				_dioParam.arr[ch] = 49999;
				_dioParam.psc[ch]  = 100;
				_dioParam.duty[ch] = 0;
				_dioParam.uploadFinshFlag = 1;
		}
		
			_pTim->Instance->PSC =  _dioParam.psc[ch];
			_pTim->Instance->ARR = _dioParam.arr[ch]; 
		
			pwmEnable_his[ch] = _dioParam.pwmEnable[ch];

}
    

void TIM1_task(void)
{
	fun_calcPwmParam(1,&htim1);
	htim1.Instance->CCR1 = _dioParam.duty[0]; 
}


void TIM2_task(void)
{
	fun_calcPwmParam(6,&htim2);
	htim2.Instance->CCR2 = _dioParam.duty[5]; 
}	


void TIM3_task(void)
{
	fun_calcPwmParam(3,&htim3);
	htim3.Instance->CCR2 = _dioParam.duty[2]; 
}


void TIM4_task(void)
{
	fun_calcPwmParam(2,&htim4);
	htim4.Instance->CCR3 = _dioParam.duty[1]; 
}

void TIM5_task(void)
{
	fun_calcPwmParam(5,&htim5);
	htim5.Instance->CCR3 = _dioParam.duty[4]; 
}

void TIM8_task(void)
{
	fun_calcPwmParam(4,&htim8);
	htim8.Instance->CCR4 = _dioParam.duty[3]; 
}





