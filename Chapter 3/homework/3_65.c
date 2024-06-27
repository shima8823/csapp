/*

movq	rcx = rdx : t = *(A[i][j])
movq	rsi = rax : rsi = *(A[j][i])
movq	rdx = rax : *(A[i][j]) = rsi
movq	rax = rdx : *(A[j][i]) = t

addq	rdx += 8  : A[i][j] += 8 ?
addq	rax += 120: A[j][i] += 120
cmpq	rax != rdi: 
jne		

A.	rdx
B.	rax
C.	15

*/