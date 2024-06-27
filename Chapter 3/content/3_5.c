
// 				rdi			rsi		rdx
void decode1(long *xp, long *yp, long *zp) {
	long r8 = *xp;
	long rcx = *yp;
	long rax = *zp;
	
	*yp = r8;
	*zp = rcx;
	*xp = rax;
}