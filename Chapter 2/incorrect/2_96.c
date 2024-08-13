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

float_bits float_f2i(float_bits f) {
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	int k = 8;
	int n = 23;

	if (exp == 0xFF) {
		return INT_MIN;
	}
	if (exp == 0) {
		// Denormalizedも2倍する
		// frac <<= 1
	}
	// normalized
	// 2E * M
	int bias = (2 << k) - 1;

	int E = exp - bias;
	int F = frac / n;
	int M = 1 + F;
	return (2 << E) * M;
	// return (sign << 31) | (exp << 23) | frac;
}

int main() {
	printf("%d\n", float_f2i(0xFF));

	// for (unsigned i = 1; i < 0xFFFFFFFF ; i++)
	// {
	// 	unsigned fb_result = float_twice(i);
    //     float f = u2f(i);
    //     float f_result = 2.0f * f;
    //     unsigned standard_result = f2u(f_result);

    //     if (fb_result != standard_result) {
	// 		printf("Error at %u: fb_result = 0x%08X, standard_result = 0x%08X\n", i, fb_result, standard_result);

	// 		// printf("fabsf(i)                : %f\n", fabsf((float) i));
	// 		// printf("float_to_bits(fabsf((float) i)): %x\n", float_to_bits(fabsf((float) i)));
	// 		// printf("float_to_bits(fabsf((float) i)): %x\n", float_to_bits((float)float_absval(i)));

			
	// 		return 0;
	// 	}
	// 	// if ((float)float_negate(i) !=  (float) -i) {
	// 	// 	printf("incorrect i: %x\n", i);
	// 	// 	printf("float_negate(i): %f\n", float_negate(i));
	// 	// 	printf("- (float) i    : %f\n", (float)- i);
	// 	// 	return 0;
	// 	// }
	// }
	
	return 0;
}


/*
 * float-f2i.c
 */
#include <stdio.h>
#include <assert.h>

/*
 * Compute (float) f
 * If conversion cause overflow or f is NaN, return 0x80000000
 */
int float_f2i(float_bits f) {
  unsigned sig = f >> 31;
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  unsigned bias = 0x7F;

  int num;
  unsigned E;
  unsigned M;

  /*
   * consider positive numbers
   *
   * 0 00000000 00000000000000000000000
   *   ===>
   * 0 01111111 00000000000000000000000
   *   0 <= f < 1
   * get integer 0
   *
   * 0 01111111 00000000000000000000000
   *   ===>
   * 0 (01111111+31) 00000000000000000000000
   *   1 <= f < 2^31
   * integer round to 0
   *
   * 0 (01111111+31) 00000000000000000000000
   *   ===>
   * greater
   *   2^31 <= f < oo
   * return 0x80000000
   */
  if (exp >= 0 && exp < 0 + bias) {
    /* number less than 1 */
    num = 0;
  } else if (exp >= 31 + bias) {
    /* number overflow */
    /* or f < 0 and (int)f == INT_MIN */
    num = 0x80000000;
  } else {
    E = exp - bias;
    M = frac | 0x800000;
    if (E > 23) {
      num = M << (E - 23);
    } else {
      /* whether sig is 1 or 0, round to zero */
      num = M >> (23 - E);
    }
  }

  return sig ? -num : num;
}
