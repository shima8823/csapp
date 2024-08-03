// 似たような答え

#include <stdio.h>
#include <stdlib.h>

static char *mem_heap;     /* Points to first byte of heap */ 
static char *heap_listp;     /* Points to first byte of heap */ 

static void place(void *bp, size_t asize) {
	size_t free_block = GET_SIZE(HDRP(heap_listp));

	for (size_t i = 0; i < asize; i++) {
		heap_listp[i] = ((char*)bp)[i];
	}

	if (free_block - asize >= DSIZE) {
		// sizeを変えてごにょごにょする
	}

}

// answer
static void place(void *bp, size_t asize) {
    size_t csize = GET_SIZE(HDRP(bp));   

    if ((csize - asize) >= (2*DSIZE)) { 
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));
    }
    else { 
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}
