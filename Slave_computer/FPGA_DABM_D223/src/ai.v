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

//==========================================
// 时钟和复位
//==========================================
wire clk_pllOut1;
wire pll_lock;
wire pll_ok;

Gowin_rPLL pll_u1(
    .clkout(clk_pllOut1),
    .lock(pll_lock),
    .reset(!RST_N),
    .clkin(CLK_25M)
);

assign pll_ok = pll_lock;

//对接SPI接口
wire [3:0]psram_io_u1_a;

// SPI边沿检测优化 - 减少组合逻辑
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
reg [7:0]reg_cmdA2FBuf[0:10];
reg [7:0]reg_cmdF2ABuf[0:3];
wire [3:0]qspi_io_mode1;
wire [3:0]qspi_io_mode2;

// 寄存器数据映射
reg [7:0]reg_a2f_sram_workEnable;
reg [7:0]reg_a2f_sram_extTrig;
reg [23:0]reg_sram_recordMaxLen;
reg [23:0]reg_adc_sample_cycleMax;
reg [7:0]reg_a2f_sram_adcChEnable;
reg [7:0]reg_a2f_sram_adcChEnableTotal;

reg [7:0]reg_f2a_sramDataBufTick;
wire [7:0]din_buf;
assign din_buf = ~i_din;

// 寄存器更新流水线优化
reg [7:0]reg_cmdA2FBuf_sync[0:10];
reg spi_cs_sync;
always @(posedge clk_pllOut1) begin
    spi_cs_sync <= spi_cs;
end

always @ (posedge clk_pllOut1) begin
    if(!pll_lock) begin
        reg_sram_recordMaxLen <= 0;
    end
    else if(spi_cs_sync) begin
        reg_a2f_sram_workEnable <= reg_cmdA2FBuf_sync[`REG_SRAM_WORK_STATE1];
        reg_a2f_sram_extTrig <= reg_cmdA2FBuf_sync[`REG_SRAM_WORK_STATE2];
        
        reg_sram_recordMaxLen <= {reg_cmdA2FBuf_sync[`REG_SRAM_RECORD_MAX_LEN3],
                                  reg_cmdA2FBuf_sync[`REG_SRAM_RECORD_MAX_LEN2],
                                  reg_cmdA2FBuf_sync[`REG_SRAM_RECORD_MAX_LEN1]};
                                  
        reg_adc_sample_cycleMax <= {reg_cmdA2FBuf_sync[`REG_FPGA_ADC_SAMPLE_CYCLE_MAX3],
                                    reg_cmdA2FBuf_sync[`REG_FPGA_ADC_SAMPLE_CYCLE_MAX2],
                                    reg_cmdA2FBuf_sync[`REG_FPGA_ADC_SAMPLE_CYCLE_MAX1]};
                                    
        reg_a2f_sram_adcChEnable <= reg_cmdA2FBuf_sync[`REG_FPGA_ADC_CH_ENABLE];
        reg_a2f_sram_adcChEnableTotal <= reg_cmdA2FBuf_sync[`REG_FPGA_ADC_CH_ENABLE_TOTAL];
        
        reg_cmdF2ABuf[`REG_SRAM_WORK_STATE1] <= reg_cmdA2FBuf_sync[`REG_SRAM_WORK_STATE1];
        reg_cmdF2ABuf[`REG_SRAM_WORK_STATE2] <= reg_f2a_sramDataBufTick;
        reg_cmdF2ABuf[`REG_DIN] <= din_buf;
    end
end

// 主状态解码
wire MODE_FPGA_STOP = (reg_a2f_sram_workEnable == 0);
wire MODE_FPGA_WRITE = (reg_a2f_sram_workEnable == 1);
wire MODE_STM32_READ_PSRAM = (reg_a2f_sram_workEnable == 2);
wire MODE_STM32_READ_FIFO = (reg_a2f_sram_workEnable == 3);
wire MODE_PSRAM_INIT = (reg_a2f_sram_workEnable == 'hff);

wire MODE_FPGA_EXT_IO_TRIG = (reg_a2f_sram_extTrig == 1);
wire MODE_FPGA_EXT_VOLT_TRIG_POS = (reg_a2f_sram_extTrig == 2);
wire MODE_FPGA_EXT_VOLT_TRIG_NEG = (reg_a2f_sram_extTrig == 3);

// PSRAM IO控制 - 寄存器输出优化
reg [3:0] psram_io_a_reg;
reg psram_cs_a_reg;
reg psram_sck_a_reg;
reg [3:0] qspi_io_reg;
reg qspi_io_oe;

// 预计算模式条件
wire mode_write_or_init = MODE_FPGA_WRITE | MODE_PSRAM_INIT;
wire mode_read_psram_and_not_dir = MODE_STM32_READ_PSRAM && !qspi_dir;
wire mode_read_psram_and_dir = MODE_STM32_READ_PSRAM && qspi_dir;
wire mode_read_fifo_and_dir = MODE_STM32_READ_FIFO && qspi_dir;

always @(posedge clk_pllOut1 or negedge pll_lock) begin
    if(!pll_lock) begin
        psram_io_a_reg <= 4'hz;
        psram_cs_a_reg <= 1'b1;
        psram_sck_a_reg <= 1'b0;
        qspi_io_reg <= 4'hz;
        qspi_io_oe <= 1'b0;
    end
    else begin
        // PSRAM IO控制
        if(mode_write_or_init) begin
            psram_io_a_reg <= psram_io_u1_a;
        end
        else if(mode_read_psram_and_not_dir) begin
            psram_io_a_reg <= qspi_io;
        end
        else begin
            psram_io_a_reg <= 4'hz;
        end
        
        // PSRAM CS/SCK控制
        psram_cs_a_reg <= MODE_STM32_READ_PSRAM ? qspi_cs : psram_cs_u1_a;
        psram_sck_a_reg <= MODE_STM32_READ_PSRAM ? qspi_sck : psram_sck_u1_a;
        
        // QSPI IO控制
        if(mode_read_psram_and_dir) begin
            qspi_io_reg <= psram_io_a;
            qspi_io_oe <= 1'b1;
        end
        else if(mode_read_fifo_and_dir) begin
            qspi_io_reg <= qspi_rd_hl ? qspi_io_outBuf[7:4] : qspi_io_outBuf[3:0];
            qspi_io_oe <= 1'b1;
        end
        else begin
            qspi_io_reg <= 4'hz;
            qspi_io_oe <= 1'b0;
        end
    end
end

assign psram_io_a = psram_io_a_reg;
assign psram_cs_a = psram_cs_a_reg;
assign psram_sck_a = psram_sck_a_reg;
assign qspi_io = qspi_io_oe ? qspi_io_reg : 4'hz;

wire [15:0]ad7606_data[0:15];
wire ad_update_Flag;
reg [23:0]psram_rwIndex;
reg [23:0]psram_rwIndex_d;

// 触发检测优化
reg adc_trig;
reg [2:0]adc_trig_edge;
always @ (posedge clk_pllOut1) begin
    if(!pll_lock) begin
        adc_trig_edge <= 0;
    end
    else begin
        adc_trig_edge <= {adc_trig_edge[1:0], din_buf[7]};
    end
end

always @ (posedge clk_pllOut1) begin
    if(!pll_lock) begin
        adc_trig <= 0;
    end
    else begin
        adc_trig <= (adc_trig_edge[1:0] == 2'b01) || (adc_trig_edge[1:0] == 2'b11);
    end
end

reg psram_writeEnable;
reg reg_f2a_sramDataBufFlag;

// 预计算比较结果优化时序
reg [23:0]psram_limit;
reg compare_result;
always @(posedge clk_pllOut1) begin
    if(!pll_lock) begin
        psram_limit <= 24'd8_380_000;
    end
    else begin
        psram_limit <= 24'd8_380_000;
    end
end

always @(posedge clk_pllOut1) begin
    if(!pll_lock) begin
        compare_result <= 1'b0;
    end
    else begin
        compare_result <= (psram_rwIndex < psram_limit) && (psram_rwIndex <= reg_sram_recordMaxLen);
    end
end

always @ (posedge clk_pllOut1) begin
    if(!pll_lock) begin
        psram_rwIndex <= 0;
        psram_rwIndex_d <= 0;
        psram_writeEnable <= 0;
        reg_f2a_sramDataBufTick <= 0;
        reg_f2a_sramDataBufFlag <= 0;
    end
    else if(MODE_FPGA_STOP) begin
        psram_rwIndex <= 0;	
        psram_rwIndex_d <= 0;	
        psram_writeEnable <= 0;	
    end
    else if(MODE_FPGA_WRITE) begin
        if(compare_result) begin
            if(ad_update_Flag) begin
                psram_rwIndex_d <= psram_rwIndex;
                psram_writeEnable <= 1;	
            end
            else if(psram_writeEnable) begin
                psram_rwIndex <= psram_rwIndex_d + reg_a2f_sram_adcChEnableTotal;
                psram_writeEnable <= 0;	
            end
            reg_f2a_sramDataBufFlag <= 1;
        end
        else if(reg_f2a_sramDataBufFlag == 1) begin
            reg_f2a_sramDataBufTick <= reg_f2a_sramDataBufTick + 1;
            reg_f2a_sramDataBufFlag <= 0;
        end
        else if(adc_trig) begin
            psram_rwIndex <= 0;	
            psram_rwIndex_d <= 0;	
            psram_writeEnable <= 0;	
        end
    end
end

// SPI接口驱动优化
wire spi_sck_rise;
wire spi_sck_fall;
reg [2:0]spi_sck_sync;

always @(posedge clk_pllOut1) begin
    if(!pll_lock) begin
        spi_sck_sync <= 3'b111;
    end
    else begin
        spi_sck_sync <= {spi_sck_sync[1:0], spi_sck};
    end
end

assign spi_sck_rise = (spi_sck_sync[1:0] == 2'b01);
assign spi_sck_fall = (spi_sck_sync[1:0] == 2'b10);

always @ (posedge clk_pllOut1) begin
    if(!pll_lock) begin
        spi_sck_edge <= 'b111;
    end
    else begin
        spi_sck_edge <= {spi_sck_edge[1:0], spi_sck};
    end
end

always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (spi_cs_sync == 1'b1)) begin
        spi_reg_index <= 0;
        spi_reg_index_d <= 0;	
    end
    else begin
        if((spi_sck_tick == 1) && spi_reg_index_enable) begin
            spi_reg_index <= spi_reg_index_d + 1'd1;
        end
        else begin
            spi_reg_index_d <= spi_reg_index;
        end
    end
end

// SPI计数优化
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (spi_cs_sync == 1'b1)) begin
        spi_sck_tick <= 1'd0;	
        spi_sck_tick_d <= 1'd0;	
        spi_reg_index_enable <= 0;
    end
    else if({spi_sck_edge[2:0], spi_sck} == 0) begin
        if(spi_sck_tick == 9) begin
            spi_reg_index_enable <= 1;
            spi_sck_tick <= 1;
            spi_sck_tick_d <= 0;
        end
        else begin
            spi_sck_tick <= spi_sck_tick_d + 1'd1;
        end
    end
    else begin
        spi_sck_tick_d <= spi_sck_tick;
    end		
end

// SPI通信寄存器地址累加
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (spi_cs_sync == 1'b1)) begin
        arm_spiRx_Buf <= 0;
        spi_cmd <= 0;
        spi_reg_start_addr <= 0;
    end
    else if(spi_sck_rise) begin
        if((spi_sck_tick != 9) && (spi_sck_tick != 0)) begin
            arm_spiRx_Buf[8-spi_sck_tick] <= spi_mosi;
        end
    end
    else if(spi_sck_fall && (spi_sck_tick == 8)) begin
        if(spi_reg_index == 0) begin
            spi_cmd <= arm_spiRx_Buf;
        end
        else if(spi_cmd == 'h80) begin
            if(spi_reg_index == 1) begin
                spi_reg_start_addr <= arm_spiRx_Buf;
            end
            else begin
                reg_cmdA2FBuf_sync[spi_reg_start_addr + spi_reg_index - 2] <= arm_spiRx_Buf;
            end
        end
        else if(spi_cmd == 'h00) begin
            if(spi_reg_index == 1) begin
                spi_reg_start_addr <= arm_spiRx_Buf;
            end
        end
    end
    else if(spi_sck_fall) begin
        if(spi_sck_tick == 8) begin
            spi_io_outBuf <= reg_cmdF2ABuf[spi_reg_start_addr + spi_reg_index - 1];
        end
        spi_miso <= spi_io_outBuf[7-spi_sck_tick];
    end
end

// QSPI接口变量
reg qspi_dir;
reg [15:0]qspi_sck_tick;
reg [15:0]qspi_sck_tick_d;
reg [1:0]qspi_sck_edge;
reg [7:0]arm_qspiRx_Buf;
reg [7:0]qspi_io_outBuf;
reg [7:0]qspi_cmd;
reg [15:0]qspi_reg_start_addr;
reg [15:0]qspi_reg_rw_addr;
reg [15:0]qspi_reg_rw_addr_d;
reg qspi_reg_index_enable;
reg qspi_rd_hl;

reg [2:0]psram_rw_Finish_pos_tick;
reg psram_readWrite_flag;
reg [23:0]reg_adcSramBuf_indexNow;
reg reg_psram_read_write_dir;
reg [23:0]psramSaveAddrIndex;
reg [23:0]psramReadAddrIndex;
reg [7:0]reg_adcBuf[0:16];
reg [7:0]reg_adcBuf_10history[0:65];
reg [7:0]reg_adcBuf_10history_tick;
reg [7:0]reg_adcBuf_10history_tick_d;

// QSPI边沿检测
wire qspi_sck_rise;
wire qspi_sck_fall;
reg [1:0]qspi_sck_sync;

always @(posedge clk_pllOut1) begin
    if(!pll_lock) begin
        qspi_sck_sync <= 2'b00;
    end
    else begin
        qspi_sck_sync <= {qspi_sck_sync[0], qspi_sck};
    end
end

assign qspi_sck_rise = (qspi_sck_sync == 2'b01);
assign qspi_sck_fall = (qspi_sck_sync == 2'b10);

always @(posedge clk_pllOut1) begin
    if(!pll_lock) begin
        qspi_sck_edge <= 'b0;
    end
    else begin
        qspi_sck_edge <= {qspi_sck_edge[0], qspi_sck};
    end
end

// QSPI方向控制
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (qspi_cs == 1'b1)) begin
        qspi_dir <= 0;
    end
    else if(MODE_STM32_READ_PSRAM) begin
        if(qspi_sck_tick >= 9) begin
            qspi_dir <= 1;
        end
    end
    else if(MODE_STM32_READ_FIFO) begin
        if(qspi_sck_tick >= 9) begin
            qspi_dir <= qspi_cmd[7];
        end	
    end
end

// QSPI计数
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (qspi_cs == 1'b1)) begin
        qspi_sck_tick <= 1'd0;	
        qspi_sck_tick_d <= 1'd0;	
    end
    else begin
        if(qspi_sck_rise || qspi_sck_fall) begin
            qspi_sck_tick <= qspi_sck_tick_d + 1'd1;
        end
        else begin
            qspi_sck_tick_d <= qspi_sck_tick;
        end
    end
end

// QSPI发送数据
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (qspi_cs == 1'b1)) begin
        qspi_io_outBuf <= 0;
    end
    else if((qspi_cs == 1'b0) && (qspi_dir == 1) && MODE_STM32_READ_FIFO) begin
        if(qspi_sck_fall) begin
            if(qspi_sck_tick[0] == 0) begin
                if(qspi_sck_tick > 'd8) begin
                    if(qspi_cmd == 'h80) begin
                        if(qspi_reg_rw_addr <= 16) begin
                            qspi_io_outBuf <= reg_adcBuf[qspi_reg_rw_addr];
                        end
                    end
                    else if(qspi_cmd == 'h81) begin
                        if(qspi_reg_rw_addr <= 65) begin
                            qspi_io_outBuf <= reg_adcBuf_10history[qspi_reg_rw_addr];
                        end
                    end
                end
            end
        end
    end
end

// QSPI命令地址提取
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (qspi_cs == 1'b1)) begin
        qspi_cmd <= 0;
        qspi_reg_start_addr <= 0;
    end
    else if(MODE_STM32_READ_FIFO) begin
        if(qspi_sck_rise) begin
            if(qspi_sck_tick == 2) begin
                qspi_cmd <= arm_qspiRx_Buf;
            end
            else if(qspi_sck_tick == 6) begin
                qspi_reg_start_addr[15:8] <= arm_qspiRx_Buf;
            end
            else if(qspi_sck_tick == 8) begin
                qspi_reg_start_addr[7:0] <= arm_qspiRx_Buf;
            end
        end
    end
end

// QSPI地址累加
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (qspi_cs == 1'b1)) begin
        qspi_reg_rw_addr_d <= 0;
        qspi_reg_rw_addr <= 0;
    end
    else if(qspi_reg_index_enable) begin
        if(qspi_sck_rise) begin
            if(qspi_sck_tick[0]) begin
                qspi_reg_rw_addr <= qspi_reg_rw_addr_d + 'd1;
            end
        end
        else begin
            qspi_reg_rw_addr_d <= qspi_reg_rw_addr;
        end
    end
    else begin
        qspi_reg_rw_addr_d <= qspi_reg_start_addr;
        qspi_reg_rw_addr <= qspi_reg_start_addr;
    end
end

// QSPI索引使能
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (qspi_cs == 1'b1) || (!MODE_STM32_READ_FIFO)) begin
        qspi_reg_index_enable <= 0;
    end
    else if(MODE_STM32_READ_FIFO) begin
        if(qspi_sck_fall) begin			
            if(qspi_sck_tick == 0) begin
                qspi_reg_index_enable <= 'b0;
            end	
            else if(qspi_sck_tick == 'd10) begin
                qspi_reg_index_enable <= 'b1;
            end
        end
    end
end

// QSPI高低字节切换
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (qspi_cs == 1'b1)) begin
        qspi_rd_hl <= 'b0;
    end
    else begin
        if(qspi_sck_fall) begin			
            if(qspi_sck_tick[0] == 0) begin
                qspi_rd_hl <= 'b1;
            end
            else begin
                qspi_rd_hl <= 'b0;
            end
        end
    end
end

// QSPI数据接收
always @ (posedge clk_pllOut1) begin
    if((!pll_lock) || (qspi_cs == 1'b1)) begin
        arm_qspiRx_Buf <= 0;
    end
    else if((qspi_cs == 1'b0) && (qspi_dir == 0) && MODE_STM32_READ_FIFO) begin
        if(qspi_sck_rise) begin
            if(qspi_sck_tick[0] == 0) begin
                arm_qspiRx_Buf <= {qspi_io, arm_qspiRx_Buf[3:0]};			
            end
            else begin
                arm_qspiRx_Buf <= {arm_qspiRx_Buf[7:4], qspi_io};
            end
        end
    end
end

// 模块实例化
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
    .i_clk(clk_pllOut1),
    .rst_n(pll_lock)
);

reg adc_fifo_waitQspiRead;
wire [1:0]w_adcBuf_10history_tick;
assign w_adcBuf_10history_tick = reg_adcBuf_10history_tick[1:0];

always@(posedge clk_pllOut1) begin
    if(!pll_lock | MODE_FPGA_STOP) begin 	
        reg_adcBuf_10history_tick <= 0;
        reg_adcBuf_10history_tick_d <= 0;
        adc_fifo_waitQspiRead <= 0;
    end 
    else if(ad_update_Flag) begin
        adc_fifo_waitQspiRead <= 'b1;
        reg_adcBuf_10history_tick <= reg_adcBuf_10history_tick_d;
    end
    else if(!ad_update_Flag & qspi_cs) begin 
        adc_fifo_waitQspiRead <= 'b0;	
        reg_adcBuf[0] <= ad7606_data[0][7:0];
        reg_adcBuf[1] <= ad7606_data[0][15:8];
        reg_adcBuf[2] <= ad7606_data[1][7:0];
        reg_adcBuf[3] <= ad7606_data[1][15:8];
        reg_adcBuf[4] <= ad7606_data[2][7:0];
        reg_adcBuf[5] <= ad7606_data[2][15:8];
        reg_adcBuf[6] <= ad7606_data[3][7:0];
        reg_adcBuf[7] <= ad7606_data[3][15:8];
        reg_adcBuf[8] <= ad7606_data[4][7:0];
        reg_adcBuf[9] <= ad7606_data[4][15:8];
        reg_adcBuf[10] <= ad7606_data[5][7:0];
        reg_adcBuf[11] <= ad7606_data[5][15:8];
        reg_adcBuf[12] <= ad7606_data[6][7:0];
        reg_adcBuf[13] <= ad7606_data[6][15:8];
        reg_adcBuf[14] <= ad7606_data[7][7:0];
        reg_adcBuf[15] <= ad7606_data[7][15:8];
        reg_adcBuf[16] <= din_buf;
        
        case(w_adcBuf_10history_tick)
            'd0: begin
                reg_adcBuf_10history[0] <= ad7606_data[0][7:0];
                reg_adcBuf_10history[1] <= ad7606_data[0][15:8];
                reg_adcBuf_10history[2] <= ad7606_data[1][7:0];
                reg_adcBuf_10history[3] <= ad7606_data[1][15:8];
                reg_adcBuf_10history[4] <= ad7606_data[2][7:0];
                reg_adcBuf_10history[5] <= ad7606_data[2][15:8];
                reg_adcBuf_10history[6] <= ad7606_data[3][7:0];
                reg_adcBuf_10history[7] <= ad7606_data[3][15:8];
                reg_adcBuf_10history[8] <= ad7606_data[4][7:0];
                reg_adcBuf_10history[9] <= ad7606_data[4][15:8];
                reg_adcBuf_10history[10] <= ad7606_data[5][7:0];
                reg_adcBuf_10history[11] <= ad7606_data[5][15:8];
                reg_adcBuf_10history[12] <= ad7606_data[6][7:0];
                reg_adcBuf_10history[13] <= ad7606_data[6][15:8];
                reg_adcBuf_10history[14] <= ad7606_data[7][7:0];
                reg_adcBuf_10history[15] <= ad7606_data[7][15:8];
            end
            'd1: begin
                reg_adcBuf_10history[16] <= ad7606_data[0][7:0];
                reg_adcBuf_10history[17] <= ad7606_data[0][15:8];
                reg_adcBuf_10history[18] <= ad7606_data[1][7:0];
                reg_adcBuf_10history[19] <= ad7606_data[1][15:8];
                reg_adcBuf_10history[20] <= ad7606_data[2][7:0];
                reg_adcBuf_10history[21] <= ad7606_data[2][15:8];
                reg_adcBuf_10history[22] <= ad7606_data[3][7:0];
                reg_adcBuf_10history[23] <= ad7606_data[3][15:8];
                reg_adcBuf_10history[24] <= ad7606_data[4][7:0];
                reg_adcBuf_10history[25] <= ad7606_data[4][15:8];
                reg_adcBuf_10history[26] <= ad7606_data[5][7:0];
                reg_adcBuf_10history[27] <= ad7606_data[5][15:8];
                reg_adcBuf_10history[28] <= ad7606_data[6][7:0];
                reg_adcBuf_10history[29] <= ad7606_data[6][15:8];
                reg_adcBuf_10history[30] <= ad7606_data[7][7:0];
                reg_adcBuf_10history[31] <= ad7606_data[7][15:8];
            end
            'd2: begin
                reg_adcBuf_10history[32] <= ad7606_data[0][7:0];
                reg_adcBuf_10history[33] <= ad7606_data[0][15:8];
                reg_adcBuf_10history[34] <= ad7606_data[1][7:0];
                reg_adcBuf_10history[35] <= ad7606_data[1][15:8];
                reg_adcBuf_10history[36] <= ad7606_data[2][7:0];
                reg_adcBuf_10history[37] <= ad7606_data[2][15:8];
                reg_adcBuf_10history[38] <= ad7606_data[3][7:0];
                reg_adcBuf_10history[39] <= ad7606_data[3][15:8];
                reg_adcBuf_10history[40] <= ad7606_data[4][7:0];
                reg_adcBuf_10history[41] <= ad7606_data[4][15:8];
                reg_adcBuf_10history[42] <= ad7606_data[5][7:0];
                reg_adcBuf_10history[43] <= ad7606_data[5][15:8];
                reg_adcBuf_10history[44] <= ad7606_data[6][7:0];
                reg_adcBuf_10history[45] <= ad7606_data[6][15:8];
                reg_adcBuf_10history[46] <= ad7606_data[7][7:0];
                reg_adcBuf_10history[47] <= ad7606_data[7][15:8];
            end
            'd3: begin
                reg_adcBuf_10history[48] <= ad7606_data[0][7:0];
                reg_adcBuf_10history[49] <= ad7606_data[0][15:8];
                reg_adcBuf_10history[50] <= ad7606_data[1][7:0];
                reg_adcBuf_10history[51] <= ad7606_data[1][15:8];
                reg_adcBuf_10history[52] <= ad7606_data[2][7:0];
                reg_adcBuf_10history[53] <= ad7606_data[2][15:8];
                reg_adcBuf_10history[54] <= ad7606_data[3][7:0];
                reg_adcBuf_10history[55] <= ad7606_data[3][15:8];
                reg_adcBuf_10history[56] <= ad7606_data[4][7:0];
                reg_adcBuf_10history[57] <= ad7606_data[4][15:8];
                reg_adcBuf_10history[58] <= ad7606_data[5][7:0];
                reg_adcBuf_10history[59] <= ad7606_data[5][15:8];
                reg_adcBuf_10history[60] <= ad7606_data[6][7:0];
                reg_adcBuf_10history[61] <= ad7606_data[6][15:8];
                reg_adcBuf_10history[62] <= ad7606_data[7][7:0];
                reg_adcBuf_10history[63] <= ad7606_data[7][15:8];
            end
        endcase
        
        reg_adcBuf_10history[64] <= reg_adcBuf_10history_tick;
        reg_adcBuf_10history[65] <= din_buf;
        reg_adcBuf_10history_tick_d <= reg_adcBuf_10history_tick + 1;
    end
end

endmodule