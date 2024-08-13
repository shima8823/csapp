// 面白い問題

#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;

// 0xFF00: 1111 1111
// 0x8000: 1000 0000

// 0x6600: 0110 0110
// 0x4000: 0100 0000

int leftmost_one(unsigned x) {
  /*
   * first, generate a mask that all bits after leftmost one are one
   * e.g. 0xFF00 -> 0xFFFF, and 0x6000 -> 0x7FFF
   * If x = 0, get 0
   */

  // 0x6600:
// 0110 0110
// 0011 0011
// 0111 0111
  x |= x >> 1;

// 0111 0111 0000 0000
// 0001 1101 1100 0000
// 0111 1111 1100 0000
  x |= x >> 2;

// 0111 1111 1100 0000
// 0000 0111 1111 1100

  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  /*
   * then, do (mask >> 1) + (mask && 1), in which mask && 1 deals with case x = 0, reserve leftmost bit one
   * that's we want
   */

// x: 0x7fff 0111 1111 .... 1111
// x >> 1: 0011 1111 .... 1111
// x &  1: 0000 .... 0001
  return (x >> 1) + (x && 1);
}

int main(int argc, char* argv[]) {
  assert(leftmost_one(0xFF00) == 0x8000);
  assert(leftmost_one(0x6000) == 0x4000);
  assert(leftmost_one(0x0) == 0x0);
  assert(leftmost_one(0x80000000) == 0x80000000);
  return 0;
}