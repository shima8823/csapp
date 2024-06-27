/*

A,	x:rdi
	y:rcx
	n:rdx

B.	x自身を条件式に使っていなく、すぐに実行されるから(x+=y; (*p)++)

C.	rax = x
	rcx = x
	rcx = x * x
	rdx = x + x
.L2
	rax = 1 + x*x + x (x+=y; (*p)++)
	rdx = x+x -1
	test rdx rdx
	jg .L2
	ret

*/