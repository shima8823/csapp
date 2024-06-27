/*

*/


void switcher(long a, long b, long c, long *dest) {
	long val;
	switch (a) {
		case 5: // A
			// .L7
			c = b ^ 15;
			// Fall through
		case 0: // B
			//  L3
			val = c + 112;
			break;
		case 2: // C
		case 7: // D
			// L5
			val = (b+c) << 2;
			break;
		case 4: // E
			val = a;
			break;
		default: // 1,3,6
			val = b;
	}
	// .L6
	*dest = val;
}