/* Copyright (C) 2023 Ray Chason, see COPYING.DJ for details */

#include <stdlib.h>
#include <malloc.h>

void *memalign(size_t alignment, size_t size)
{
    return aligned_alloc(alignment, size);
}
