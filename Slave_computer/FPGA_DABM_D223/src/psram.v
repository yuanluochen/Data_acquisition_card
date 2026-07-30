`timescale 1ns/1ns
//每次读写8个长度各2字节的adc, 共16字节,32个SCLK
module psram( 
	
	output reg  psram_cs,
	output reg	psram_sck,
	inout[3:0]psram_io,
	
	input [23:0]psram_rw_addr,
	
	input [15:0]psram_inData1,
	input [15:0]psram_inData2,
	input [15:0]psram_inData3,
	input [15:0]psram_inData4,
	input [15:0]psram_inData5,
	input [15:0]psram_inData6,
	input [15:0]psram_inData7,
	input [15:0]psram_inData8,

	input read_write_Enable,
	input psram_init,
	input [7:0]writeAdcChEnable,
	input i_clk,
	input rst_n
	);

assign psram_io[0] = (qspi_io_dir[0] == 0) ? 1'bz : psram_io_outBuf[0];
assign psram_io[1] = (qspi_io_dir[1] == 0) ? 1'bz : psram_io_outBuf[1];
assign psram_io[2] = (qspi_io_dir[2] == 0) ? 1'bz : psram_io_outBuf[2];
assign psram_io[3] = (qspi_io_dir[3] == 0) ? 1'bz : psram_io_outBuf[3];

reg [15:0]psram_dataBuf;		
reg [15:0]psram_inDataBuf[0:7];		
reg [3:0]psram_io_outBuf;		
reg [7:0]psram_clk_tick;		
reg [3:0]qspi_io_dir;		
		
wire [7:0]PSRAM_REG_QSPI_ENABLE;		
wire [7:0]PSRAM_REG_QSPI_READ;		
wire [7:0]PSRAM_REG_QSPI_WRITE;		
assign PSRAM_REG_QSPI_ENABLE = 'h35;
assign PSRAM_REG_QSPI_READ = 'hEB;
assign PSRAM_REG_QSPI_WRITE = 'h38;

localparam QSPI_CLK_MAX  = 130;
localparam PSRAM_WORK_MODE_INIT  = 'd0;
localparam PSRAM_WORK_MODE_QSPI_NORMAL  = 'd1;
reg reg_psram_init;
reg [23:0]psram_rw_addr_buf;
//reg psram_sck_div;
always@(posedge i_clk) 
if (!rst_n)
begin 	

end 
else //if(psram_sck_div)
begin 
//psram_sck_div<=0;
	if(psram_clk_tick == QSPI_CLK_MAX)
	begin
		psram_clk_tick <= psram_clk_tick;	//加满不再加,限制上限
		
		if(psram_init)
		begin
			reg_psram_init <= 1;
			psram_clk_tick <= 0;
		end
		else if(read_write_Enable)	//如果已经写完,且外部提供写使能,则开始写,未写完不响应
		begin
			psram_clk_tick <= 0;	//开始写, 时间轴清零
			reg_psram_init <= 0;

			psram_inDataBuf[0] <=  psram_inData1;
			psram_inDataBuf[1] <=  psram_inData2;
			psram_inDataBuf[2] <=  psram_inData3;
			psram_inDataBuf[3] <=  psram_inData4;
			psram_inDataBuf[4] <=  psram_inData5;
			psram_inDataBuf[5] <=  psram_inData6;
			psram_inDataBuf[6] <=  psram_inData7;
			psram_inDataBuf[7] <=  psram_inData8;
			
			psram_rw_addr_buf <= psram_rw_addr;
		end
	end
	else
	begin
		psram_clk_tick <= psram_clk_tick + 'd1;	//psram clk计数器累加
	end
end


always@(posedge i_clk) 
if (!rst_n)
begin 	
	psram_cs <= 'b1;
	psram_sck <= 'b0;
end 
else 
begin 
	if (reg_psram_init)	
	begin
		case (psram_clk_tick)	
			//下降沿推送adc数据, 上升沿锁fpga存数据
			//cs下降沿推送数据
			//开启QSPI指令为0x35,即'b00110101
			'd0:
			begin
				psram_cs <= 'b0;
				psram_sck <= 'b0;
			end
			'd1,'d3,'d5,'d7,'d9,'d11,'d13,'d15:
			begin
				psram_cs <= 'b0;
				psram_sck <= 'b0;
				qspi_io_dir = 'b0001;//0为高阻输入 ,1为输出写psram
			end
			
			//上升沿给PSRAM锁存数据
			'd2 ,'d4 ,'d6 ,'d8 ,'d10,'d12,'d14,'d16:
			begin 	
				qspi_io_dir = 'b0001;//0为高阻输入 ,1为输出写psram
				psram_cs <= 'b0;
				psram_sck  <= 'b1;
			end 			
			
			default:
			begin
				qspi_io_dir = 0;//0为高阻输入 ,1为输出写psram
				psram_cs <= 'b1;
				psram_sck <= 'b0;
			end
		endcase
	end	
	else
	begin
		case (psram_clk_tick)	
			//下降沿推送adc数据, 上升沿锁fpga存数据
			//cs下降沿推送数据
			//开启QSPI指令为0x35,即'b00110101
			'd0:
			begin
				psram_cs <= 'b0;
				psram_sck <= 'b0;
			end

			1,3,
			5,7,9,11,13,15,
			17,19,21,23,
			25,27,29,31,
			33,35,37,39,
			41,43,45,47,
			49,51,53,55,
			57,59,61,63,
			65,67,69,71,
			73,75,77,79:
			begin
				qspi_io_dir <= 'b1111;//io 0为高阻输入 ,1为输出写psram
				psram_cs <= 'b0;
				psram_sck <= 'b0;
			end

		//上升沿给PSRAM锁存数据
			2,4,
			6,8,10,12,14,16:
			begin
				psram_sck  <= 'b1;
			end 	
			
			18,20,22,24:
			begin
				if(writeAdcChEnable[0])
				begin
					psram_sck  <= 'b1;
				end
			end 	
			26,28,30,32:
			begin
				if(writeAdcChEnable[1])
				begin
					psram_sck  <= 'b1;
				end
			end 	
			34,36,38,40:
			begin
				if(writeAdcChEnable[2])
				begin
					psram_sck  <= 'b1;
				end
			end 	
			42,44,46,48:
			begin
				if(writeAdcChEnable[3])
				begin
					psram_sck  <= 'b1;
				end
			end 	
			50,52,54,56:
			begin
				if(writeAdcChEnable[4])
				begin
					psram_sck  <= 'b1;
				end
			end 	
			58,60,62,64:
			begin
				if(writeAdcChEnable[5])
				begin
					psram_sck  <= 'b1;
				end
			end 	
			66,68,70,72:
			begin
				if(writeAdcChEnable[6])
				begin
					psram_sck  <= 'b1;
				end
			end 	
			74,76,78,80:
			begin
				if(writeAdcChEnable[7])
				begin
					psram_sck  <= 'b1;
				end
			end 	
			
			default:
			begin
				qspi_io_dir <= 0;//io 0为高阻输入 ,1为输出写psram
				psram_cs <= 'b1;
				psram_sck <= 'b0;
			end
		endcase
	end
end	

always@(posedge i_clk) 
if (!rst_n)
begin 	

end 
else 
begin 
		if(reg_psram_init)	
		begin
			case (psram_clk_tick)	
				//下降沿推送adc数据, 上升沿锁fpga存数据
				//cs下降沿推送数据
				//开启QSPI指令为0x35,即'b00110101
				'd0:
				begin
					psram_io_outBuf[0]  <= 'b0;
				end
				'd1,'d3,'d5,'d7,'d9,'d11,'d13,'d15:
				begin
					psram_io_outBuf[0]  <= PSRAM_REG_QSPI_ENABLE['d7 - psram_clk_tick[7:1]];
					
				end
				
				default:
				begin
					
				end
			endcase
		end	
		else
		begin
				case (psram_clk_tick)	
					//下降沿推送adc数据, 上升沿锁fpga存数据
					//cs下降沿推送数据
					//开启QSPI指令为0x35,即'b00110101
					1:
					begin
						psram_io_outBuf[3]  <= PSRAM_REG_QSPI_WRITE[7];
						psram_io_outBuf[2]  <= PSRAM_REG_QSPI_WRITE[6];
						psram_io_outBuf[1]  <= PSRAM_REG_QSPI_WRITE[5];
						psram_io_outBuf[0]  <= PSRAM_REG_QSPI_WRITE[4];
					end
					
					3:
					begin
						psram_io_outBuf[3]  <= PSRAM_REG_QSPI_WRITE[3];
						psram_io_outBuf[2]  <= PSRAM_REG_QSPI_WRITE[2];
						psram_io_outBuf[1]  <= PSRAM_REG_QSPI_WRITE[1];
						psram_io_outBuf[0]  <= PSRAM_REG_QSPI_WRITE[0];
					end

					//写入地址 PSRAM_REG_QSPI_WRITE
					5:
					begin
						psram_io_outBuf[3]  <= psram_rw_addr_buf[23];
						psram_io_outBuf[2]  <= psram_rw_addr_buf[22];
						psram_io_outBuf[1]  <= psram_rw_addr_buf[21];
						psram_io_outBuf[0]  <= psram_rw_addr_buf[20];
					end
					//写入地址 PSRAM_REG_QSPI_WRITE
					7:
					begin
						psram_io_outBuf[3]  <= psram_rw_addr_buf[19];
						psram_io_outBuf[2]  <= psram_rw_addr_buf[18];
						psram_io_outBuf[1]  <= psram_rw_addr_buf[17];
						psram_io_outBuf[0]  <= psram_rw_addr_buf[16];
					end
					//写入地址 PSRAM_REG_QSPI_WRITE
					9:
					begin
						psram_io_outBuf[3]  <= psram_rw_addr_buf[15];
						psram_io_outBuf[2]  <= psram_rw_addr_buf[14];
						psram_io_outBuf[1]  <= psram_rw_addr_buf[13];
						psram_io_outBuf[0]  <= psram_rw_addr_buf[12];
					end
					//写入地址 PSRAM_REG_QSPI_WRITE
					11:
					begin
						psram_io_outBuf[3]  <= psram_rw_addr_buf[11];
						psram_io_outBuf[2]  <= psram_rw_addr_buf[10];
						psram_io_outBuf[1]  <= psram_rw_addr_buf[9];
						psram_io_outBuf[0]  <= psram_rw_addr_buf[8];
					end
					//写入地址 PSRAM_REG_QSPI_WRITE
					13:
					begin
						psram_io_outBuf[3]  <= psram_rw_addr_buf[7];
						psram_io_outBuf[2]  <= psram_rw_addr_buf[6];
						psram_io_outBuf[1]  <= psram_rw_addr_buf[5];
						psram_io_outBuf[0]  <= psram_rw_addr_buf[4];
					end
					//写入地址 PSRAM_REG_QSPI_WRITE
					15:
					begin
						psram_io_outBuf[3]  <= psram_rw_addr_buf[3];
						psram_io_outBuf[2]  <= psram_rw_addr_buf[2];
						psram_io_outBuf[1]  <= psram_rw_addr_buf[1];
						psram_io_outBuf[0]  <= psram_rw_addr_buf[0];
					end
					
					//写入8个adc数据,每个数据需要4个clk
					//推送data1
					17:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[0][15];
						psram_io_outBuf[2]  <= psram_inDataBuf[0][14];
						psram_io_outBuf[1]  <= psram_inDataBuf[0][13];
						psram_io_outBuf[0]  <= psram_inDataBuf[0][12];
					end
					19:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[0][11];
						psram_io_outBuf[2]  <= psram_inDataBuf[0][10];
						psram_io_outBuf[1]  <= psram_inDataBuf[0][9];
						psram_io_outBuf[0]  <= psram_inDataBuf[0][8];
					end
					21:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[0][7];
						psram_io_outBuf[2]  <= psram_inDataBuf[0][6];
						psram_io_outBuf[1]  <= psram_inDataBuf[0][5];
						psram_io_outBuf[0]  <= psram_inDataBuf[0][4];
					end
					23:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[0][3];
						psram_io_outBuf[2]  <= psram_inDataBuf[0][2];
						psram_io_outBuf[1]  <= psram_inDataBuf[0][1];
						psram_io_outBuf[0]  <= psram_inDataBuf[0][0];
					end
					
					//推送data2
					25:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[1][15];
						psram_io_outBuf[2]  <= psram_inDataBuf[1][14];
						psram_io_outBuf[1]  <= psram_inDataBuf[1][13];
						psram_io_outBuf[0]  <= psram_inDataBuf[1][12];
					end
					27:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[1][11];
						psram_io_outBuf[2]  <= psram_inDataBuf[1][10];
						psram_io_outBuf[1]  <= psram_inDataBuf[1][9];
						psram_io_outBuf[0]  <= psram_inDataBuf[1][8];
					end
					29:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[1][7];
						psram_io_outBuf[2]  <= psram_inDataBuf[1][6];
						psram_io_outBuf[1]  <= psram_inDataBuf[1][5];
						psram_io_outBuf[0]  <= psram_inDataBuf[1][4];
					end
					31:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[1][3];
						psram_io_outBuf[2]  <= psram_inDataBuf[1][2];
						psram_io_outBuf[1]  <= psram_inDataBuf[1][1];
						psram_io_outBuf[0]  <= psram_inDataBuf[1][0];
					end
					
					//推送data3
					33:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[2][15];
						psram_io_outBuf[2]  <= psram_inDataBuf[2][14];
						psram_io_outBuf[1]  <= psram_inDataBuf[2][13];
						psram_io_outBuf[0]  <= psram_inDataBuf[2][12];
					end
					35:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[2][11];
						psram_io_outBuf[2]  <= psram_inDataBuf[2][10];
						psram_io_outBuf[1]  <= psram_inDataBuf[2][9];
						psram_io_outBuf[0]  <= psram_inDataBuf[2][8];
					end
					37:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[2][7];
						psram_io_outBuf[2]  <= psram_inDataBuf[2][6];
						psram_io_outBuf[1]  <= psram_inDataBuf[2][5];
						psram_io_outBuf[0]  <= psram_inDataBuf[2][4];
					end
					39:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[2][3];
						psram_io_outBuf[2]  <= psram_inDataBuf[2][2];
						psram_io_outBuf[1]  <= psram_inDataBuf[2][1];
						psram_io_outBuf[0]  <= psram_inDataBuf[2][0];
					end
					
					//推送data4
					41:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[3][15];
						psram_io_outBuf[2]  <= psram_inDataBuf[3][14];
						psram_io_outBuf[1]  <= psram_inDataBuf[3][13];
						psram_io_outBuf[0]  <= psram_inDataBuf[3][12];
					end
					43:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[3][11];
						psram_io_outBuf[2]  <= psram_inDataBuf[3][10];
						psram_io_outBuf[1]  <= psram_inDataBuf[3][9];
						psram_io_outBuf[0]  <= psram_inDataBuf[3][8];
					end
					45:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[3][7];
						psram_io_outBuf[2]  <= psram_inDataBuf[3][6];
						psram_io_outBuf[1]  <= psram_inDataBuf[3][5];
						psram_io_outBuf[0]  <= psram_inDataBuf[3][4];
					end
					47:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[3][3];
						psram_io_outBuf[2]  <= psram_inDataBuf[3][2];
						psram_io_outBuf[1]  <= psram_inDataBuf[3][1];
						psram_io_outBuf[0]  <= psram_inDataBuf[3][0];
					end
					
					//推送data5
					49:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[4][15];
						psram_io_outBuf[2]  <= psram_inDataBuf[4][14];
						psram_io_outBuf[1]  <= psram_inDataBuf[4][13];
						psram_io_outBuf[0]  <= psram_inDataBuf[4][12];
					end
					51:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[4][11];
						psram_io_outBuf[2]  <= psram_inDataBuf[4][10];
						psram_io_outBuf[1]  <= psram_inDataBuf[4][9];
						psram_io_outBuf[0]  <= psram_inDataBuf[4][8];
					end
					53:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[4][7];
						psram_io_outBuf[2]  <= psram_inDataBuf[4][6];
						psram_io_outBuf[1]  <= psram_inDataBuf[4][5];
						psram_io_outBuf[0]  <= psram_inDataBuf[4][4];
					end
					55:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[4][3];
						psram_io_outBuf[2]  <= psram_inDataBuf[4][2];
						psram_io_outBuf[1]  <= psram_inDataBuf[4][1];
						psram_io_outBuf[0]  <= psram_inDataBuf[4][0];
					end
					
					//推送data6
					57:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[5][15];
						psram_io_outBuf[2]  <= psram_inDataBuf[5][14];
						psram_io_outBuf[1]  <= psram_inDataBuf[5][13];
						psram_io_outBuf[0]  <= psram_inDataBuf[5][12];
					end
					59:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[5][11];
						psram_io_outBuf[2]  <= psram_inDataBuf[5][10];
						psram_io_outBuf[1]  <= psram_inDataBuf[5][9];
						psram_io_outBuf[0]  <= psram_inDataBuf[5][8];
					end
					61:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[5][7];
						psram_io_outBuf[2]  <= psram_inDataBuf[5][6];
						psram_io_outBuf[1]  <= psram_inDataBuf[5][5];
						psram_io_outBuf[0]  <= psram_inDataBuf[5][4];
					end
					63:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[5][3];
						psram_io_outBuf[2]  <= psram_inDataBuf[5][2];
						psram_io_outBuf[1]  <= psram_inDataBuf[5][1];
						psram_io_outBuf[0]  <= psram_inDataBuf[5][0];
					end
					
					//推送data7
					65:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[6][15];
						psram_io_outBuf[2]  <= psram_inDataBuf[6][14];
						psram_io_outBuf[1]  <= psram_inDataBuf[6][13];
						psram_io_outBuf[0]  <= psram_inDataBuf[6][12];
					end
					67:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[6][11];
						psram_io_outBuf[2]  <= psram_inDataBuf[6][10];
						psram_io_outBuf[1]  <= psram_inDataBuf[6][9];
						psram_io_outBuf[0]  <= psram_inDataBuf[6][8];
					end
					69:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[6][7];
						psram_io_outBuf[2]  <= psram_inDataBuf[6][6];
						psram_io_outBuf[1]  <= psram_inDataBuf[6][5];
						psram_io_outBuf[0]  <= psram_inDataBuf[6][4];
					end
					71:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[6][3];
						psram_io_outBuf[2]  <= psram_inDataBuf[6][2];
						psram_io_outBuf[1]  <= psram_inDataBuf[6][1];
						psram_io_outBuf[0]  <= psram_inDataBuf[6][0];
					end
					
					//推送data8
					73:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[7][15];
						psram_io_outBuf[2]  <= psram_inDataBuf[7][14];
						psram_io_outBuf[1]  <= psram_inDataBuf[7][13];
						psram_io_outBuf[0]  <= psram_inDataBuf[7][12];
					end
					75:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[7][11];
						psram_io_outBuf[2]  <= psram_inDataBuf[7][10];
						psram_io_outBuf[1]  <= psram_inDataBuf[7][9];
						psram_io_outBuf[0]  <= psram_inDataBuf[7][8];
					end
					77:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[7][7];
						psram_io_outBuf[2]  <= psram_inDataBuf[7][6];
						psram_io_outBuf[1]  <= psram_inDataBuf[7][5];
						psram_io_outBuf[0]  <= psram_inDataBuf[7][4];
					end
					79:
					begin
						psram_io_outBuf[3]  <= psram_inDataBuf[7][3];
						psram_io_outBuf[2]  <= psram_inDataBuf[7][2];
						psram_io_outBuf[1]  <= psram_inDataBuf[7][1];
						psram_io_outBuf[0]  <= psram_inDataBuf[7][0];
					end
					
				endcase
		end
end	











endmodule 





