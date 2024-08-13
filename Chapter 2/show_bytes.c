#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
	size_t i;
	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_int(int x) {
	printf("int:    ");
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
	printf("float:  ");
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
	printf("void:   ");
    show_bytes((byte_pointer) &x, sizeof(void *));
}

// 2.57
void show_short(short x) {
	printf("short:  ");
    show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x) {
	printf("long:   ");
    show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x) {
	printf("double: ");
    show_bytes((byte_pointer) &x, sizeof(double));
}

// 2.58
bool is_little_endian() {
	int x = 1;
	byte_pointer start = (byte_pointer)&x;
	if (start[0])
		return true;
	return false;
}

// 2.59
void sum_bit() {
	int x = 0x89ABCDEF;
	int y = 0x76543210;

	int r = (x & 0xFF) | (y & ~0xFF);

	printf("%x", r);
	printf("\n");
}

// 2.60
unsigned replace_byte(unsigned x, int i, unsigned char b) {
	byte_pointer s = (byte_pointer) &x;
	size_t u_size = (sizeof(unsigned) * 8)/8 - 1;
	for (int j = u_size - 1; j >= 0; j--) {
		if (j == i) {
			s[j] = b;
		}
	}
	return x;
}

void test(int x) {
	int int_x = (int)x;
	float float_x = (float)x;
	void *void_x = (void *)&x;
	short short_x = (short)x;
	long long_x = (long)x;
	double double_x = (double)x;
	show_int(int_x);
	show_float(float_x);
	show_pointer(void_x);
	show_short(short_x);
	show_long(long_x);
	show_double(double_x);	
}

int main() {
	// 2.57
	// test(12345);
	// 2.58
	// printf("%s\n", (is_little_endian() ? "true": "false"));
	// 2.59
	// sum_bit();
	// 2.60
	// unsigned r;
	// r = replace_byte(0x12345678, 2, 0xAB);
	// printf("%x\n", r);
	// r = replace_byte(0x12345678, 0, 0xAB);
	// printf("%x\n", r);

	// 8倍するとおなじ
	// printf("%lu\n", sizeof(int)<<3);

	
	return 0;
}