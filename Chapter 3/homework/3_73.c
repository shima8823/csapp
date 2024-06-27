/*



*/

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x) {
	range_t result;
	__asm__(
		"vxorps %%xmm1, %%xmm1, %%xmm1\n\t"
		"vucomiss %%xmm0, %%xmm1\n\t" // 0 cmp x
		"ja .ne\n\t"
		"jp .na\n\t"
		"je .ze\n\t"
		"jb .po\n\t"
		".na:\n\t"
		"movl $3, %%eax\n\t"
		"jmp .done\n"
		".ne:\n\t"
		"movl $0, %%eax\n\t"
		"jmp .done\n"
		".ze:\n\t"
		"movl $1, %%eax\n\t"
		"jmp .done\n"
		".po:\n\t"
		"movl $2, %%eax\n\t"
		".done:\n\t"
		: "=a" (result) // 出力オペランド：%eaxの値をresultに格納
        : "x" (x)       // 入力オペランド：xを%xmm0に格納
        : "xmm1"  
    );
	return result;
}

// range_t find_range(float x) {
//   __asm__(
//       "vxorps %xmm1, %xmm1, %xmm1\n\t"
//       "vucomiss %xmm1, %xmm0\n\t"
//       "jp .P\n\t"
//       "ja .A\n\t"
//       "jb .B\n\t"
//       "je .E\n\t"
//       ".A:\n\t"
//       "movl $2, %eax\n\t"
//       "jmp .Done\n\t"
//       ".B:\n\t"
//       "movl $0, %eax\n\t"
//       "jmp .Done\n\t"
//       ".E:\n\t"
//       "movl $1, %eax\n\t"
//       "jmp .Done\n\t"
//       ".P:\n\t"
//       "movl $3, %eax\n\t"
//       ".Done:\n\t"
//       );
// }


#include <stdio.h>
int main(int ac, char **av) {
	range_t n = NEG, z = ZERO, p = POS, o = OTHER;
	printf("%s\n", (o == find_range(0.0/0.0) ? "true" : "false"));
	printf("%s\n", (n == find_range(-2.3) ? "true" : "false"));
	printf("%s\n", (z == find_range(0.0) ? "true" : "false"));
	printf("%s\n", (p == find_range(3.33) ? "true" : "false"));
	// printf("%s\n", (find_range(0.0) == ZERO ? "true" : "false"));
	// printf("%s\n", (find_range(-1) == NEG ? "true" : "false"));
	// printf("%s\n", (find_range(1) == POS ? "true" : "false"));
	// printf("%s\n", (find_range(0.0 /0.0) == OTHER ? "true" : "false"));
	return 0;
}