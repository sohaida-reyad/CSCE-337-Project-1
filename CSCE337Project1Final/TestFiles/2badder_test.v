3
in	ci	1
in	x	[1:0]
in	y	[1:0]
2
out	co	1
out	s	[1:0]
0
24
wire	_00_
wire	_01_
wire	_02_
wire	_03_
wire	_04_
wire	_05_
wire	_06_
wire	_07_
wire	_08_
wire	_09_
wire	_10_
wire	_11_
wire	_12_
wire	_13_
wire	_14_
wire	_15_
wire	_16_
wire	_17_
wire	_18_
wire	_19_
wire	_20_
wire	_21_
wire	_22_
wire	_23_
8
assign	_00_	ci
assign	_15_	y[1]
assign	_16_	x[1]
assign	s[1]	_01_
assign	co	_05_
assign	_07_	y[0]
assign	_09_	x[0]
assign	s[0]	_11_
NAND2X1	_24_	2	_15_	_16_	_17_
OR2X2	_25_	2	_15_	_16_	_02_
NAND2X1	_26_	2	_17_	_02_	_03_
AND2X2	_27_	2	_07_	_09_	_04_
INVX1	_28_	1	_04_	_06_
NOR2X1	_29_	2	_07_	_09_	_08_
NOR2X1	_30_	2	_08_	_04_	_10_
NAND2X1	_31_	2	_00_	_10_	_12_
NAND2X1	_32_	2	_06_	_12_	_13_
XNOR2X1	_33_	2	_13_	_03_	_01_
NAND2X1	_34_	2	_02_	_13_	_14_
NAND2X1	_35_	2	_17_	_14_	_05_
XOR2X1	_36_	2	_10_	_00_	_11_
