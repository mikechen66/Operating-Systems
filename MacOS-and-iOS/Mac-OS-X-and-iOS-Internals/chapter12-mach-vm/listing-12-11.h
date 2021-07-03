// Listing 12-11: OSMalloc functions, as defined in libkern/libkern/OSMalloc.h

typedef struct __OSMallocTag__ * OSMallocTag;
// First get a tag — this actually uses kalloc() 
extern OSMallocTag OSMalloc_Tagalloc(const char * name,
                                     uint32_t flags);
// Then allocate with it:
extern void * OSMalloc(uint32_t size, OSMallocTag tag);
// The following two are equivalent:
extern void * OSMalloc_nowait(uint32_t size, OSMallocTag tag);
extern void * OSMalloc_noblock (uint32_t size, OSMallocTag tag);
// Freeing memory requires the tag, as well:
extern void OSFree(void      * addr, uint32_t    size, OSMallocTag tag);
// Finally, free tag
extern void OSMalloc_Tagfree(OSMallocTag tag);