#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

typedef unsigned char *byte_pointer;

int any_odd_one(unsigned x) {
	unsigned mask = 0x55555555;
	return !!(x & mask);
}

void test(int x) {
}

int main() {
	printf("%d\n", any_odd_one(0x55555555));
	printf("%d\n", any_odd_one(5));
	printf("%d\n", any_odd_one(4));
	printf("%d\n", any_odd_one(2));
	return 0;
}