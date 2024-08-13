#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// A. 型の上限値を超えたシフト演算をするとINT_MINになるはず。
// A_ans. 未定義動作と書いてある。
// B. bad_int_size_is_32_at_32bit_machine
// C. 

// int bad_int_size_is_32() {
// 	int set_msb = 1 << 31; // 16 bitの真偽
// 	int beyond_msb = 1 << 32; // 64 bitの真偽

// 	return set_msb && !beyond_msb;
// }

int bad_int_size_is_32() {
	int set_msb = 1 << 31; // 16 bitの真偽
	int beyond_msb = 1 << 32; // 64 bitの真偽

	printf("%d\n", beyond_msb);

	return set_msb && !beyond_msb;
}

int bad_int_size_is_32_at_32bit_machine() {
	int set_msb = 1 << 31;
	int beyond_msb = 1 << 31;
	int sum_beyond_msb = beyond_msb + beyond_msb;

	return set_msb && sum_beyond_msb >= 0;
}

int int_size_is_32_for_16bit() {
  int set_msb = 1 << 15 << 15 << 1;
  int beyond_msb = set_msb << 1;

  return set_msb && !beyond_msb;
}

int main() {
	// printf("%d\n", bad_int_size_is_32());
	printf("%d\n", bad_int_size_is_32_at_32bit_machine());
	return 0;
}