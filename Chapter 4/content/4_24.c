/*

word dstE = [
	icode in { IRRMOVQ } && Cnd : rB;
	icode in { IIRMOVQ, IOPQ } : rB;
	icode in { IPUSHQ, IPOPQ, ICALLQ, IRET } : RRSP;
	1: RNONE;
];

*/