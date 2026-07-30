module gw_gao(
    \reg_a2f_sram_workEnable[7] ,
    \reg_a2f_sram_workEnable[6] ,
    \reg_a2f_sram_workEnable[5] ,
    \reg_a2f_sram_workEnable[4] ,
    \reg_a2f_sram_workEnable[3] ,
    \reg_a2f_sram_workEnable[2] ,
    \reg_a2f_sram_workEnable[1] ,
    \reg_a2f_sram_workEnable[0] ,
    \rst_cnt[24] ,
    \rst_cnt[23] ,
    \rst_cnt[22] ,
    \rst_cnt[21] ,
    \rst_cnt[20] ,
    \rst_cnt[19] ,
    \rst_cnt[18] ,
    \rst_cnt[17] ,
    \rst_cnt[16] ,
    \rst_cnt[15] ,
    \rst_cnt[14] ,
    \rst_cnt[13] ,
    \rst_cnt[12] ,
    \rst_cnt[11] ,
    \rst_cnt[10] ,
    \rst_cnt[9] ,
    \rst_cnt[8] ,
    \rst_cnt[7] ,
    \rst_cnt[6] ,
    \rst_cnt[5] ,
    \rst_cnt[4] ,
    \rst_cnt[3] ,
    \rst_cnt[2] ,
    \rst_cnt[1] ,
    \rst_cnt[0] ,
    pll_lock,
    rst_onlyOne,
    MODE_FPGA_RST,
    clk_pllOut1,
    tms_pad_i,
    tck_pad_i,
    tdi_pad_i,
    tdo_pad_o
);

input \reg_a2f_sram_workEnable[7] ;
input \reg_a2f_sram_workEnable[6] ;
input \reg_a2f_sram_workEnable[5] ;
input \reg_a2f_sram_workEnable[4] ;
input \reg_a2f_sram_workEnable[3] ;
input \reg_a2f_sram_workEnable[2] ;
input \reg_a2f_sram_workEnable[1] ;
input \reg_a2f_sram_workEnable[0] ;
input \rst_cnt[24] ;
input \rst_cnt[23] ;
input \rst_cnt[22] ;
input \rst_cnt[21] ;
input \rst_cnt[20] ;
input \rst_cnt[19] ;
input \rst_cnt[18] ;
input \rst_cnt[17] ;
input \rst_cnt[16] ;
input \rst_cnt[15] ;
input \rst_cnt[14] ;
input \rst_cnt[13] ;
input \rst_cnt[12] ;
input \rst_cnt[11] ;
input \rst_cnt[10] ;
input \rst_cnt[9] ;
input \rst_cnt[8] ;
input \rst_cnt[7] ;
input \rst_cnt[6] ;
input \rst_cnt[5] ;
input \rst_cnt[4] ;
input \rst_cnt[3] ;
input \rst_cnt[2] ;
input \rst_cnt[1] ;
input \rst_cnt[0] ;
input pll_lock;
input rst_onlyOne;
input MODE_FPGA_RST;
input clk_pllOut1;
input tms_pad_i;
input tck_pad_i;
input tdi_pad_i;
output tdo_pad_o;

wire \reg_a2f_sram_workEnable[7] ;
wire \reg_a2f_sram_workEnable[6] ;
wire \reg_a2f_sram_workEnable[5] ;
wire \reg_a2f_sram_workEnable[4] ;
wire \reg_a2f_sram_workEnable[3] ;
wire \reg_a2f_sram_workEnable[2] ;
wire \reg_a2f_sram_workEnable[1] ;
wire \reg_a2f_sram_workEnable[0] ;
wire \rst_cnt[24] ;
wire \rst_cnt[23] ;
wire \rst_cnt[22] ;
wire \rst_cnt[21] ;
wire \rst_cnt[20] ;
wire \rst_cnt[19] ;
wire \rst_cnt[18] ;
wire \rst_cnt[17] ;
wire \rst_cnt[16] ;
wire \rst_cnt[15] ;
wire \rst_cnt[14] ;
wire \rst_cnt[13] ;
wire \rst_cnt[12] ;
wire \rst_cnt[11] ;
wire \rst_cnt[10] ;
wire \rst_cnt[9] ;
wire \rst_cnt[8] ;
wire \rst_cnt[7] ;
wire \rst_cnt[6] ;
wire \rst_cnt[5] ;
wire \rst_cnt[4] ;
wire \rst_cnt[3] ;
wire \rst_cnt[2] ;
wire \rst_cnt[1] ;
wire \rst_cnt[0] ;
wire pll_lock;
wire rst_onlyOne;
wire MODE_FPGA_RST;
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
    .trig0_i(MODE_FPGA_RST),
    .data_i({\reg_a2f_sram_workEnable[7] ,\reg_a2f_sram_workEnable[6] ,\reg_a2f_sram_workEnable[5] ,\reg_a2f_sram_workEnable[4] ,\reg_a2f_sram_workEnable[3] ,\reg_a2f_sram_workEnable[2] ,\reg_a2f_sram_workEnable[1] ,\reg_a2f_sram_workEnable[0] ,\rst_cnt[24] ,\rst_cnt[23] ,\rst_cnt[22] ,\rst_cnt[21] ,\rst_cnt[20] ,\rst_cnt[19] ,\rst_cnt[18] ,\rst_cnt[17] ,\rst_cnt[16] ,\rst_cnt[15] ,\rst_cnt[14] ,\rst_cnt[13] ,\rst_cnt[12] ,\rst_cnt[11] ,\rst_cnt[10] ,\rst_cnt[9] ,\rst_cnt[8] ,\rst_cnt[7] ,\rst_cnt[6] ,\rst_cnt[5] ,\rst_cnt[4] ,\rst_cnt[3] ,\rst_cnt[2] ,\rst_cnt[1] ,\rst_cnt[0] ,pll_lock,rst_onlyOne}),
    .clk_i(clk_pllOut1)
);

endmodule
