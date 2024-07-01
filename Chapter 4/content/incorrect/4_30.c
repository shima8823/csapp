/*

word f_stat = [

	!instr_valid : SINS;
	icode == IHALT : SHLT;
	1 : SAOK;
]

ans
word f_stat = [
	imem_error : SADR;
	!instr_valid : SINS;
	icode == IHALT : SHLT;
	1 : SAOK;
]

word Stat = [
	imem_error || dmem_error : SADR;
	!instr_valid : SINS;
	icode == IHALT : SHLT;
	1 : SAOK;
];

*/