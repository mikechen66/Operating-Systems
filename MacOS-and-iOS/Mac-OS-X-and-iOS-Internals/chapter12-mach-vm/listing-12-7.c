// Listing 12-7 : Mach zones

struct zone {
        int             count;          /* Number of elements used now */
        vm_offset_t     free_elements;  // Linked list of free elements
        decl_lck_mtx_data(,lock)        /* zone lock */
        lck_mtx_ext_t   lock_ext;       /* placeholder for indirect mutex */
        lck_attr_t      lock_attr;      /* zone lock attribute */
        lck_grp_t       lock_grp;       /* zone lock group */
        lck_grp_attr_t  lock_grp_attr;  /* zone lock group attribute */
        vm_size_t       cur_size;       /* current memory utilization */
        vm_size_t       max_size;       /* how large can this zone grow */
        vm_size_t       elem_size;      /* size of an element */
        vm_size_t       alloc_size;     /* size used for more memory */
        uint64_t        sum_count;      /* count of allocs (life of zone) */
        // the following italicized fields can be changed with zone_change()
        unsigned int
        /* boolean_t */ exhaustible :1, /* (F) merely return if empty? */
        /* boolean_t */ collectable :1, /* (F) garbage collect empty pages */
        /* boolean_t */ expandable :1,  /* (T) expand zone (with message)? */
        /* boolean_t */ allows_foreign :1,/* (F) allow non-zalloc space */
        /* boolean_t */ doing_alloc :1, /* is zone expanding now? */
        /* boolean_t */ waiting :1,     /* is thread waiting for expansion? */
        /* boolean_t */ async_pending :1,/* asynchronous allocation pending? */
#if CONFIG_ZLEAKS
        /* boolean_t */ zleak_on :1,   /* Are we collecting allocation info? */
#endif  /* ZONE_DEBUG */  // they mean CONFIG_ZLEAKS — mistake in source 
        /* boolean_t */ caller_acct: 1,/* account allocation/free to caller? */  
        /* boolean_t */ doing_gc :1,    /* garbage collect in progress? */
        /* boolean_t */ noencrypt :1;
        int             index;  /* index into zone_info arrays for this zone */
        struct zone *   next_zone;      /* Link for all-zones list */
        call_entry_data_t  call_async_alloc; /* callout for asynch alloc */
        const char      *zone_name;     /* a name for the zone */
#if     ZONE_DEBUG
        queue_head_t    active_zones;   /* active elements */
#endif  /* ZONE_DEBUG */
#if CONFIG_ZLEAKS
        uint32_t num_allocs;    /* alloc stats for zleak benchmarks */
        uint32_t num_frees;     /* free stats for zleak benchmarks */
        uint32_t zleak_capture; /* per-zone counter for capturing every N allocations */
#endif /* CONFIG_ZLEAKS */
};