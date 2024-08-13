#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

typedef unsigned float_bits;

union u_float_bits {
    float f;
    unsigned u;
};

unsigned float_to_bits(float f) {
    union u_float_bits fb;
    fb.f = f;
    return fb.u;
}

float_bits float_absval(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	if (exp == 0xFF) {
		return f;
	}

	return ((sign ^ sign) << 31) | (exp << 23) | frac;
}


int main() {
	for (unsigned i = 0; i < pow(2, 32) ; i++)
	{
		if (float_to_bits((float)float_absval(i)) != float_to_bits(fabsf((float) i))) {
			printf("incorrect i: %x\n", i);
			printf("float_absval(i)                : %f\n",(float) float_absval(i));
			printf("fabsf(i)                : %f\n", fabsf((float) i));
			printf("float_to_bits(fabsf((float) i)): %x\n", float_to_bits(fabsf((float) i)));
			printf("float_to_bits(fabsf((float) i)): %x\n", float_to_bits((float)float_absval(i)));

			
			return 0;
		}
		// if ((float)float_negate(i) !=  (float) -i) {
		// 	printf("incorrect i: %x\n", i);
		// 	printf("float_negate(i): %f\n", float_negate(i));
		// 	printf("- (float) i    : %f\n", (float)- i);
		// 	return 0;
		// }
	}
	
	return 0;
}