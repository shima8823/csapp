#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char *byte_pointer;

// malloc, memset

void *calloc(size_t nmemb, size_t size) {
	if (nmemb == 0 || size == 0)
		return NULL;

	size_t mul = nmemb * size;
	if (mul / nmemb != size)
		return NULL;
	void *dest = malloc(mul);
	if (!dest) return NULL;
	memset(dest, 0, mul);
	return dest;
}

int main() {
	void* p;
  p = calloc(0x1234, 1);
  assert(p != NULL);
  free(p);

  p = calloc(SIZE_MAX, 1);
  assert(p == NULL);
  free(p);
  return 0;
	return 0;
}