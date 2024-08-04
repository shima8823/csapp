#include <stdio.h>
#include <stdlib.h>

static char *searched_pointer;
static char *heap_listp;	 /* Points to first byte of heap */ 

static void *find_next_fit(size_t asize) {
	void *bp;

	if (!searched_pointer) {
		searched_pointer = heap_listp;
	}

	for (bp = searched_pointer; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
		if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
			searched_pointer = bp;
			return bp;
		}
	}

	return find_fit(asize);
} 
