/*



*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *lgets(char *s) {
	int c;
	char *dest = s;
	while ((c = getchar()) != '\n' && c != EOF)
		*dest++ = c;
	if (c == EOF && dest == s)
		return NULL;
	*dest++ = '\0';
	return s;
}

void echo() {
	char buf[8];
	lgets(buf);
	puts(buf);
}