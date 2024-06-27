#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/*

*/

int main() {
	int a = 1;
	int b = 0;

	bool xor = (a && !b) || (!a && b);

	// xor * 64
	// xorの結果が!eq -> or -> not
}
