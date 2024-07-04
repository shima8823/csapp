/*

A.	rsp以外は正確に記述している。なぜならデクリメントされた値が代入されているから。
B.	code

*/

#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
int pushtest() {
	int result = 0;
	__asm__(
		"movq %%rsp, %%rax\n\t"

		// nomral Registerの場合
		// "movq %%rsp, %%rcx\n\t"
		// // "pushq %%rsp\n\t"
		// "subq $8, %%rsp\n\t"
		// "movq %%rcx, (%%rsp)\n\t"


		// rspの場合
		"movq %%rsp, %%rdi\n\t"
		// "pushq %%rsp\n\t"
		"movq %%rdi, %%rcx\n\t" // tmp
		"subq $8, %%rsp\n\t" // rsp = 120, rsp = 120 - 8 = 112
		"movq %%rcx, (%%rdi)\n\t" // rsp = 112
		// "movq %%rcx, (%%rsp)\n\t" // tmp

		// answer rspの場合"にも"対応する場合
		"movq %%rsp, -8(%%rsp)\n\t"
		"subq $8, %%rsp\n\t"
		

		"popq %%rdx\n\t"
		"subq %%rdx, %%rax\n\t" // 120 - 112 = 8 // 120 - 136
		: "=a" (result) // 出力オペランド：%eaxの値をresultに格納
	);
	return result;
}
		// "movq %%rsp, %%rcx\n\t"
		// "addq $8, %%rsp\n\t"

int main() {
	printf("%d\n", pushtest());
}