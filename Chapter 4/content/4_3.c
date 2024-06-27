/*

sum:
	xorq	%rax, %rax
	andq	%rsi, %rsi
	jmp		test
loop:
	mrmovq	(%rsi), %r10
	addq	%r10, %rax
	iaddq	$8, %rdi
	iaddq	$-1, %rsi
test:
	jne		loop
	ret
	
*/