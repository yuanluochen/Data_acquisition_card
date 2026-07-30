#ifndef __REGMAP_H_
#define __REGMAP_H_


//ARM到FPGA控制寄存器指令
#define 	RESERVE	0
#define 	REG_SRAM_WORK_STATE1	1
//bit0 reg_sram_workEnable
#define 	REG_SRAM_WORK_STATE2	2
#define 	REG_SRAM_RECORD_MAX_LEN1	3
#define 	REG_SRAM_RECORD_MAX_LEN2	4
#define 	REG_SRAM_RECORD_MAX_LEN3	5
#define 	REG_SRAM_RECORD_MAX_LEN4	6


//FPGA到ARM返回寄存器指令
#define 	RESERVE	0
#define 	REG_SRAM_WORK_STATE1	1
#define 	REG_SRAM_WORK_STATE2	2



#endif

