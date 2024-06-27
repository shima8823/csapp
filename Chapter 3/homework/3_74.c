/*



*/

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x) {
	range_t result;
	__asm__(
		"vxorps %%xmm1, %%xmm1, %%xmm1\n\t"
		"vucomiss %%xmm0, %%xmm1\n\t" // 0 cmp x
        "movl $0, %%ecx\n\t" // NEG
        "movl $1, %%edx\n\t" // ZERO
		"movl $2, %%eax\n\t" // POS
        "movl $3, %%esi\n\t" // OTHER
		"cmoval %%ecx, %%eax\n\t"
		"cmovel %%edx, %%eax\n\t"
		"cmovpl %%esi, %%eax\n\t"
		: "=a" (result) // 出力オペランド：%eaxの値をresultに格納
        : "x" (x)       // 入力オペランド：xを%xmm0に格納
        : "xmm1"  
    );
	return result;
}

#include <stdio.h>
int main(int ac, char **av) {
	printf("%s\n", (find_range(0.0) == ZERO ? "true" : "false"));
	printf("%s\n", (find_range(-1) == NEG ? "true" : "false"));
	printf("%s\n", (find_range(1) == POS ? "true" : "false"));
	printf("%s\n", (find_range(0.0 /0.0) == OTHER ? "true" : "false"));
	return 0;
}