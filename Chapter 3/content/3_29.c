/*

A. iがインクリメントされないので永遠にループする。
B. 

*/


long sum_even_for() {
	long sum = 0;
	long i;
	for (i = 0; i < 10; i++)
	{
		if (i & 1)
			continue;
		sum += i;
	}
	return sum;
}
long sum_even_while() {
	long sum = 0;
	long i = 0;
	while (i < 10) {
		if (i & 1)
			goto increment;
		sum += i;
	increment:
		i++;
	}
	return sum;
}

#include <stdio.h>
int main() {
	printf("%ld\n", sum_even_for());
	printf("%ld\n", sum_even_while());
}