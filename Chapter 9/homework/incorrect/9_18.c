// --- mm.c	2021-02-25 07:26:33.315926002 +0000
// +++ mm.9.18.c	2021-02-25 07:26:33.315926002 +0000
// @@ -20,7 +20,7 @@
//  #define MAX(x, y) ((x) > (y)? (x) : (y))
 
//  /* Pack a size and allocated bit into a word */
// -#define PACK(size, alloc)  ((size) | (alloc)) //line:vm:mm:pack
// +#define PACK(size, alloc, prev_alloc)  ((size) | (alloc) | (prev_alloc << 1)) //line:vm:mm:pack
 
//  /* Read and write a word at address p */
//  #define GET(p)       (*(unsigned int *)(p))            //line:vm:mm:get
// @@ -29,6 +29,7 @@
//  /* Read the size and allocated fields from address p */
//  #define GET_SIZE(p)  (GET(p) & ~0x7)                   //line:vm:mm:getsize
//  #define GET_ALLOC(p) (GET(p) & 0x1)                    //line:vm:mm:getalloc
// +#define GET_PREV_ALLOC(p) ((GET(p) >> 1) & 0x1)
 
//  /* Given block ptr bp, compute address of its header and footer */
//  #define HDRP(bp)       ((char *)(bp) - WSIZE)                      //line:vm:mm:hdrp
// @@ -63,9 +64,9 @@
//    if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1) //line:vm:mm:begininit
//      return -1;
//    PUT(heap_listp, 0);                          /* Alignment padding */
// -  PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); /* Prologue header */
// -  PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); /* Prologue footer */
// -  PUT(heap_listp + (3*WSIZE), PACK(0, 1));     /* Epilogue header */
// +  PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1, 1)); /* Prologue header */
// +  PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1, 1)); /* Prologue footer */
// +  PUT(heap_listp + (3*WSIZE), PACK(0, 1, 1));     /* Epilogue header */
//    heap_listp += (2*WSIZE);                     //line:vm:mm:endinit
//    /* $end mminit */
 
// @@ -98,10 +99,10 @@
//      return NULL;
 
//    /* Adjust block size to include overhead and alignment reqs. */
// -  if (size <= DSIZE)                                          //line:vm:mm:sizeadjust1
// -    asize = 2*DSIZE;                                        //line:vm:mm:sizeadjust2
// +  if (size <= WSIZE)
// +    asize = DSIZE;
//    else
// -    asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE); //line:vm:mm:sizeadjust3
// +    asize = DSIZE * ((size + (WSIZE) + (DSIZE-1)) / DSIZE); //line:vm:mm:sizeadjust3
 
//    /* Search the free list for a fit */
//    if ((bp = find_fit(asize)) != NULL) {  //line:vm:mm:findfitcall
// @@ -136,8 +137,16 @@
//    }
//    /* $begin mmfree */
 
// -  PUT(HDRP(bp), PACK(size, 0));
// -  PUT(FTRP(bp), PACK(size, 0));
// +  PUT(HDRP(bp), PACK(size, 0, GET_PREV_ALLOC(HDRP(bp))));
// +  PUT(FTRP(bp), PACK(size, 0, GET_PREV_ALLOC(HDRP(bp))));
// +
// +  if (GET_ALLOC(HDRP(NEXT_BLKP(bp))))
// +    PUT(HDRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 1, 0));
// +  else {
// +    PUT(HDRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 0, 0));
// +    PUT(FTRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 0, 0));
// +  }
// +
//    coalesce(bp);
//  }
 
// @@ -148,7 +157,7 @@
//  /* $begin mmfree */
//  static void *coalesce(void *bp)
//  {
// -  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
// +  size_t prev_alloc = GET_PREV_ALLOC(HDRP(bp));
//    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
//    size_t size = GET_SIZE(HDRP(bp));
 
// @@ -158,22 +167,22 @@
 
//    else if (prev_alloc && !next_alloc) {      /* Case 2 */
//      size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
// -    PUT(HDRP(bp), PACK(size, 0));
// -    PUT(FTRP(bp), PACK(size,0));
// +    PUT(HDRP(bp), PACK(size, 0, 1));
// +    PUT(FTRP(bp), PACK(size, 0, 1));
//    }
 
//    else if (!prev_alloc && next_alloc) {      /* Case 3 */
//      size += GET_SIZE(HDRP(PREV_BLKP(bp)));
// -    PUT(FTRP(bp), PACK(size, 0));
// -    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
// +    PUT(FTRP(bp), PACK(size, 0, 1));
// +    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0, 1));
//      bp = PREV_BLKP(bp);
//    }
 
//    else {                                     /* Case 4 */
//      size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
//        GET_SIZE(FTRP(NEXT_BLKP(bp)));
// -    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
// -    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
// +    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0, 1));
// +    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0, 1));
//      bp = PREV_BLKP(bp);
//    }
//    /* $end mmfree */
// @@ -246,9 +255,9 @@
//      return NULL;                                        //line:vm:mm:endextend
 
//    /* Initialize free block header/footer and the epilogue header */
// -  PUT(HDRP(bp), PACK(size, 0));         /* Free block header */   //line:vm:mm:freeblockhdr
// -  PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */   //line:vm:mm:freeblockftr
// -  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */ //line:vm:mm:newepihdr
// +  PUT(HDRP(bp), PACK(size, 0, GET_PREV_ALLOC(HDRP(bp))));         /* Free block header */   //line:vm:mm:freeblockhdr
// +  PUT(FTRP(bp), PACK(size, 0, GET_PREV_ALLOC(HDRP(bp))));         /* Free block footer */   //line:vm:mm:freeblockftr
// +  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1, 0)); /* New epilogue header */ //line:vm:mm:newepihdr
 
//    /* Coalesce if the previous block was free */
//    return coalesce(bp);                                          //line:vm:mm:returnblock
// @@ -267,15 +276,14 @@
//    size_t csize = GET_SIZE(HDRP(bp));
 
//    if ((csize - asize) >= (2*DSIZE)) {
// -    PUT(HDRP(bp), PACK(asize, 1));
// -    PUT(FTRP(bp), PACK(asize, 1));
// +    PUT(HDRP(bp), PACK(asize, 1, 1));
//      bp = NEXT_BLKP(bp);
// -    PUT(HDRP(bp), PACK(csize-asize, 0));
// -    PUT(FTRP(bp), PACK(csize-asize, 0));
// +    PUT(HDRP(bp), PACK(csize-asize, 0, 1));
// +    PUT(FTRP(bp), PACK(csize-asize, 0, 1));
//    }
//    else {
// -    PUT(HDRP(bp), PACK(csize, 1));
// -    PUT(FTRP(bp), PACK(csize, 1));
// +    PUT(HDRP(bp), PACK(csize, 1, 1));
// +    PUT(HDRP(NEXT_BLKP(bp)), PACK(csize, 1, 1));
//    }
//  }
//  /* $end mmplace */
