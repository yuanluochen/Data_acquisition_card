module gw_gao(
    qspi_cs,
    \reg_adcSdpbBuf[0][7] ,
    \reg_adcSdpbBuf[0][6] ,
    \reg_adcSdpbBuf[0][5] ,
    \reg_adcSdpbBuf[0][4] ,
    \reg_adcSdpbBuf[0][3] ,
    \reg_adcSdpbBuf[0][2] ,
    \reg_adcSdpbBuf[0][1] ,
    \reg_adcSdpbBuf[0][0] ,
    \reg_adcSdpbBuf[1][7] ,
    \reg_adcSdpbBuf[1][6] ,
    \reg_adcSdpbBuf[1][5] ,
    \reg_adcSdpbBuf[1][4] ,
    \reg_adcSdpbBuf[1][3] ,
    \reg_adcSdpbBuf[1][2] ,
    \reg_adcSdpbBuf[1][1] ,
    \reg_adcSdpbBuf[1][0] ,
    sdpb_read_clk,
    \qspi_reg_rw_addr[4] ,
    \qspi_reg_rw_addr[3] ,
    \qspi_reg_rw_addr[2] ,
    \qspi_reg_rw_addr[1] ,
    \qspi_reg_rw_addr[0] ,
    \adc_buf_sdpb_data[7] ,
    \adc_buf_sdpb_data[6] ,
    \adc_buf_sdpb_data[5] ,
    \adc_buf_sdpb_data[4] ,
    \adc_buf_sdpb_data[3] ,
    \adc_buf_sdpb_data[2] ,
    \adc_buf_sdpb_data[1] ,
    \adc_buf_sdpb_data[0] ,
    \qspi_io[3] ,
    \qspi_io[2] ,
    \qspi_io[1] ,
    \qspi_io[0] ,
    qspi_sck,
    qspi_rd_hl,
    \qspi_sck_tick[7] ,
    \qspi_sck_tick[6] ,
    \qspi_sck_tick[5] ,
    \qspi_sck_tick[4] ,
    \qspi_sck_tick[3] ,
    \qspi_sck_tick[2] ,
    \qspi_sck_tick[1] ,
    \qspi_sck_tick[0] ,
    \sdpb_outAddr[7] ,
    \sdpb_outAddr[6] ,
    \sdpb_outAddr[5] ,
    \sdpb_outAddr[4] ,
    \sdpb_outAddr[3] ,
    \sdpb_outAddr[2] ,
    \sdpb_outAddr[1] ,
    \sdpb_outAddr[0] ,
    clk_pllOut1,
    tms_pad_i,
    tck_pad_i,
    tdi_pad_i,
    tdo_pad_o
);

input qspi_cs;
input \reg_adcSdpbBuf[0][7] ;
input \reg_adcSdpbBuf[0][6] ;
input \reg_adcSdpbBuf[0][5] ;
input \reg_adcSdpbBuf[0][4] ;
input \reg_adcSdpbBuf[0][3] ;
input \reg_adcSdpbBuf[0][2] ;
input \reg_adcSdpbBuf[0][1] ;
input \reg_adcSdpbBuf[0][0] ;
input \reg_adcSdpbBuf[1][7] ;
input \reg_adcSdpbBuf[1][6] ;
input \reg_adcSdpbBuf[1][5] ;
input \reg_adcSdpbBuf[1][4] ;
input \reg_adcSdpbBuf[1][3] ;
input \reg_adcSdpbBuf[1][2] ;
input \reg_adcSdpbBuf[1][1] ;
input \reg_adcSdpbBuf[1][0] ;
input sdpb_read_clk;
input \qspi_reg_rw_addr[4] ;
input \qspi_reg_rw_addr[3] ;
input \qspi_reg_rw_addr[2] ;
input \qspi_reg_rw_addr[1] ;
input \qspi_reg_rw_addr[0] ;
input \adc_buf_sdpb_data[7] ;
input \adc_buf_sdpb_data[6] ;
input \adc_buf_sdpb_data[5] ;
input \adc_buf_sdpb_data[4] ;
input \adc_buf_sdpb_data[3] ;
input \adc_buf_sdpb_data[2] ;
input \adc_buf_sdpb_data[1] ;
input \adc_buf_sdpb_data[0] ;
input \qspi_io[3] ;
input \qspi_io[2] ;
input \qspi_io[1] ;
input \qspi_io[0] ;
input qspi_sck;
input qspi_rd_hl;
input \qspi_sck_tick[7] ;
input \qspi_sck_tick[6] ;
input \qspi_sck_tick[5] ;
input \qspi_sck_tick[4] ;
input \qspi_sck_tick[3] ;
input \qspi_sck_tick[2] ;
input \qspi_sck_tick[1] ;
input \qspi_sck_tick[0] ;
input \sdpb_outAddr[7] ;
input \sdpb_outAddr[6] ;
input \sdpb_outAddr[5] ;
input \sdpb_outAddr[4] ;
input \sdpb_outAddr[3] ;
input \sdpb_outAddr[2] ;
input \sdpb_outAddr[1] ;
input \sdpb_outAddr[0] ;
input clk_pllOut1;
input tms_pad_i;
input tck_pad_i;
input tdi_pad_i;
output tdo_pad_o;

wire qspi_cs;
wire \reg_adcSdpbBuf[0][7] ;
wire \reg_adcSdpbBuf[0][6] ;
wire \reg_adcSdpbBuf[0][5] ;
wire \reg_adcSdpbBuf[0][4] ;
wire \reg_adcSdpbBuf[0][3] ;
wire \reg_adcSdpbBuf[0][2] ;
wire \reg_adcSdpbBuf[0][1] ;
wire \reg_adcSdpbBuf[0][0] ;
wire \reg_adcSdpbBuf[1][7] ;
wire \reg_adcSdpbBuf[1][6] ;
wire \reg_adcSdpbBuf[1][5] ;
wire \reg_adcSdpbBuf[1][4] ;
wire \reg_adcSdpbBuf[1][3] ;
wire \reg_adcSdpbBuf[1][2] ;
wire \reg_adcSdpbBuf[1][1] ;
wire \reg_adcSdpbBuf[1][0] ;
wire sdpb_read_clk;
wire \qspi_reg_rw_addr[4] ;
wire \qspi_reg_rw_addr[3] ;
wire \qspi_reg_rw_addr[2] ;
wire \qspi_reg_rw_addr[1] ;
wire \qspi_reg_rw_addr[0] ;
wire \adc_buf_sdpb_data[7] ;
wire \adc_buf_sdpb_data[6] ;
wire \adc_buf_sdpb_data[5] ;
wire \adc_buf_sdpb_data[4] ;
wire \adc_buf_sdpb_data[3] ;
wire \adc_buf_sdpb_data[2] ;
wire \adc_buf_sdpb_data[1] ;
wire \adc_buf_sdpb_data[0] ;
wire \qspi_io[3] ;
wire \qspi_io[2] ;
wire \qspi_io[1] ;
wire \qspi_io[0] ;
wire qspi_sck;
wire qspi_rd_hl;
wire \qspi_sck_tick[7] ;
wire \qspi_sck_tick[6] ;
wire \qspi_sck_tick[5] ;
wire \qspi_sck_tick[4] ;
wire \qspi_sck_tick[3] ;
wire \qspi_sck_tick[2] ;
wire \qspi_sck_tick[1] ;
wire \qspi_sck_tick[0] ;
wire \sdpb_outAddr[7] ;
wire \sdpb_outAddr[6] ;
wire \sdpb_outAddr[5] ;
wire \sdpb_outAddr[4] ;
wire \sdpb_outAddr[3] ;
wire \sdpb_outAddr[2] ;
wire \sdpb_outAddr[1] ;
wire \sdpb_outAddr[0] ;
wire clk_pllOut1;
wire tms_pad_i;
wire tck_pad_i;
wire tdi_pad_i;
wire tdo_pad_o;
wire tms_i_c;
wire tck_i_c;
wire tdi_i_c;
wire tdo_o_c;
wire [9:0] control0;
wire gao_jtag_tck;
wire gao_jtag_reset;
wire run_test_idle_er1;
wire run_test_idle_er2;
wire shift_dr_capture_dr;
wire update_dr;
wire pause_dr;
wire enable_er1;
wire enable_er2;
wire gao_jtag_tdi;
wire tdo_er1;

IBUF tms_ibuf (
    .I(tms_pad_i),
    .O(tms_i_c)
);

IBUF tck_ibuf (
    .I(tck_pad_i),
    .O(tck_i_c)
);

IBUF tdi_ibuf (
    .I(tdi_pad_i),
    .O(tdi_i_c)
);

OBUF tdo_obuf (
    .I(tdo_o_c),
    .O(tdo_pad_o)
);

GW_JTAG  u_gw_jtag(
    .tms_pad_i(tms_i_c),
    .tck_pad_i(tck_i_c),
    .tdi_pad_i(tdi_i_c),
    .tdo_pad_o(tdo_o_c),
    .tck_o(gao_jtag_tck),
    .test_logic_reset_o(gao_jtag_reset),
    .run_test_idle_er1_o(run_test_idle_er1),
    .run_test_idle_er2_o(run_test_idle_er2),
    .shift_dr_capture_dr_o(shift_dr_capture_dr),
    .update_dr_o(update_dr),
    .pause_dr_o(pause_dr),
    .enable_er1_o(enable_er1),
    .enable_er2_o(enable_er2),
    .tdi_o(gao_jtag_tdi),
    .tdo_er1_i(tdo_er1),
    .tdo_er2_i(1'b0)
);

gw_con_top  u_icon_top(
    .tck_i(gao_jtag_tck),
    .tdi_i(gao_jtag_tdi),
    .tdo_o(tdo_er1),
    .rst_i(gao_jtag_reset),
    .control0(control0[9:0]),
    .enable_i(enable_er1),
    .shift_dr_capture_dr_i(shift_dr_capture_dr),
    .update_dr_i(update_dr)
);

ao_top_0  u_la0_top(
    .control(control0[9:0]),
    .trig0_i(qspi_cs),
    .data_i({qspi_cs,\reg_adcSdpbBuf[0][7] ,\reg_adcSdpbBuf[0][6] ,\reg_adcSdpbBuf[0][5] ,\reg_adcSdpbBuf[0][4] ,\reg_adcSdpbBuf[0][3] ,\reg_adcSdpbBuf[0][2] ,\reg_adcSdpbBuf[0][1] ,\reg_adcSdpbBuf[0][0] ,\reg_adcSdpbBuf[1][7] ,\reg_adcSdpbBuf[1][6] ,\reg_adcSdpbBuf[1][5] ,\reg_adcSdpbBuf[1][4] ,\reg_adcSdpbBuf[1][3] ,\reg_adcSdpbBuf[1][2] ,\reg_adcSdpbBuf[1][1] ,\reg_adcSdpbBuf[1][0] ,sdpb_read_clk,\qspi_reg_rw_addr[4] ,\qspi_reg_rw_addr[3] ,\qspi_reg_rw_addr[2] ,\qspi_reg_rw_addr[1] ,\qspi_reg_rw_addr[0] ,\adc_buf_sdpb_data[7] ,\adc_buf_sdpb_data[6] ,\adc_buf_sdpb_data[5] ,\adc_buf_sdpb_data[4] ,\adc_buf_sdpb_data[3] ,\adc_buf_sdpb_data[2] ,\adc_buf_sdpb_data[1] ,\adc_buf_sdpb_data[0] ,\qspi_io[3] ,\qspi_io[2] ,\qspi_io[1] ,\qspi_io[0] ,qspi_sck,qspi_rd_hl,\qspi_sck_tick[7] ,\qspi_sck_tick[6] ,\qspi_sck_tick[5] ,\qspi_sck_tick[4] ,\qspi_sck_tick[3] ,\qspi_sck_tick[2] ,\qspi_sck_tick[1] ,\qspi_sck_tick[0] ,\sdpb_outAddr[7] ,\sdpb_outAddr[6] ,\sdpb_outAddr[5] ,\sdpb_outAddr[4] ,\sdpb_outAddr[3] ,\sdpb_outAddr[2] ,\sdpb_outAddr[1] ,\sdpb_outAddr[0] }),
    .clk_i(clk_pllOut1)
);

endmodule
