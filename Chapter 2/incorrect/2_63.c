#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

void test(int x) {
}

unsigned srl(unsigned x, int k) {
	// Perform shift arthmetically

	// x = INTMAX + 1, k = 3
	// 1...01....
	// 1111...01....
	// ↓
	// 0001...01....
	unsigned xsra = (int) x >> k;
	// 0000

	// 先頭からkビット分を0に変える
	// or 先頭からkビット文を除いたものをコピーする
	// 0001111111111

	//  1: 000000000000001
	//  1 << : 00100000000
	//  -1: 00011111111111
	int mask = (1 << ((sizeof(unsigned) << 3) - k)) - 1; // kビット分のマスクを作成
	return xsra & mask;
}

int sra(int x, int k) {
	// Perform shift logically

	// x = -1, k = 3
	// 1...11....
	// 1111...11....
	// ↓
	// 0001...11...
	int xsrl = (unsigned) x >> k;
	// xsrlの先頭からkビット分をxが負だった場合1そうじゃなければ0にする
	// -1 << ((8 * sizeof(int)) - k)
	// 111....00...
	return x & (8 * sizeof(int)) && xsrl | ~(-1 << ((8 * sizeof(int)) - k));

	return xsrl;
}

unsigned srl_correct(unsigned x, int k) {
  unsigned xsra = (int) x >> k;

  int w = sizeof(int) << 3;
//   w = 32
//   k = 2
//   110000000000000000
  int mask = (int) -1 << (w - k);
  return xsra & ~mask;
}

int sra_correct(int x, int k) {
  int xsrl = (unsigned) x >> k;

  int w = sizeof(int) << 3;
  int mask = (int) -1 << (w - k);
  //let mask remain unchanged when the first bit of x is 1, otherwise 0.
  int m = 1 << (w - 1);
//   100000000
// ! (x & m) - 1, 2通りある
// 	 A  0, !(x & m) - 1 = 0;変えなくて良い
//   B -1, !(x & m) - 1 = 
	printf("%d\n", ! (x & m) - 1);
  mask &= ! (x & m) - 1;
  return xsrl | mask;
}

int main() {
	// unsigned x = (unsigned)INT_MAX + 1;
	// int      k = 2;
	// printf("sizeof(unsigned): %lu\n", sizeof(unsigned) << 3);
	// printf("sizeof(int): %lu\n", sizeof(int) << 3);
	// printf("%u\n", srl(x, k));
	// printf("srl_correct %u\n", srl_correct(x, k));
	// return 0;

	unsigned test_unsigned = 0x12345678;
  int test_int = 0x12345678;

  assert(srl(test_unsigned, 4) == test_unsigned >> 4);
  assert(sra_correct(test_int, 4) == test_int >> 4);

  test_unsigned = 0x87654321;
	test_int = 0x87654321;

	assert (srl (test_unsigned, 4) == test_unsigned >> 4);
	assert (sra_correct (test_int, 4) == test_int >> 4);
  
  return 0;
}