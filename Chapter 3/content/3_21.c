/*

	leak 0 + x * 8: rax = 8x;
	testq y, y
	jle .L2 ?
	movq rax = y
	subq rax = y - x
	movq rdx = x;
	andq rdx = x & y;
	cmpq x, y
	cmovge rax = rdx

.L2
	addq rdi = x + y;
	cmpq $-2, y
	cmovle rax = x


	// comp
	com 10, 5
	jle 5 <= 10
	5 - 10 = -5 <-ここで負フラグを設定されている

	jleはcmpやtestでフラグをつけられた後のゼロフラグ、負のフラグを判定しているだけ？
*/

long test(long x, long y) {
	long val = 8 * x;
	if (y > 0) {
		if (x < y)
			val = y - x;
		else
			// cmovge rax = rdx
			val = x & y;
	} else if (y <= -2)
	// addq rdi = x + y;
	// cmpq $-2, y
	// cmovle rax = x
		val = x + y;
	return val;
}