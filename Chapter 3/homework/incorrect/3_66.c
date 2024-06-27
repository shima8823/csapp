/*

凡ミス

leaq	r8 = 1 + 4 * n
leaq	rax = 3n
movq	rdi = 3n
testq	rax, rax
jle .L4	rax <= 0
salq	r8 = (1 + 4n) * 8
leaq	rcx = A + 8j
movl	eax = 0
movl	edx = 0

.L3
addq	rax = 0 + (A + 8j)
addq	rdx = 0 + 1
addq	rcx = (A + 8j) + (1 + 4n)8 = A + 8(4n+1 + j)
cmpq	
jne		i != 3n

.L4
movl	eax = 0
ret

*/

#define NR(x) (3 * x)
#define NC(x) (4*x+1)

long sum_col(long n, long A[NR(n)][NC(n)], long j) {
	long i;
	long result = 0;
	for (i = 0; i < NR(n); i++)
		result += A[i][j];
	return result;
}