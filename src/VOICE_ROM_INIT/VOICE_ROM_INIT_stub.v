// Copyright 1986-2014 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2014.2 (win64) Build 928826 Thu Jun  5 18:21:07 MDT 2014
// Date        : Wed Sep 10 03:37:55 2014
// Host        : Dtysky running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               d:/spira_heaven/0-myworks/ld3320_axi/ld3320_axi_1.0/src/VOICE_ROM_INIT/VOICE_ROM_INIT_stub.v
// Design      : VOICE_ROM_INIT
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z010clg400-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "blk_mem_gen_v8_2,Vivado 2014.2" *)
module VOICE_ROM_INIT(clka, wea, addra, dina, clkb, addrb, doutb)
/* synthesis syn_black_box black_box_pad_pin="clka,wea[0:0],addra[5:0],dina[15:0],clkb,addrb[5:0],doutb[15:0]" */;
  input clka;
  input [0:0]wea;
  input [5:0]addra;
  input [15:0]dina;
  input clkb;
  input [5:0]addrb;
  output [15:0]doutb;
endmodule
