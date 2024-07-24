#include <stdio.h>
void f(void);

int x = 15212;
int y = 15213;

int main() {
	f();
	printf("x = 0x%x y = 0x%x \n", x, y);
	return 0;
}
