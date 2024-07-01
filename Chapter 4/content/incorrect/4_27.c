/*

word Stat = [
	!imem_error || !dmem_error : SADR;
	!icode : SINS;
	!instr_valid : SHLT;
	1 : SAOK;
];

*/

/*
ans

word Stat = [
	imem_error || dmem_error : SADR;
	!instr_valid : SINS;
	icode == IHALT : SHLT;
	1 : SAOK;
];

*/