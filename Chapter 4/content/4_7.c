#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/*

%rspの元の値をプッシュしている

*/

int pushtest() {
	int result = 0;
	__asm__(
		"movq %%rsp, %%rax\n\t"
		"pushq %%rsp\n\t"
		"popq %%rdx\n\t"
		"subq %%rdx, %%rax\n\t"
		: "=a" (result) // 出力オペランド：%eaxの値をresultに格納
	);
	return result;
}

int main() {
	printf("%d\n", pushtest());
}