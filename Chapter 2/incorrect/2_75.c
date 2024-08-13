#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

int signed_high_prod(int x, int y) {
  int64_t mul = (int64_t) x * y;
  printf("mul %llx\n", mul);
  return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
  /* TODO calculations */
  int sig_x = x >> 31;
  int sig_y = y >> 31;
  int signed_prod = signed_high_prod(x, y);
  printf("signed_prod %x\n", signed_prod);
  printf("%x\n", signed_prod + x * sig_y + y * sig_x);
  return signed_prod + x * sig_y + y * sig_x;
}

/* a theorically correct version to test unsigned_high_prod func */
unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
  uint64_t mul = (uint64_t) x * y;
  printf("another %llx\n", mul);
  return mul >> 32;
}

int main(int argc, char* argv[]) {
  unsigned x = 0x12345678;
  unsigned y = 0xFFFFFFFF;

  printf("%x\n", x * y);

  assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));
  return 0;
}