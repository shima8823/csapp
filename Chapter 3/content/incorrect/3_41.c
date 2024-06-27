/*

A.	p	: 0
	s.x	: 8
	s.y	: 12
	next: 16

B.	24 byte
C.	code

*/

struct prob {
	int *p;
	struct {
		int x;
		int y;
	} s;
	struct prob *next;	
};


void sp_init(struct prob *sp) {
	sp->s.x = sp->s.y;
	// mistake sp->p = sp->s.x;
	sp->p = &(sp->s.x);
	sp->next = sp;
}