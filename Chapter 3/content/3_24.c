#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

long loop_while(long a, long b) {
	long result = 1;
	while (a < b) {
		result = result * (a + b);
		a = a + 1;
	}
	return result;
}