/*

<<63 >> 63は偶数かどうか

subq	rsi = y - z
imulq	rdi = x * (y - z)
movq	rax = y - z
salq	rax = y - z << 63
sarq	rax = (y - z<<63) >> 63
xorq	rax = ((y - z<<63)>>63) ^ (x * (y - z))

*/

long decode2(long x, long y, long z) {
	return ((y-z) << 63) >> 63 * (x*y);
}