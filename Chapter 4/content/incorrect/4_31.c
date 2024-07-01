/*
word dstE = [
	icode in { IRRMOVQ } rB;
	icode in { IIRMOVQ, IOPQ } : rB;
	icode in { IPUSHQ, IPOPQ, ICALLQ, IRET } : RRSP;
	1: RNONE;
];

word d_dstE = [
	icode in { IRRMOVQ, IIRMOVQ, IOPQ } : D_rB;
	icode in { IPUSHQ, IPOPQ, ICALLQ, IRET } : RRSP;
	1: RNONE;
]

*/