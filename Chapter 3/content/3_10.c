long arith2(long x, long y, long z) {
	long t1 = x | y; // orq
	long t2 = t1 >> 3; // sarq 
	long t3 = ~t2; // not
	long t4 = z - t3; // mov sub
	return t4;
}