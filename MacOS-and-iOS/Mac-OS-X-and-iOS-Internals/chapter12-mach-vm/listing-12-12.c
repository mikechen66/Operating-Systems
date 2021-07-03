// Listing 12-12: OSMalloc tags

typedef struct _OSMallocTag_ {
    queue_chain_t   OSMT_link;
    uint32_t        OSMT_refcnt;
    uint32_t        OSMT_state;
    uint32_t        OSMT_attr;
    char            OSMT_name[OSMT_MAX_NAME];
} * OSMallocTag;