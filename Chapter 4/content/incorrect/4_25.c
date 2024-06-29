/*
表記ミス

bool mem_data = icode in {IRMMOVQ, IPUSHQ, ICALL}

*/
/*

Answer

bool mem_data = [
	icode in {IRMMOVQ, IPUSHQ } : valA;
	icode == ICALL : VALP;
];

*/