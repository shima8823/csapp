/*

Y86-64
absSum:
	irmovq	$8, %r8
	irmovq	$1, %r9
	xorq	%rax, %rax
	andq	%rsi, %rsi
	jmp		test
loop:
	mrmovq	(%rsi), %r10
	andq	%r10, %r10
	jge		sum_main
	rrmovq	%r10, %r11
	xorq	%r10, %r10
	subq	%r11, %r10
sum_main:
	addq	%r10, %rax
	addq	%r8, %rdi
	subq	%r9, %rsi
test:
	jne		loop
	ret



ANSWER
	

*/
