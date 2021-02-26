#include <kernel/atag.h>

uint32_t get_mem_size(atag_t * tag) {
#ifdef machine
    while (tag->tag != NONE) {
        if (tag->tag == MEM) {
            return tag->mem.size;
        }
        tag = ((uint32_t *)tag) + tag->tag_size;
    }
#else
    /* We're inside of a VM. */
    return 1024 * 1024 * 128;
#endif
}