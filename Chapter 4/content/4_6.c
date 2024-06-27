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
	xorq	%r11, %r11 // r11 = 0
	subq	%r10, %r11 // r11 = 0 - r10
	andq	%r10, %r10
	cmovl	%r11, %r10
	addq	%r10, %rax
	addq	%r8, %rdi
	subq	%r9, %rsi
test:
	jne		loop
	ret



ANSWER
	

*/
