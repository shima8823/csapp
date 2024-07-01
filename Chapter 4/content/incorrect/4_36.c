/*

word f_stat = [
	imem_error : SADR;
	!instr_valid : SINS;
	icode == IHALT : SHLT;
	1 : SAOK;
]

word m_stat = [
	imem_error || dmem_error : SADR;
	!instr_valid : SINS;
	icode == IHALT : SHLT;
	1 : SAOK;
];

ans f_statでinstruction系のstatは決めている。

word m_stat = [
	dmem_error : SADR;
	1 : SAOK;
];


*/