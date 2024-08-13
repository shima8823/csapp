// 面白い

#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// A. K =   17: (1 << 4) + 1 
int A(int x) {
	return (x << 4) + x;
}

// B. K =   -7: (1 << 3) + 1
int B(int x) {
	return x - (x << 3);
}


// C. K =   60:
// x = 2: 0010
// 0111 1000 : 120
//   1000 0000
// - 0000 1000
//   0111 1000


int C(int x) {
	// x == 1
	// 64 - 4
	return (x << 6) - (x << 2);
}	

// D. K = -112: 
int D(int x) {
	// x == 1
	// 16 - 128 
	// (1 << 4) - (1 << 7)  
	return (x << 4) - (x << 7);
}

int main() {
	assert(A(2) == 34);
	assert(B(2) == -14);
	assert(C(2) == 120);
	assert(D(2) == -224);

	return 0;
}