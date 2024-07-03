/*

//45
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

// lp = 1 / 9 1b これはmrmovqとpopqで生じる
mp = 1 / 9 2b
rp = 0


//46
loop:
	mrmovq	(%rsi), %r10
	xorq	%r11, %r11 // r11 = 0
	subq	%r10, %r11 // r11 = 0 - r10
	andq	%r10, %r10
	cmovl	%r11, %r10
	addq	%r10, %rax
	addq	%r8, %rdi
	subq	%r9, %rsi

lp = 1 / 8 1b
mp = 0
rp = 0

平均命令数
4.5	9  ans 8.5(50%でせいのため)
4.6	8

平均バブル数
4.5	3b -> 1.0
4.6 1b -> 0

平均クロック・サイクル数
	命令の頻度	条件頻度	バブル
4.5 	0.11	0.20 		1		 = 0.022
		0.11	0.40		2		 = 0.088
									 = 0
									 0.11
	0.11 + 1.00 = 1.11

	8.5サイクル + 1.0 b = 9.5サイクル

	命令の頻度	条件頻度	バブル
4.6 	0.125	0.20 		1		 = 0.025
									 = 0
									 = 0
									 0.025
	0.025 + 1.00 = 1.025
	
	ans
	1.00 8.0サイクル


*/