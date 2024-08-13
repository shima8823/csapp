#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

unsigned f2u(float x) {
	return (unsigned) x;
}

// x <= y
int float_le(float x, float y) {
	unsigned ux = f2u(x);
	unsigned uy = f2u(y);

	unsigned sx = ux >> 31;
	unsigned sy = uy >> 31;

	//      -x       && +y        || +x        && -y        || 
	// return (sx & 0x0 && sy & 0x1) || (sx & 0x1 && sy & 0x0)

	return (ux << 1 == 0 && uy << 1 == 0) || /* both zeros */
    (sx && !sy) ||                         /* x < 0, y >= 0 or x <= 0, y > 0 */
    (!sx && !sy && ux <= uy) ||            /* x > 0, y >= 0 or x >= 0, y > 0 */
    (sx && sy && ux >= uy);                /* x < 0, y <= 0 or x <= 0, y < 0 */
}

int main() {
	assert(float_le(-0, +0));
  assert(float_le(+0, -0));
  assert(float_le(0, 3));
  assert(float_le(-4, -0));
  assert(float_le(-4, 4));
	return 0;
}