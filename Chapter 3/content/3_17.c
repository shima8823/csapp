#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

long lt_cnt = 0;
long ge_cnt = 0;


long gotodiff_se(long x, long y) {
	long result;
	if (x < y)
		goto success;
	ge_cnt++;
	result = x - y;
	return result;
success:
	lt_cnt++;
	result = y - x;
	return result;
}

// B. 読みやすさのため統一する

int main() {
	
	return 0;
}