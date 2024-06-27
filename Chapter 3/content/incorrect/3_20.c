/*

	x == -8 (1000)
	-8 >> 3 = (0001) これはダメ

	7 + -8 = -1

	testq 負フラグにセット
	cmovns xが非負なら、temp = x
	sarq -1 >> 3
	1111 >> 3 = 1111

	x == -4 (1100)
	-8 >> 3 = (0001) これはダメ

	7 + -4 = 3

	testq 負フラグにセット
	cmovns xが非負なら、temp = x
	sarq 3 >> 3
	0011 >> 3 = 0000

*/

#define OP /

long arith(long x) {
	return x OP 8;
}

