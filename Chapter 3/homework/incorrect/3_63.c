/*
面白い


*/


long switch_prob(long x, long n) {
	long result = x;
	// n -= 0x3c;
	// n -= 60
	// n > 5

	switch (n) {
		case 60: // a1
		case 62: // a1
			result = x * 8;
			break;
		case 63: // aa
			result >>= 3;
			break;
		case 64: // b2
			x = (result << 4) - x;
		case 65: // bf
			x *= x;
		default : // c3
			result = 0x4B + x;
	}
	return result;
}
