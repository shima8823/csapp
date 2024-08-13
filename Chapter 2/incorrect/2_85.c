// つまらん
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *byte_pointer;
/*
bias = 2^(k-1) - 1
V = 2^E * M


A: E = e{k-1}, ... e{1}, e{0} 0000....01
   M = 000...111
   f = 000...000
   V = 7

A correct: 7.0 = 0b111.000…
M = 0b1.11, f = 0b0.11, E = 2, e = bias + E, V = 7.0

bits
0 10....01 110....

B: 
Assume bias » n
bigest odd number, M must be 0b1.111111…., f = 0b0.11111111…(n bits 1)
E = n, V = 0b11111111…(n+1 bits 1) = 2^(n+1) - 1
bits
0 bias+n 11111....

C: 最小の正の正規化数の逆数
e = 1, E = 1 - (k + n), 2E = M = 1 e

least standard number

M must be 0b1.00…., f = 0b0.000…., E = 1 - bias

V = 2^(1-bias)

reciprocal

V = 2^(bias-1)

M = 0b1.0000…, f = 0b0.000…., E = bias-1, e = bias + E

bits

0 11...101 00000.....


*/

int main() {
	return 0;
}