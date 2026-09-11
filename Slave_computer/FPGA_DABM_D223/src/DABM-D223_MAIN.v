 `include "registerMap.v"
 
module DABM_D223(
input	CLK_25M,
input	RST_N,
input [7:0]i_din,
//stm32接口
//spi
input spi_sck,
input spi_cs,
input spi_mosi,
output reg spi_miso,

//qspi
input qspi_sck,
input qspi_cs,
inout [3:0]qspi_io,

//psram接口
output  psram_cs_a,
output 	psram_sck_a,
inout	[3:0]psram_io_a,
	
//adc接口
output	ad_convert,
input	ad_busy,
output  ad_sck,
output  ad_cs,
input	ad_douta,
input	ad_doutb,
input	ad_doutc,
input	ad_doutd
 );

//对接SPI接口
//捕获CS下降沿
wire [3:0]psram_io_u1_a;
reg [2:0]spi_sck_edge;
reg [7:0]arm_spiRx_Buf;
reg [7:0]spi_io_outBuf;
reg [7:0]spi_sck_tick;
reg [7:0]spi_sck_tick_d;
reg [7:0]spi_reg_start_addr;
reg [7:0]spi_cmd;

reg [7:0]spi_reg_index;
reg [7:0]spi_reg_index_d;
reg spi_reg_index_enable;
reg  [7:0]reg_cmdA2FBuf[0:11];	//STM32写入FPGA的寄存器
reg  [7:0]reg_cmdF2ABuf[0:10];	//STM32读取FPGA的状态寄存器

//解析寄存器数据,将寄存器数据映射给变量使用
reg [7:0]reg_a2f_sram_workEnable;	//
reg [7:0]reg_a2f_sram_extTrig;	//
reg [23:0]reg_sram_recordMaxLen;
reg [23:0]reg_adc_sample_cycleMax;
reg [7:0]reg_a2f_sram_adcChEnable;	//
reg [7:0]reg_a2f_sram_adcChEnableTotal;	//
reg [7:0]reg_a2f_sram_adcDiffEnable;	//
reg [7:0]reg_f2a_sramBufCnt;	//

wire [7:0]din_buf;
assign din_buf = ~i_din;

reg [2:0]spi_cs_edge;
always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock))
    begin
		spi_cs_edge <= 'b111;
	end
	else
	begin
		//sck上升沿处理数据
		spi_cs_edge <= {spi_cs_edge[1:0],spi_cs};
	end
end


always @ (posedge clk_pllOut1)  
begin
	if(!pll_lock)					
    begin
		reg_sram_recordMaxLen <= 0;
    end
	else if((spi_cs_edge == 'b001) || (spi_cs_edge == 'b011))	//cs为0的时候通信正在进行, 不解析
    begin
		//更新A2F BUF
		reg_a2f_sram_workEnable <= 		reg_cmdA2FBuf[`REG_A2F_SRAM_WORK_MODE];
		reg_a2f_sram_extTrig <= 		reg_cmdA2FBuf[`REG_A2F_SRAM_EXIT_TRIG];
		
		reg_sram_recordMaxLen <= 		{reg_cmdA2FBuf[`REG_A2F_SRAM_RECORD_MAX_LEN3],
										reg_cmdA2FBuf[`REG_A2F_SRAM_RECORD_MAX_LEN2],
										reg_cmdA2FBuf[`REG_A2F_SRAM_RECORD_MAX_LEN1]};
										
		reg_adc_sample_cycleMax <= 	{reg_cmdA2FBuf[`REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX3],
										reg_cmdA2FBuf[`REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX2],
										reg_cmdA2FBuf[`REG_A2F_FPGA_ADC_SAMPLE_CYCLE_MAX1]};
										
		reg_a2f_sram_adcChEnable <= 	reg_cmdA2FBuf[`REG_A2F_FPGA_ADC_CH_ENABLE];
		reg_a2f_sram_adcChEnableTotal <= 	reg_cmdA2FBuf[`REG_A2F_FPGA_ADC_CH_ENABLE_TOTAL];
		reg_a2f_sram_adcDiffEnable <= 	reg_cmdA2FBuf[`REG_A2F_FPGA_ADC_DIFF_ENABLE];
							
		//更新F2A BUF
		reg_cmdF2ABuf[`REG_F2A_SRAM_WORK_MODE] <= reg_cmdA2FBuf[`REG_A2F_SRAM_WORK_MODE];
		reg_cmdF2ABuf[`REG_A2F_SRAM_BUF_CNT] <=  reg_f2a_sramBufCnt;
		reg_cmdF2ABuf[`REG_F2A_FIFO_IN_ADDR] <= sdpb_inAddr;
		reg_cmdF2ABuf[`REG_F2A_DIN] <= din_buf;
    end
end

// 主状态解码
wire MODE_FPGA_STOP = (reg_a2f_sram_workEnable == 0);
wire MODE_FPGA_RST = (reg_a2f_sram_workEnable == 'h5a);
wire MODE_FPGA_WRITE = (reg_a2f_sram_workEnable == 1);
wire MODE_STM32_READ_PSRAM = (reg_a2f_sram_workEnable == 2);
wire MODE_STM32_READ_FIFO = (reg_a2f_sram_workEnable == 3);
wire MODE_PSRAM_INIT = (reg_a2f_sram_workEnable == 'hff);

wire MODE_FPGA_EXT_IO_TRIG = (reg_a2f_sram_extTrig == 1);
wire MODE_FPGA_EXT_VOLT_TRIG_POS = (reg_a2f_sram_extTrig == 2);
wire MODE_FPGA_EXT_VOLT_TRIG_NEG = (reg_a2f_sram_extTrig == 3);

// PSRAM数据流向控制

assign psram_io_a = pll_lock ? 
                   ((MODE_FPGA_WRITE|MODE_PSRAM_INIT) ? psram_io_u1_a :      // FPGA -> PSRAM
                   ((MODE_STM32_READ_PSRAM && !qspi_dir) ? qspi_io : 4'hz)) :  // STM32 -> PSRAM
                   4'hz;  // PLL未锁定时高阻

//STM32和PSRAM QSPI引脚映射
// 使用条件运算符实现多路选择

// QSPI IO方向及数据流向控制
assign qspi_io = pll_lock ? 
                 (MODE_STM32_READ_PSRAM ? (qspi_dir ? psram_io_a:4'hz) :      // PSRAM数据 -> STM32
                 (MODE_STM32_READ_FIFO ?  (qspi_dir ?(qspi_rd_hl ? qspi_io_outBuf[7:4] : qspi_io_outBuf[3:0]) : 
                   4'hz) : 
                  4'hz)) : 
                 4'hz;  // PLL未锁定时高阻
				 
wire psram_cs_u1_a;
assign psram_cs_a = MODE_STM32_READ_PSRAM ? qspi_cs : psram_cs_u1_a ;

wire psram_sck_u1_a;
assign psram_sck_a = MODE_STM32_READ_PSRAM ? qspi_sck : psram_sck_u1_a ;

wire [15:0]ad7606_data[0:15];
wire ad_update_Flag;
wire clk_pllOut1;
reg [23:0]psram_rwIndex;	//sram存储器当前读取地址
reg [23:0]psram_rwIndex_d;	//sram存储器当前读取地址

//捕获din7的上升沿用来触发adc
reg psram_writeEnable;
reg adc_trig;
reg [3:0]adc_trig_edge;
always @ (posedge clk_pllOut1)
begin
	if(!pll_lock)					
    begin
		adc_trig_edge <= 0;
	end
	else 
	begin
		adc_trig_edge <= {adc_trig_edge[1:0],din_buf[7]};		
	end
end

always @ (posedge clk_pllOut1)	//adc_trig
begin
	if(!pll_lock)					
    begin
		adc_trig <= 0;
	end
	else if((adc_trig_edge == 'b001)||(adc_trig_edge == 'b011))
	begin
		adc_trig <= 1;
	end
	else
	begin
		adc_trig <= 0;
	end
end

reg psram_writeEnable;
reg reg_f2a_sramDataBufFlag;

always @ (posedge clk_pllOut1)  //stm32通过qspi发送指令给fpga, fpga解析寄存器开始动作
begin
	if(!pll_lock)			
    begin
        psram_rwIndex <= 0;
        psram_rwIndex_d <= 0;
        psram_writeEnable <= 0;
		reg_f2a_sramBufCnt <= 0;
		reg_f2a_sramDataBufFlag <= 0;
    end
	else if(spi_cs_edge != 'b111)
	begin
	
	end
	else if(MODE_FPGA_STOP)	//复位采集
	begin
		psram_rwIndex <= 0;	
		psram_rwIndex_d <= 0;	
		psram_writeEnable <= 0;	
	end
	else if(MODE_FPGA_WRITE)	//写入数据
	begin
		if((psram_rwIndex <= 'd8_380_000)&&(psram_rwIndex <= reg_sram_recordMaxLen))	//每次存储16个字节,最大8M字节
		begin
			if(ad_update_Flag)	//如果adc更新完成标志到来
			begin
				psram_rwIndex_d <= psram_rwIndex;
				psram_writeEnable <= 1;	
			end
			else
			begin
				psram_rwIndex <= psram_rwIndex_d + reg_a2f_sram_adcChEnableTotal;	//索引更新
				psram_writeEnable <= 0;	
			end
			reg_f2a_sramDataBufFlag <= 1;
		end
		else if(reg_f2a_sramDataBufFlag == 1)
		begin
			reg_f2a_sramBufCnt <=  reg_f2a_sramBufCnt + 1;
			reg_f2a_sramDataBufFlag <= 0;
		end
		else if(adc_trig)
		begin
			psram_rwIndex <= 0;	
			psram_rwIndex_d <= 0;	
			psram_writeEnable <= 0;	
		end
	end
end

/////////////////////////////////////////////spi接口驱动
/////////////////////////////////////////////spi接口驱动
/////////////////////////////////////////////spi接口驱动
/////////////////////////////////////////////spi接口驱动
/////////////////////////////////////////////spi接口驱动
/////////////////////////////////////////////spi接口驱动
/////////////////////////////////////////////spi接口驱动
/////////////////////////////////////////////spi接口驱动

always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock))
    begin
		spi_sck_edge <= 'b111;
	end
	else
	begin
		//sck上升沿处理数据
		spi_sck_edge <= {spi_sck_edge[1:0],spi_sck};
	end
end

always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( spi_cs  == 'b1))
    begin
		spi_reg_index <= 0;
		spi_reg_index_d <= 0;	
	end
	else
	begin
		if((spi_sck_tick == 1)&&spi_reg_index_enable)
		begin
			spi_reg_index  <= spi_reg_index_d + 1'd1;
		end
		else
		begin
			spi_reg_index_d <= spi_reg_index;
		end
	end
end

//fpga与stm32 通信对接sck上升沿计数
always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||(spi_cs  == 1'b1))
    begin
		spi_sck_tick <= 1'd0;	
		spi_sck_tick_d <= 1'd0;	
		spi_reg_index_enable<= 0;
	end
	else if({spi_sck_edge[2:0],spi_sck} == 0)
	begin
		if((spi_sck_tick == 9))
		begin
			spi_reg_index_enable <= 1;
			spi_sck_tick <= 1;
			spi_sck_tick_d <= 0;
		end
		else
		begin
			spi_sck_tick <= spi_sck_tick_d + 1'd1;
		end
	end
	else
	begin
		spi_sck_tick_d <= spi_sck_tick;
	end		
end

		

//通信格式:命令,地址,数据....
//spi通信寄存器地址累加
always @ (posedge clk_pllOut1 )  
begin
	if(!pll_lock)
    begin
		reg_cmdA2FBuf[`REG_A2F_SRAM_WORK_MODE] <= 'hff;
	end
	else if(spi_cs  == 'b1)
	begin
		arm_spiRx_Buf <= 0;
		spi_cmd <= 0;
		spi_reg_start_addr <= 0;
	end
	else if(({spi_sck_edge[2:0],spi_sck} == 'b0001)||({spi_sck_edge[2:0],spi_sck} == 'b0011))
	begin
		if((spi_sck_tick != 9) && (spi_sck_tick != 0))
		begin
			arm_spiRx_Buf[8-spi_sck_tick] <= spi_mosi;
		end
	end
	else if(({spi_sck_edge[2:0],spi_sck} == 'b1000)||({spi_sck_edge[2:0],spi_sck} == 'b1100))	//下降沿推送数据
	begin
		if(spi_sck_tick == 8)
		begin
			spi_io_outBuf <= reg_cmdF2ABuf[spi_reg_start_addr+spi_reg_index-1];
		end

		spi_miso <= spi_io_outBuf[7-spi_sck_tick];

	end
	else if(({spi_sck_edge[2:0],spi_sck} == 'b1111)&&(spi_sck_tick == 8))
	begin
		if(spi_reg_index == 0)
		begin
			spi_cmd <= arm_spiRx_Buf;
		end
		else if(spi_cmd == 'h80)
		begin
			if(spi_reg_index == 1)
			begin
				spi_reg_start_addr <= arm_spiRx_Buf;
			end
			else
			begin
				reg_cmdA2FBuf[spi_reg_start_addr + spi_reg_index-2] <= arm_spiRx_Buf;
			end
		end
		else if(spi_cmd == 'h00)
		begin
			if(spi_reg_index == 1)
			begin
				spi_reg_start_addr <= arm_spiRx_Buf;
			end
			
		end
	end
end


///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动
///////////////////////////////////////////// Qspi接口驱动

reg qspi_dir;
reg [7:0]qspi_sck_tick;
reg [7:0]qspi_sck_tick_d;
reg [1:0]qspi_sck_edge;

//对接QSPI接口
//捕获CS下降沿
reg [1:0]qspi_sck_edge;
reg [7:0]arm_qspiRx_Buf;
reg [7:0]qspi_io_outBuf;
reg  [7:0]qspi_cmd;

reg [15:0]qspi_reg_start_addr;
reg [4:0]qspi_reg_rw_addr;
reg [15:0]qspi_reg_rw_addr_d;
reg qspi_reg_index_enable;

reg qspi_rd_hl;

reg [2:0]psram_rw_Finish_pos_tick;	//sram读写完成标志位(上升沿,用来给计数器判断)
reg psram_readWrite_flag;	//psram存储触发标志

reg [23:0]reg_adcSramBuf_indexNow;

reg reg_psram_read_write_dir;

reg [23:0]psramSaveAddrIndex;	//sram存储器当前存储地址
reg [23:0]psramReadAddrIndex;	//sram存储器当前读取地址
reg [23:0]psram_rwIndex;	//sram存储器当前读取地址


//控制QSPI的IO输入输出方向
always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( qspi_cs  == 'b1))
    begin
		qspi_dir <= 0;
	end
	else if(MODE_STM32_READ_PSRAM)
	begin
		if(qspi_sck_tick >= 9)
		begin
			qspi_dir <= 1;
		end
	end
	else if(MODE_STM32_READ_FIFO)
	begin
		if(qspi_sck_tick >= 9)
		begin
			qspi_dir <= qspi_cmd[7];
		end	
	end
end


always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( qspi_cs  == 'b1))
    begin
		qspi_sck_edge <= 'b0;
	end
	else 
	begin
		//sck上升沿处理数据
		qspi_sck_edge <= {qspi_sck_edge[0],qspi_sck};
	end
end




//qspi寄存器通信索引地址累加器使能(数据传输开始)
always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( qspi_cs  == 'b1)||(!MODE_STM32_READ_FIFO))
    begin
		qspi_reg_index_enable <= 0;
	end
	else if(MODE_STM32_READ_FIFO)
	begin
		if(({qspi_sck_edge[1:0],qspi_sck} == 'b110)||({qspi_sck_edge[1:0],qspi_sck} == 'b100))
		begin			
			if(qspi_sck_tick == 0)
			begin
				qspi_reg_index_enable <= 'b0;
			end	
			else if(qspi_sck_tick=='d10)
			begin
				qspi_reg_index_enable <= 'b1;
			end
		end
	end
end

//qspi寄存器高低字节切换
always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( qspi_cs  == 'b1))
    begin
		qspi_rd_hl <= 'b0;
	end
	else
	begin
		if(({qspi_sck_edge[1:0],qspi_sck} == 'b110)||({qspi_sck_edge[1:0],qspi_sck} == 'b100))
		begin			
			if(qspi_sck_tick[0] == 0)//最后1位为0 代表偶数
			begin
				qspi_rd_hl <= 'b1;
			end
			else
			begin
				qspi_rd_hl <= 'b0;
			end
		end
	end
end


//fpga与stm32 通信对接, 控制方向, 提取命令和地址
always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( qspi_cs  == 'b1))
    begin
		qspi_cmd <= 0;
		qspi_reg_start_addr <= 0;
	end
	else if(MODE_STM32_READ_FIFO)
	begin
		if(({qspi_sck_edge[1:0],qspi_sck} == 'b100)||({qspi_sck_edge[1:0],qspi_sck} == 'b110))
		begin
			if(qspi_sck_tick == 2)
			begin
				// 0 1为cmd
				//2 3,  4 5 , 6 7, 为地址
				//8,9为第一个数据
				qspi_cmd <= arm_qspiRx_Buf;
			end
			else if(qspi_sck_tick == 6)
			begin
				qspi_reg_start_addr[15:8] <= arm_qspiRx_Buf;
			end
			else if(qspi_sck_tick == 8)
			begin
				qspi_reg_start_addr[7:0] <= arm_qspiRx_Buf;
			end
		end
	end
end


//fpga接收程序 qspi, stm32发送
always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( qspi_cs  == 'b1))
    begin
		arm_qspiRx_Buf <= 0;
    end
    else if((qspi_cs  == 'b0)&(qspi_dir == 0)&(MODE_STM32_READ_FIFO))
    begin
		 //捕获sck上升沿,每个字节占用2个上升沿,
		 //第一个上升沿为bit7:4  第二个上升沿为bit3:0
		 //第一个字节bit7为读写标志位, 读为1,写为0,为0写的时候io为高阻态
		 //第2,3,4字节为读写地址, 第5,6字节为等待, 第7字节开始为数据
		 //上升沿更新下降沿buf计数, 下降沿更新上升沿buf计数, 两个独立计数器		 
		if(({qspi_sck_edge[1:0],qspi_sck} == 'b001)||({qspi_sck_edge[1:0],qspi_sck} == 'b011))
		begin
			//sck寄存器计数
			if(qspi_sck_tick[0] == 0)//最后1位为0 代表偶数
			begin
				arm_qspiRx_Buf <= {qspi_io,arm_qspiRx_Buf[3:0]};			
			end
			else//最后1位不为0 代表奇数
			begin
				arm_qspiRx_Buf <= {arm_qspiRx_Buf[7:4],qspi_io};//推送qspi数据到arm
			end
		end
    end
end

//fpga发送程序 qspi, stm32读取
always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( qspi_cs  == 'b1))
    begin
		qspi_io_outBuf <= 0;
    end
    else if((MODE_STM32_READ_FIFO))
    begin
		if(({qspi_sck_edge[1:0],qspi_sck} == 'b110)||({qspi_sck_edge[1:0],qspi_sck} == 'b100))
		begin
			if(qspi_sck_tick[0] == 0)
			begin
				if(qspi_sck_tick > 'd8)
				begin 
					// 不再块内寻址数组，直接使用预取好的数据
					if(qspi_cmd == 'h80)
					begin
						qspi_io_outBuf <= adc_buf_real_data;
					end
					else if(qspi_cmd == 'h81)
					begin
						qspi_io_outBuf <= adc_buf_sdpb_data;
					end
				end
			end
		end
    end
end


//fpga与stm32 通信对接sck上升沿计数
always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( qspi_cs  == 1'b1))
    begin
		qspi_sck_tick <= 1'd0;	
		qspi_sck_tick_d <= 1'd0;	
	end
	else if(({qspi_sck_edge[1:0],qspi_sck} == 'b110)||({qspi_sck_edge[1:0],qspi_sck} == 'b111))
	begin
		qspi_sck_tick <= qspi_sck_tick_d + 1'd1;
	end
	else if(({qspi_sck_edge[1:0],qspi_sck} == 'b001)||({qspi_sck_edge[1:0],qspi_sck} == 'b011))
	begin
		if(qspi_sck_tick == 'd255)
		begin
			qspi_sck_tick_d <= 'd199;
		end
		else
		begin
			qspi_sck_tick_d <= qspi_sck_tick;
		end
	end
end



reg [7:0] adc_buf_real_data;
always @(posedge clk_pllOut1) 
begin
    if(!pll_lock) 
	begin
        adc_buf_real_data <= 8'd0;
    end 
	else 
	begin
        adc_buf_real_data <= reg_adcRealBuf[qspi_reg_rw_addr];
    end
end
// 提前一拍根据地址取出ADC缓存数据，拆分关键路径
reg [7:0] adc_buf_sdpb_data;
always @(posedge clk_pllOut1) 
begin
    if(!pll_lock) 
	begin
        adc_buf_sdpb_data <= 8'd0;
    end 
	else 
	begin
        adc_buf_sdpb_data <= reg_adcSdpbBuf[qspi_reg_rw_addr];
    end
end

//qspi通信寄存器地址累加

// qspi 在线记录仪 qspi索引地址
reg [7:0]sdpb_outAddr;
reg [7:0]sdpb_outAddr_d;
reg [7:0]sdpb_inAddr;
reg [7:0]sdpb_inAddr_d;

always @ (posedge clk_pllOut1 )  
begin
	if((!pll_lock)||( qspi_cs  == 'b1))
    begin
		qspi_reg_rw_addr_d <= 0;
		qspi_reg_rw_addr <= 0;
		sdpb_read_clk <= 0;
		sdpb_outAddr <= 0;
		sdpb_outAddr_d <= 0;
	end
	else if(qspi_sck_tick == 8)
	begin
		sdpb_outAddr <= qspi_reg_start_addr[7:0];
		sdpb_outAddr_d <= qspi_reg_start_addr[7:0];
	end
	else if(qspi_sck_tick == 9)
	begin
		sdpb_read_clk <= 1;
	end
	else if(qspi_reg_index_enable)
	begin
		if(({qspi_sck_edge[1:0],qspi_sck} == 'b001)||({qspi_sck_edge[1:0],qspi_sck} == 'b011))
		begin
			if((qspi_sck_tick[0]))
			begin
				if(qspi_reg_rw_addr_d == 16)
				begin
					sdpb_read_clk <= 1;
					qspi_reg_rw_addr <= 0;
					sdpb_outAddr_d <= sdpb_outAddr;
				end
				else
				begin
					sdpb_read_clk <= 0;
					qspi_reg_rw_addr <= qspi_reg_rw_addr_d + 'd1;
					sdpb_outAddr <= sdpb_outAddr_d + 1;
				end
			end
		end
		else
		begin
			qspi_reg_rw_addr_d <= qspi_reg_rw_addr;
		end
	end
end


always@(posedge clk_pllOut1) 
	begin
	if (!pll_lock)
	begin     
		sdpb_inAddr <= 0;
		sdpb_inAddr_d <= 0;
	end 
	else if(ad_update_Flag)
	begin
		sdpb_inAddr_d <=  sdpb_inAddr;
	end
	else 
	begin
		sdpb_inAddr <=  sdpb_inAddr_d + 'd1;
	end
end

wire [7:0]reg_adcRealBuf[0:17];	//STM32即时读取当前adc值(实时值)
/*
always@(posedge clk_pllOut1) 
	begin
	if (!pll_lock||( qspi_cs  == 'b0))
	begin     

	end 
	else if(ad_update_Flag)
	begin
		{reg_adcRealBuf[1],reg_adcRealBuf[0]} <= ad7606_data[0];
		{reg_adcRealBuf[3],reg_adcRealBuf[2]} <= ad7606_data[1];
		{reg_adcRealBuf[5],reg_adcRealBuf[4]} <= ad7606_data[2];
		{reg_adcRealBuf[7],reg_adcRealBuf[6]} <= ad7606_data[3];
		{reg_adcRealBuf[9],reg_adcRealBuf[8]} <= ad7606_data[4];
		{reg_adcRealBuf[11],reg_adcRealBuf[10]} <= ad7606_data[5];
		{reg_adcRealBuf[13],reg_adcRealBuf[12]} <= ad7606_data[6];
		{reg_adcRealBuf[15],reg_adcRealBuf[14]} <= ad7606_data[7];
		{reg_adcRealBuf[17],reg_adcRealBuf[16]} <= {8'b0,din_buf};
	end
end
*/

assign {reg_adcRealBuf[1],reg_adcRealBuf[0]} = ad7606_data[0];
assign {reg_adcRealBuf[3],reg_adcRealBuf[2]} = ad7606_data[1];
assign {reg_adcRealBuf[5],reg_adcRealBuf[4]} = ad7606_data[2];
assign {reg_adcRealBuf[7],reg_adcRealBuf[6]} = ad7606_data[3];
assign {reg_adcRealBuf[9],reg_adcRealBuf[8]} = ad7606_data[4];
assign {reg_adcRealBuf[11],reg_adcRealBuf[10]} = ad7606_data[5];
assign {reg_adcRealBuf[13],reg_adcRealBuf[12]} = ad7606_data[6];
assign {reg_adcRealBuf[15],reg_adcRealBuf[14]} = ad7606_data[7];
assign {reg_adcRealBuf[17],reg_adcRealBuf[16]} = din_buf;

wire [15:0]ad7606_data[0:7];

wire [7:0]reg_adcSdpbBuf[0:17];	//STM32即时读取当前adc值(实时值)
// 新增RAM输出缓存寄存器
/*
reg [135:0] sdpb_outData_reg;
always @(posedge clk_pllOut1) 
begin
    if(!pll_lock)
        sdpb_outData_reg <= 'd0;
    else
        sdpb_outData_reg <= sdpb_outData;
end
*/
// assign改用寄存后数据，消除RAM异步长组合
assign {
    reg_adcSdpbBuf[17],reg_adcSdpbBuf[16],reg_adcSdpbBuf[15],reg_adcSdpbBuf[14],reg_adcSdpbBuf[13],
    reg_adcSdpbBuf[12],reg_adcSdpbBuf[11],reg_adcSdpbBuf[10],reg_adcSdpbBuf[9],
    reg_adcSdpbBuf[8],reg_adcSdpbBuf[7],reg_adcSdpbBuf[6],reg_adcSdpbBuf[5],
    reg_adcSdpbBuf[4],reg_adcSdpbBuf[3],reg_adcSdpbBuf[2],reg_adcSdpbBuf[1],reg_adcSdpbBuf[0]
} = sdpb_outData;

assign sdpb_inData = {
din_buf,
ad7606_data[7],
ad7606_data[6],
ad7606_data[5],
ad7606_data[4],
ad7606_data[3],
ad7606_data[2],
ad7606_data[1],
ad7606_data[0]
};

wire [135:0]sdpb_inData;


reg sdpb_read_clk;
wire [135:0]sdpb_outData;

wire fifo_AlmostFull,fifo_AlmostEmpty;
wire fifo_empty,fifo_full;

 Gowin_SDPB sdpb_u1(
 .din(sdpb_inData), 
 .dout(sdpb_outData), 
 
 .clka(ad_update_Flag),//写入时钟
 .clkb(sdpb_read_clk), //读取时钟
 
 .ada(sdpb_inAddr), //写入地址
 .adb(sdpb_outAddr),    //读取地址
 
 .cea(1), 
 .reseta(!pll_lock), 
 .ceb(1), 
 .resetb(!pll_lock), 
 .oce(1)

 );
 

psram psram_u1(
	.psram_cs(psram_cs_u1_a),
	.psram_sck(psram_sck_u1_a),
	.psram_io(psram_io_u1_a),

	.psram_inData1(ad7606_data[0]),
	.psram_inData2(ad7606_data[1]),
	.psram_inData3(ad7606_data[2]),
	.psram_inData4(ad7606_data[3]),
	.psram_inData5(ad7606_data[4]),
	.psram_inData6(ad7606_data[5]),
	.psram_inData7(ad7606_data[6]),
	.psram_inData8(ad7606_data[7]),
	.writeAdcChEnable(reg_a2f_sram_adcChEnable),

	.psram_rw_addr(psram_rwIndex),
	.read_write_Enable(psram_writeEnable),
	.psram_init(MODE_PSRAM_INIT),
	.i_clk(clk_pllOut1),
	.rst_n(pll_lock)
);

ad7606 _ad7606_u1 (
	.ad7606_busy(ad_busy),
	.ad7606_convert(ad_convert),  
	.ad7606_sck(ad_sck),
	.ad7606_cs(ad_cs),
	._ad7606_douta(ad_douta),
	._ad7606_doutb(ad_doutb),
	.ad_update_Flag(ad_update_Flag),
	.ad7606_data_1(ad7606_data[0]),
	.ad7606_data_2(ad7606_data[1]),
	.ad7606_data_3(ad7606_data[2]),
	.ad7606_data_4(ad7606_data[3]),
	.ad7606_data_5(ad7606_data[4]),
	.ad7606_data_6(ad7606_data[5]),
	.ad7606_data_7(ad7606_data[6]),
	.ad7606_data_8(ad7606_data[7]),
	.adc_sample_cycleMax(reg_adc_sample_cycleMax),
	.reg_sram_adcDiffEnable(reg_a2f_sram_adcDiffEnable),
	
	
	.i_clk(clk_pllOut1),
	.rst_n(pll_lock)
);

reg adc_fifo_waitQspiRead;

reg pll_lock;
wire pll_isLock;

Gowin_rPLL  pll_u1(
.clkout(clk_pllOut1),
 .lock(pll_isLock),
 .reset(!RST_N),
 .clkin(CLK_25M)
);

reg [24:0]rst_cnt;
reg rst_onlyOne;
always @(posedge CLK_25M) 
begin
    if(!RST_N)
	begin
        pll_lock <= 'd0;
		rst_cnt <= 'd0;
		rst_onlyOne <= 'd0;
	end
	else if(!pll_isLock)
	begin
        pll_lock <= 'd0;
		rst_cnt <= 'd0;
		rst_onlyOne <= 'd0;
	end	
	else if(MODE_FPGA_RST&(!rst_onlyOne))
	begin
        pll_lock <= 'd0;
		rst_cnt <= 'd0;
		rst_onlyOne <= 'b1;
	end
    else if(rst_cnt < 'd1_000_000)
	begin
        rst_cnt <= rst_cnt + 'd1;
		pll_lock <= 'd0;
	end
	else
	begin
		rst_cnt <= rst_cnt;
		pll_lock <= 'd1;
	end
end


endmodule



