// 面白い

#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

int A(int k) {
	return -1 << k;
}

int B(int k, int j) {
  return ~A(k) << j;
	// 8bit 00000000 
}

int main() {
	printf("%d\n", A(4) == 0xFFFFFFF0);
	printf("%d\n", A(0) == 0xFFFFFFFF);
	printf("%d\n", B(16, 8) == 0x00FFFF00);
	printf("%x\n", B(16, 8));
	

	

	
	return 0;
}