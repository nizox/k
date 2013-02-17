#include "c/heap.h"
#include "c/memory.h"
#include "c/types.h"

static uint64_t *heap = (uint64_t *)HEAPBASE;

void
*shlimit(int inc)
{
    uint64_t        *save = heap;

    heap += inc;
    if (heap < (uint64_t *)HEAPBASE || heap > (uint64_t *)HEAPLIMIT)
        goto err;

    return save;
err:
    heap = save;
    return (void *)-1;
}
