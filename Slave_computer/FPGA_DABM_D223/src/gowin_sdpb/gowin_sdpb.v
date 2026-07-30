//Copyright (C)2014-2025 Gowin Semiconductor Corporation.
//All rights reserved.
//File Title: IP file
//Tool Version: V1.9.12 (64-bit)
//Part Number: GW1NR-LV4QN88PC6/I5
//Device: GW1NR-4
//Device Version: D
//Created Time: Fri Jun 19 18:16:17 2026

module Gowin_SDPB (dout, clka, cea, reseta, clkb, ceb, resetb, oce, ada, din, adb);

output [135:0] dout;
input clka;
input cea;
input reseta;
input clkb;
input ceb;
input resetb;
input oce;
input [7:0] ada;
input [135:0] din;
input [7:0] adb;

wire gw_vcc;
wire gw_gnd;

assign gw_vcc = 1'b1;
assign gw_gnd = 1'b0;

SDPB sdpb_inst_0 (
    .DO(dout[31:0]),
    .CLKA(clka),
    .CEA(cea),
    .RESETA(reseta),
    .CLKB(clkb),
    .CEB(ceb),
    .RESETB(resetb),
    .OCE(oce),
    .BLKSELA({gw_gnd,gw_gnd,gw_gnd}),
    .BLKSELB({gw_gnd,gw_gnd,gw_gnd}),
    .ADA({gw_gnd,ada[7:0],gw_gnd,gw_vcc,gw_vcc,gw_vcc,gw_vcc}),
    .DI(din[31:0]),
    .ADB({gw_gnd,adb[7:0],gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd})
);

defparam sdpb_inst_0.READ_MODE = 1'b0;
defparam sdpb_inst_0.BIT_WIDTH_0 = 32;
defparam sdpb_inst_0.BIT_WIDTH_1 = 32;
defparam sdpb_inst_0.BLK_SEL_0 = 3'b000;
defparam sdpb_inst_0.BLK_SEL_1 = 3'b000;
defparam sdpb_inst_0.RESET_MODE = "SYNC";

SDPB sdpb_inst_1 (
    .DO(dout[63:32]),
    .CLKA(clka),
    .CEA(cea),
    .RESETA(reseta),
    .CLKB(clkb),
    .CEB(ceb),
    .RESETB(resetb),
    .OCE(oce),
    .BLKSELA({gw_gnd,gw_gnd,gw_gnd}),
    .BLKSELB({gw_gnd,gw_gnd,gw_gnd}),
    .ADA({gw_gnd,ada[7:0],gw_gnd,gw_vcc,gw_vcc,gw_vcc,gw_vcc}),
    .DI(din[63:32]),
    .ADB({gw_gnd,adb[7:0],gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd})
);

defparam sdpb_inst_1.READ_MODE = 1'b0;
defparam sdpb_inst_1.BIT_WIDTH_0 = 32;
defparam sdpb_inst_1.BIT_WIDTH_1 = 32;
defparam sdpb_inst_1.BLK_SEL_0 = 3'b000;
defparam sdpb_inst_1.BLK_SEL_1 = 3'b000;
defparam sdpb_inst_1.RESET_MODE = "SYNC";

SDPX9B sdpx9b_inst_2 (
    .DO(dout[99:64]),
    .CLKA(clka),
    .CEA(cea),
    .RESETA(reseta),
    .CLKB(clkb),
    .CEB(ceb),
    .RESETB(resetb),
    .OCE(oce),
    .BLKSELA({gw_gnd,gw_gnd,gw_gnd}),
    .BLKSELB({gw_gnd,gw_gnd,gw_gnd}),
    .ADA({gw_gnd,ada[7:0],gw_gnd,gw_vcc,gw_vcc,gw_vcc,gw_vcc}),
    .DI(din[99:64]),
    .ADB({gw_gnd,adb[7:0],gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd})
);

defparam sdpx9b_inst_2.READ_MODE = 1'b0;
defparam sdpx9b_inst_2.BIT_WIDTH_0 = 36;
defparam sdpx9b_inst_2.BIT_WIDTH_1 = 36;
defparam sdpx9b_inst_2.BLK_SEL_0 = 3'b000;
defparam sdpx9b_inst_2.BLK_SEL_1 = 3'b000;
defparam sdpx9b_inst_2.RESET_MODE = "SYNC";

SDPX9B sdpx9b_inst_3 (
    .DO(dout[135:100]),
    .CLKA(clka),
    .CEA(cea),
    .RESETA(reseta),
    .CLKB(clkb),
    .CEB(ceb),
    .RESETB(resetb),
    .OCE(oce),
    .BLKSELA({gw_gnd,gw_gnd,gw_gnd}),
    .BLKSELB({gw_gnd,gw_gnd,gw_gnd}),
    .ADA({gw_gnd,ada[7:0],gw_gnd,gw_vcc,gw_vcc,gw_vcc,gw_vcc}),
    .DI(din[135:100]),
    .ADB({gw_gnd,adb[7:0],gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd})
);

defparam sdpx9b_inst_3.READ_MODE = 1'b0;
defparam sdpx9b_inst_3.BIT_WIDTH_0 = 36;
defparam sdpx9b_inst_3.BIT_WIDTH_1 = 36;
defparam sdpx9b_inst_3.BLK_SEL_0 = 3'b000;
defparam sdpx9b_inst_3.BLK_SEL_1 = 3'b000;
defparam sdpx9b_inst_3.RESET_MODE = "SYNC";

endmodule //Gowin_SDPB
