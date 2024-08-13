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

float_bits float_denorm_zero(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	if (exp == 0) {
		// Denormalized
		frac = 0;
	}
	return (sign << 31) | (exp << 23) | frac;
}

// NaNは指数フィールドが全て1かつ小数フィールドが非ゼロの場合

float_bits float_negate(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (exp == 0xFF) {
		return f;
	}
	sign = !sign;
	// printf("sign %d\n", sign);
	return (sign << 31) | (exp << 23) | frac;
}

int compare_uf(unsigned x, float y) {
	unsigned x_sign = x >> 31;
	unsigned x_exp = x >> 23 & 0xFF;
	unsigned x_frac = x & 0x7FFFFF;

	unsigned yu = (unsigned) y;

	unsigned y_sign = yu >> 31;
	unsigned y_exp = yu >> 23 & 0xFF;
	unsigned y_frac = yu & 0x7FFFFF;

	if (x_sign != y_sign) {
        return x_sign - y_sign;
    }

    if (x_exp != y_exp) {
        return x_exp - y_exp;
    }

    return x_frac - y_frac;
}

int main() {
	for (unsigned i = 0; i < pow(2, 32) ; i++)
	{
		// if (compare_uf(float_negate(i), -(float) i)) {
		// 	printf("incorrect i: %x\n", i);
		// 	return 0;
		// }
		if (float_negate(i) != float_to_bits(-(float) i)) {
			printf("incorrect i: %x\n", i);
			// printf("incorrect i: %x\n", float_negate(i));

			printf("my : %x\n", float_negate(i));
			printf("co : %x\n", float_to_bits(-(float) i));
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