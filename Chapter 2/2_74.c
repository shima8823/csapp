#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

int tsub_ok(int x, int y) {
	int sum = x - y;
	int sig_mask = INT_MIN;

	int pos_over = !(x & sig_mask) && !(-y & sig_mask) && (sum & sig_mask);	
	int neg_over = (x & sig_mask) && (-y & sig_mask) && !(sum & sig_mask);
	return !(INT_MIN == y || pos_over || neg_over);
}

int main() {
	assert(tsub_ok(10, 10));
	assert(!tsub_ok(INT_MIN, 10));
	assert(!tsub_ok(INT_MAX, -20));
	assert(!tsub_ok(INT_MAX, INT_MIN));

	assert(!tsub_ok(0x00, INT_MIN));
  assert(tsub_ok(0x00, 0x00));
	return 0;
}