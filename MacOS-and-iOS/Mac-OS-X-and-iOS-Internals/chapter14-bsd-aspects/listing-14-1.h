// Listing 14-1: BSD malloc functions, from bsd/sys/malloc.h

extern void     *_MALLOC(size_t       size,
                          int         type,
                          int         flags); // M_NOWAIT or M_ZERO
extern void     _FREE(void           *addr,
                        int           type);
extern void     *_REALLOC(void       *addr,
                        size_t        size,
                        int           type,
                        int           flags);
extern void     *_MALLOC_ZONE(size_t  size,
                        int           type,
                        int           flags);
extern void     _FREE_ZONE(void      *elem,
                        size_t        size,
                        int           type);