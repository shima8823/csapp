/*
面白い

A. code
B. i = 64で初期化されていて、条件式であるi!=0であるのは明らかだから。
C. 鏡像を作るかのようにビットを反転させている.
	x = 1 100000....0
	x = 2 010000....0
	x = 3 110000....0
	x = 9 100100....0
	x =10 010100....0

*/

// long fun_b(unsigned long x) {
// 	long val = 0;
// 	long i;
// 	for (i = 64; i > 0; i--) {
// 		unsigned long rcx = x;
// 		rcx = rcx & 0x1;
// 		val += val;
// 		val |= rcx;
// 		x >>= 1;
// 	}
// 	return val;
// }

long fun_b(unsigned long x) {
	long val = 0;
	long i;
	for (i = 64; i > 0; i--) {
		val = (val << 1) | (x & 0x1);
		x >>= 1;
	}
	return val;
}


#include <stdio.h>
void printBits(long num) {
    // 各ビットを出力するためのマスク
    unsigned long mask = 1UL << (sizeof(long) * 8 - 1);

    // マスクを用いてビットをチェック
    for (int i = 0; i < sizeof(long) * 8; i++) {
        // ビットが1か0かをチェックして出力
        if (num & mask) {
            printf("1");
        } else {
            printf("0");
        }
        // マスクを右に1ビットシフト
        mask >>= 1;
    }
}
int main() {
	for (long i = 0; i < 11; i++)
	{
		long ans = fun_b(i);
		printBits(ans);
		printf(": %ld\n", ans);
	}
	
}