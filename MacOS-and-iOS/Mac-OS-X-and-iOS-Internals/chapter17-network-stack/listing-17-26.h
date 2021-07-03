// Listing 17-26: The dummynet heap implementation from bsd/netinet/ip_dummynet.h

struct dn_heap_entry {
    dn_key key ;        /* sorting key. Topmost element is smallest one */
    void *object ;      /* object pointer */
} ;

struct dn_heap {
    int size ;
    int elements ;
    int offset ; /* XXX if > 0 this is the offset of direct ptr to obj */
    struct dn_heap_entry *p ;   /* really an array of “size” entries */
} ;