// Listing 12-9: Some of the kalloc functions in osfmk/kern/kalloc.h

extern void *kalloc(vm_size_t   size);
extern void *kalloc_noblock(vm_size_t   size);
extern void  kfree(void *data, vm_size_t size);