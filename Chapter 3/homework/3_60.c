/*

movl	ecx = n
movl	edx = 1 mask?
movl	eax = 0 result?
jmp		.L2

.L3
movq	r8 = x
andq	r8 = x & edx
orq		rax = result | (x & edx)
salq	rdx = rdx << cl(４番目の引数 rcx)

.L2
testq	%rdx, %rdx
jne		.L3 0じゃないなら.L3

A.	x		: r8
	n		: ecx
	result	: rax
	mask	: rdx

B.	result = 0, mask = 1
C.	mask != 0
D.	mask << (char)n
E.	(x & mask)

*/

long loop(long x, int n) {
	long result = 0;
	long mask;
	for (mask = 1; mask != 0; mask = mask << (char)n ){
		result |= (x & mask);
	}
	return result;
}