#include <stdlib.h>

void *basic_memset(void *s, int c, size_t n) {
	size_t k = sizeof(unsigned long);
	size_t cnt;
	unsigned char *schar = s;
	for (cnt = 0; cnt + (k-1) < n; cnt += k) {
		unsigned char uc_c = (unsigned char) c;
		unsigned int pack = 0;
		pack |= uc_c;pack <<= 1;
		pack |= uc_c;pack <<= 1;
		pack |= uc_c;pack <<= 1;
		pack |= uc_c;pack <<= 1;
		pack |= uc_c;pack <<= 1;
		pack |= uc_c;pack <<= 1;
		pack |= uc_c;pack <<= 1;
		pack |= uc_c;
		*schar = pack;
		schar += k;
	}
	
	for (; cnt < n; cnt++) {
		*schar++ = (unsigned char) c;
	}
	return s;
}


/*
 * K = sizeof(unsigned long)
 * cs store K chars for memset
 */
void* effective_memset(void *s, unsigned long cs, size_t n) {
  /* align to K */
  size_t K = sizeof(unsigned long);
  size_t cnt = 0;
  unsigned char *schar = s;
  while (cnt < n) {
    if ((size_t)schar % K == 0) {
      break;
    }
    *schar++ = (unsigned char)cs;
    cnt++;
  }

  /* set K chars one time */
  unsigned long *slong = (unsigned long *)schar;
  size_t rest = n - cnt;
  size_t loop = rest / K;
  size_t tail = rest % K;

  for (size_t i = 0; i < loop; i++) {
    *slong++ = cs;
  }

  /* pad the tail part */
  schar = (unsigned char *)slong;
  for (size_t i = 0; i < tail; i++) {
    *schar++ = (unsigned char)cs;
  }
  return s;
}
