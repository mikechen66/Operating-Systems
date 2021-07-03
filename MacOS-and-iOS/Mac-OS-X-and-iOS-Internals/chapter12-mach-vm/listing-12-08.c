// Listing 12-8: kernel_memory_allocate(), from osfmk/vm/vm_kern

/*
 * Master entry point for allocating kernel memory.
 * NOTE: this routine is _never_ interrupt safe.
 *
 * map          : map to allocate into
 * addrp        : pointer to start address of new memory
 * size         : size of memory requested
 * flags        : options
 *                KMA_HERE              *addrp is base address, else “anywhere”
 *                KMA_NOPAGEWAIT        don't wait for pages if unavailable
 //                                     (returns KERN_RESOURCE_SHORTAGE instead)
 *                KMA_KOBJECT           use kernel_object
 *                KMA_LOMEM             support for 32 bit devices in a 64 bit world
 *                                      if set and a lomemory pool is available
 *                                      grab pages from it... this also implies
 *                                      KMA_NOPAGEWAIT
 //   And also:
 //               KMA_NOENCRYPT          Do not encrypt the pages (calls
 //               pmap_set_noencrypt())
 //               KMA_GUARD_[FIRST|LAST] Place guard pages before or after the
 //               allocation
 */
kern_return_t kernel_memory_allocate(
        register vm_map_t       map,
        register vm_offset_t    *addrp,
        register vm_size_t      size,
        register vm_offset_t    mask,
        int                     flags);