// Listing 12-1: The vm_map struct

struct vm_map_header {
        struct vm_map_links     links;          /* first, last, min, max */
        int                     nentries;       /* Number of entries */
        boolean_t               entries_pageable;
                                                /* are map entries pageable? */
        vm_map_offset_t         highest_entry_end_addr; /* The ending address of the 
                                                        /* highest allocated 
                                                        /* vm_entry_t */
#ifdef VM_MAP_STORE_USE_RB
        struct rb_head  rb_head_store;
#endif
};
struct _vm_map {
        lock_t                lock;           /* uni- and smp-lock */
        struct vm_map_header  hdr;            /* Map entry header */
#define min_offset            hdr.links.start /* start of range */
#define max_offset            hdr.links.end   /* end of range */
#define highest_entry_end     hdr.highest_entry_end_addr
        pmap_t                pmap;           /* Physical map */
        vm_map_size_t         size;           /* virtual size */
        vm_map_size_t         user_wire_limit;/* rlimit on user locked memory */
        vm_map_size_t         user_wire_size; /* current size of user locked memory in
                                              /* this map*/
        int                   ref_count;      /* Reference count */
#if     TASK_SWAPPER
        int                   res_count;      /* Residence count (swap) */
        int                   sw_state;       /* Swap state */
#endif  /* TASK_SWAPPER */
        decl_lck_mtx_data(,   s_lock)         /* Lock ref, res fields */
        lck_mtx_ext_t         s_lock_ext;
        vm_map_entry_t        hint;           /* hint for quick lookups */
        vm_map_entry_t        first_free;     /* First free space hint */
        unsigned int            
        /* boolean_t */       wait_for_space:1,  /* Should callers wait for space? */
        /* boolean_t */       wiring_required:1, /* All memory wired? */
        /* boolean_t */       no_zero_fill:1,    /* No zero fill absent pages */
        /* boolean_t */       mapped:1,          /*has this map been mapped */
        /* boolean_t */       switch_protect:1,  /* Protect from write faults while
                                                 /* switched */
        /* boolean_t */       disable_vmentry_reuse:1, // entry alloc. Monotonically
                                                       // increases 
        /* boolean_t */       map_disallow_data_exec:1,// set NX bit, if possible
        /* reserved */        pad:25;
        unsigned int          timestamp;      /* Version number */
        unsigned int          color_rr;       /* next color (not protected by a lock) */
#if CONFIG_FREEZE // default freezer — we get to that later.
        void                  *default_freezer_toc;
#endif
        boolean_t             jit_entry_exists; // used for dynamic codesigning (iOS)
} ;