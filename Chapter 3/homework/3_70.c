/*

A.	e1.p : 0
	e1.y : 8
	e2.x : 0
	e2.next : 8

B.	16 byte

movq	rax = 8 + up
movq	rdx = 8 + up
movq	rdx = *(8 + up)
subq	*(8 + up) -= *(8 + (8 + up))
movq	rdi = *(8 + up) - *(8 + (8 + up))

C.	

*/

union ele {
	struct {
		long *p;
		long y;
	} e1;
	struct {
		long x;
		union ele *next;
	} e2;
};

void proc(union ele *up) {
	up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e1.y;
}