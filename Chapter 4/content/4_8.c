#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/*

%rspにメモリから読み出した値をセットする

*/

int poptest() {
	int result = 0;
	__asm__(
		"movq %%rsp, %%rdi\n\t"
		"pushq $0xabcd\n\t"
		"popq %%rsp\n\t"
		"movq %%rsp, %%rax\n\t"
		"movq %%rdi, %%rsp\n\t"
		: "=a" (result) // 出力オペランド：%eaxの値をresultに格納
	);
	return result;
}

int main() {
	printf("%x\n", poptest());
}