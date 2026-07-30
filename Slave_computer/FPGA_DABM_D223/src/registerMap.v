//ARM到FPGA控制寄存器指令
`define 	RESERVE	0
`define 	REG_A2F_SRAM_WORK_MODE	1
//bit0 reg_sram_workEnable
`define 	REG_A2F_SRAM_EXIT_TRIG	2
`define 	REG_A2F_SRAM_RECORD_MAX_LEN1	3
`define 	REG_A2F_SRAM_RECORD_MAX_LEN2	4
`define 	REG_A2F_SRAM_RECORD_MAX_LEN3	5

`define 	REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX1	6
`define 	REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX2	7
`define 	REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX3	8

`define 	REG_A2F_FPGA_ADC_CH_ENABLE	9
`define 	REG_A2F_FPGA_ADC_CH_ENABLE_TOTAL	10
`define 	REG_A2F_FPGA_ADC_DIFF_ENABLE	11


//FPGA到ARM返回寄存器指令
`define 	RESERVE	0
`define 	REG_F2A_SRAM_WORK_MODE	1
`define 	REG_F2A_FIFO_IN_ADDR	2
`define 	REG_F2A_DIN	3
`define 	REG_A2F_SRAM_BUF_CNT	4



/*
// 主状态解码
wire pll_ok = pll_lock;
wire MODE_FPGA_STOP = (reg_a2f_sram_workEnable == 0);
wire MODE_FPGA_WRITE = (reg_a2f_sram_workEnable == 1);
wire MODE_STM32_READ_PSRAM = (reg_a2f_sram_workEnable == 2);
wire MODE_STM32_READ_FIFO = (reg_a2f_sram_workEnable == 3);
*/



