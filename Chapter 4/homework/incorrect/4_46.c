/*

A.	rsp以外は正確に記述してる(movqも変更しないといけないが)。
B.	code

*/

#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
int poptest() {
	int result = 0;
	__asm__(
		"movq %%rsp, %%rdi\n\t"
		"pushq $0xabcd\n\t"


		// "popq %%rcx\n\t"
		// "movq (%%rsp), %%rsp\n\t"
		// "addq $8, %%rsp\n\t"

		// "popq %%rsp\n\t"
		// "movq (%%rsp), %%r8\n\t"
		// "addq $8, %%rsp\n\t"
		// "movq %%r8, %%rsp\n\t"

		// answer
		"addq $8, %%rsp\n\t"
		"movq -8(%%rsp), %%rsp\n\t"




		"movq %%rsp, %%rax\n\t"
		"movq %%rdi, %%rsp\n\t"
		: "=a" (result) // 出力オペランド：%eaxの値をresultに格納
	);
	return result;
}

int main() {
	printf("%x\n", poptest());
}