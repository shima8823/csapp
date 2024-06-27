#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

long test(long x, long y, long z) {
	long val = x + y + z;
	if (x < -3) {
		if (y < z)
			val = x * y;
		else
			// l3
			val = y * z;
	} else if (x > 2)
		// l2
		val = x * z;
	return val;
}