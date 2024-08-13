#include <stdio.h>
// #include <limits.h>
// #include <stdint.h>
#include <stdbool.h>
#include <limits.h>

typedef unsigned char *byte_pointer;

void test(int x) {
}

int int_shifts_are_arithmetic() {
	int x = -1;
	// 11111111
	// 1 -> 11111111
	// printf("%d\n", (x >> (sizeof(int) << 3)));
	// printf("%d\n", (x ^ (x >> 1)));

	// printf("bool %d\n", !(x ^ (x >> 1)));
	return !~(x >> (sizeof(int) << 3));
}

int answer() {
	int x = -1;
	return !(x ^ (x >> 1));
}

int main() {
	printf("my  %s\n", (int_shifts_are_arithmetic() == 1 ? "true" : "false"));
	printf("ans %s\n", (answer() == 1 ? "true" : "false"));
	return 0;
}