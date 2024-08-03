// 似たような答え

#include <stdio.h>
#include <stdlib.h>

static char *mem_heap;     /* Points to first byte of heap */ 
static char *heap_listp;     /* Points to first byte of heap */ 

static void *find_fit(size_t asize) {
	char *p = mem_heap;
	while ((p = NEXT_BLKP(p))) {
		if (!GET_ALLOC(p) && GET_SIZE(p) >= asize)
			return p;
	}
	return NULL;
}

// answer
static void *find_fit(size_t asize) {
	void *bp;

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            return bp;
        }
    }
    return NULL;
}
