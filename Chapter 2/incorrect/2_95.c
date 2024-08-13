#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

typedef unsigned float_bits;

float u2f(unsigned x) {
    return *(float*)&x;
}

unsigned f2u(float f) {
    return *(unsigned*)&f;
}

float_bits float_half(float_bits f) {
	unsigned sign = f >> 31;
	unsigned rest = f & 0x7FFFFFFF;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	if (exp == 0xFF) {
		return f;
	}

	int addtion = (frac & 0x3) == 0x3;

	if (exp == 0) {
		// Denormalizedも.5倍する 
		frac >>= 1;
		frac += addtion;
	} else {
		exp -= 1;
		if (exp == 0) {
			rest >>= 1;
			rest += addtion;
			exp = rest >> 23 & 0xFF;
			frac = rest & 0x7FFFFF;
		}
	}

	return (sign << 31) | (exp << 23) | frac;
}

int main() {
	for (unsigned i = 1; i < 0xFFFFFFFF ; i++)
	{
		unsigned fb_result = float_half(i);
        float f = u2f(i);
        float f_result = 2.0f * f;
        unsigned standard_result = f2u(f_result);

        if (fb_result != standard_result) {
			printf("Error at %u: fb_result = 0x%08X, standard_result = 0x%08X\n", i, fb_result, standard_result);

			// printf("fabsf(i)                : %f\n", fabsf((float) i));
			// printf("float_to_bits(fabsf((float) i)): %x\n", float_to_bits(fabsf((float) i)));
			// printf("float_to_bits(fabsf((float) i)): %x\n", float_to_bits((float)float_absval(i)));

			
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


/*
#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF) {
        // NaN or Infinity
        return f;
    }

    if (exp == 0) {
        // Denormalized
        frac <<= 1;
    } else {
        exp += 1;
        if (exp == 0xFF) {
            frac = 0;
        }
    }

    return (sign << 31) | (exp << 23) | frac;
}

float u2f(unsigned x) {
    return *(float*)&x;
}

unsigned f2u(float f) {
    return *(unsigned*)&f;
}

int main() {
    unsigned errors = 0;
    for (unsigned i = 0; i < 0xFFFFFFFF; ++i) {
        unsigned fb_result = float_twice(i);
        float f = u2f(i);
        float f_result = 2.0f * f;
        unsigned standard_result = f2u(f_result);

        if (fb_result != standard_result) {
            errors++;
            printf("Error at %u: fb_result = 0x%08X, standard_result = 0x%08X\n", i, fb_result, standard_result);
        }
    }

    printf("Total errors: %u\n", errors);
    return 0;
}
*/