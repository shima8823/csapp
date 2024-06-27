/*

面白い

A. jump to middle
B. code
C.	x = 8 (0000 ... 1000)
	val = 8
	x >>= 1, x = 4

	val = 8 ^ 4 = 12;
	x >> = 1, x = 2

	...
	val = 15(1111)
	x >>= 1, x=0

	val & 1

	A. xの中に1ビットが存在するのか調べている。
	correct A. xのパリティを計算するもの。xに1が奇数の場合は1、偶数であれば0;
*/

long fun_a(unsigned long x) {
	long val = 0;
	while (x != 0) {
		val = val ^ x;
		x >>= 1;
	}
	return val & 1;
}