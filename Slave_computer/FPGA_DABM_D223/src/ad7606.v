`timescale 1ns/1ns

module ad7606( 
	
	input  ad7606_busy,
	output reg	ad7606_convert,  
	output reg	ad7606_sck,
	output reg	ad7606_cs,
	input  _ad7606_douta,
	input  _ad7606_doutb,
	input  [23:0]adc_sample_cycleMax,
	input  [7:0]reg_sram_adcDiffEnable,

	output  reg[15:0]ad7606_data_1,
	output  reg[15:0]ad7606_data_2,
	output  reg[15:0]ad7606_data_3,
	output  reg[15:0]ad7606_data_4,
	output  reg[15:0]ad7606_data_5,
	output  reg[15:0]ad7606_data_6,
	output  reg[15:0]ad7606_data_7,
	output  reg[15:0]ad7606_data_8,
	
	output reg ad_update_Flag,
 
	input i_clk,
	input rst_n
	);
	
localparam CONVERT_MAX  = 'd145;
localparam CONVERT_MAX_DIV2  = 'd80;


reg [15:0]ad_valueA;
reg [15:0]ad_valueB;


reg  [15:0]ad7606_dataA[0:3];
reg  [15:0]ad7606_dataB[0:3];
	
reg [7:0] adc_clk_tick;		
reg [23:0] convert_tick;
		

//产生convert信号, 
always@(posedge i_clk) 
if (!rst_n)
begin 	
	convert_tick  <=  'b0;
	ad7606_convert <= 'b1;
end 
else if(adc_sample_cycleMax < CONVERT_MAX)
begin
	if(convert_tick == CONVERT_MAX)
	begin
		convert_tick <= 'd0;
		ad7606_convert <= 'b0;
	end
	else if(convert_tick == CONVERT_MAX_DIV2)
	begin
		convert_tick <= convert_tick + 'b1;
		ad7606_convert <= 'b1;
	end
	else
	begin
		convert_tick <= convert_tick + 'b1;
	end
end
else
begin
	if(convert_tick == adc_sample_cycleMax)
	begin
		convert_tick <= 'd0;
		ad7606_convert <= 'b0;
	end
	else if(convert_tick == CONVERT_MAX_DIV2)
	begin
		convert_tick <= convert_tick + 'b1;
		ad7606_convert <= 'b1;
	end
	else
	begin
		convert_tick <= convert_tick + 'b1;
	end
end


//抓取busy下降沿
reg busy_d,busy_d2,busy_negedge;

always@(posedge i_clk) 
if (!rst_n)
begin 	
	busy_negedge <= 'b0;
	busy_d  <= 'b0;
end 
else 
begin
	busy_d <= ad7606_busy;
	busy_d2 <= busy_d;
	if(busy_d2 && !busy_d)
	begin
		busy_negedge <= 'b1;
	end
	else
	begin
		busy_negedge <= 'b0;
	end
end



//生成SCK计时器, 给clk时钟分频
reg [2:0]chAddr;	//8ch, 每次读2ch, 所以共读4次, 需要2bit
localparam  ADC_CNT_MAX  = 'd33;
reg [2:0]updateFlag_tick;



always@(posedge i_clk) 
if (!rst_n )
begin 	
	adc_clk_tick  <=  ADC_CNT_MAX;	//复位时数字赋最大值, 最大时候不动作, 64
end
else if (busy_negedge)	//busy下降沿代表芯片转换完成
begin 	
	adc_clk_tick  <=  'b0;	//计数清零
end 
else
begin
	if(adc_clk_tick == ADC_CNT_MAX)		//64, clk计数完成64个周期则结束一次读取, emc位宽为32bit,相当于2个16位adc值, 共64个sck边沿
	begin
		if(chAddr != 'd3)		//说明已经读取完成
		begin
			adc_clk_tick <= 0;
		end
	end
	else
	begin
		adc_clk_tick <= adc_clk_tick + 'd1;
	end
end
	
always@(posedge i_clk) 
if (!rst_n )
begin 	
	chAddr <= 'b11;		//同上
end
else if (busy_negedge)	//busy下降沿代表芯片转换完成
begin 	
	chAddr <= 'd0;			//ch清零
end 
else if(adc_clk_tick == ADC_CNT_MAX)
begin
	if(chAddr != 'd3)		//说明已经读取完成
	begin
		chAddr <= chAddr + 3'd1;
	end
end

//ad7606_busy下降沿开始采集
//生成SCK计时器, 给clk时钟分频
always@(posedge i_clk) 
if (!rst_n )
begin 	
	ad7606_cs <= 'b1;	//cs取消片选
end
else if (busy_negedge)	//busy下降沿代表芯片转换完成
begin 	
	ad7606_cs <= 'b0;		//片选
	updateFlag_tick <= 0;
	ad_update_Flag <= 'b0;
end 
else if((adc_clk_tick == ADC_CNT_MAX)&&(chAddr == 'd3))		//64, clk计数完成64个周期则结束一次读取, emc位宽为32bit,相当于2个16位adc值, 共64个sck边沿
begin
	if(updateFlag_tick<=7)
	begin
		if(reg_sram_adcDiffEnable[0])
		begin
			ad7606_data_1 <= ad7606_dataA[0] - ad7606_dataA[1];
			ad7606_data_2 <= ad7606_dataA[1] - ad7606_dataA[0];
		end
		else
		begin
			ad7606_data_1 <= ad7606_dataA[0];
			ad7606_data_2 <= ad7606_dataA[1];
		end

		if(reg_sram_adcDiffEnable[1])
		begin
			ad7606_data_3 <= ad7606_dataA[2] - ad7606_dataA[3];
			ad7606_data_4 <= ad7606_dataA[3] - ad7606_dataA[2];
		end
		else
		begin
			ad7606_data_3 <= ad7606_dataA[2];
			ad7606_data_4 <= ad7606_dataA[3];
		end


		if(reg_sram_adcDiffEnable[2])
		begin
			ad7606_data_5 <= ad7606_dataB[0] - ad7606_dataB[1];
			ad7606_data_6 <= ad7606_dataB[1] - ad7606_dataB[0];
		end
		else
		begin
			ad7606_data_5 <= ad7606_dataB[0];
			ad7606_data_6 <= ad7606_dataB[1];
		end

		if(reg_sram_adcDiffEnable[3])
		begin
			ad7606_data_7 <= ad7606_dataB[2] - ad7606_dataB[3];
			ad7606_data_8 <= ad7606_dataB[3] - ad7606_dataB[2];
		end
		else
		begin
			ad7606_data_7 <= ad7606_dataB[2];
			ad7606_data_8 <= ad7606_dataB[3];
		end
		
		ad_update_Flag <= 'b1;
		updateFlag_tick <= updateFlag_tick + 'd1;
	end
	else
	begin
		ad7606_cs <= 'b1;	//cs取消片选
		ad_update_Flag <= 'b0;
	end
end



always@(posedge i_clk) 
if (!rst_n )
begin 	
	ad7606_sck  <= 'b0;
end
else
begin
	case (adc_clk_tick)	
		//上升推送adc数据, 下降沿锁fpga存数据
		0,2,4,6,
		8,10,12,14,
		16,18,20,22,
		24,26,28,30:
		begin 	
			ad7606_sck  <= 'b0;
		end 
		
		1,3,5,7,
		9,11,13,15,
		17,19,21,23,
		25,27,29,31:
		begin 	
			ad7606_sck  <= 'b1;
		end 

		default
		begin
			ad7606_sck  <= 'b1;
		end
	endcase
end

//每个周期的动作
always@(posedge i_clk) 
if (!rst_n)
begin 	
	ad_valueA <= 'd0;
	ad_valueB <= 'd0;
end 
else 
begin 
	case (adc_clk_tick)	
		1://,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31:
		begin
			ad_valueA[15-(adc_clk_tick>>1)] <= _ad7606_douta;
			ad_valueB[15-(adc_clk_tick>>1)] <= _ad7606_doutb;
		end
		
		3:
		begin
			ad_valueA[14] <= _ad7606_douta;
			ad_valueB[14] <= _ad7606_doutb;
		end
		
		5:
		begin
			ad_valueA[13] <= _ad7606_douta;
			ad_valueB[13] <= _ad7606_doutb;
		end
		
		7:
		begin
			ad_valueA[12] <= _ad7606_douta;
			ad_valueB[12] <= _ad7606_doutb;
		end
		
		9:
		begin
			ad_valueA[11] <= _ad7606_douta;
			ad_valueB[11] <= _ad7606_doutb;
		end
		
		11:
		begin
			ad_valueA[10] <= _ad7606_douta;
			ad_valueB[10] <= _ad7606_doutb;
		end
		
		13:
		begin
			ad_valueA[9] <= _ad7606_douta;
			ad_valueB[9] <= _ad7606_doutb;
		end
		
		15:
		begin
			ad_valueA[8] <= _ad7606_douta;
			ad_valueB[8] <= _ad7606_doutb;
		end
		
		17:
		begin
			ad_valueA[7] <= _ad7606_douta;
			ad_valueB[7] <= _ad7606_doutb;
		end
		
		19:
		begin
			ad_valueA[6] <= _ad7606_douta;
			ad_valueB[6] <= _ad7606_doutb;
		end
		
		21:
		begin
			ad_valueA[5] <= _ad7606_douta;
			ad_valueB[5] <= _ad7606_doutb;
		end
		
		23:
		begin
			ad_valueA[4] <= _ad7606_douta;
			ad_valueB[4] <= _ad7606_doutb;
		end
		
		25:
		begin
			ad_valueA[3] <= _ad7606_douta;
			ad_valueB[3] <= _ad7606_doutb;
		end
		
		27:
		begin
			ad_valueA[2] <= _ad7606_douta;
			ad_valueB[2] <= _ad7606_doutb;
		end
		
		29:
		begin
			ad_valueA[1] <= _ad7606_douta;
			ad_valueB[1] <= _ad7606_doutb;
		end
		
		31:
		begin
			ad_valueA[0] <= _ad7606_douta;
			ad_valueB[0] <= _ad7606_doutb;
		end
	//*/
		32:
		begin
			ad7606_dataA[chAddr] <= ad_valueA;
			ad7606_dataB[chAddr] <= ad_valueB;
		end
		
		default:
		begin 
		
		end

	endcase
end		






endmodule 



