// Listing 12-2: A vm_map_entry

struct vm_map_entry {
        struct vm_map_links     links;          /* links to other entries */
#define vme_prev                links.prev
#define vme_next                links.next
#define vme_start               links.start
#define vme_end                 links.end
        struct vm_map_store     store;
        union vm_map_object     object;         /* object I point to */
        vm_object_offset_t      offset;         /* offset into object */
        unsigned int
        /* boolean_t */         is_shared:1,    /* region is shared */
        /* boolean_t */         is_sub_map:1,   /* Is “object” a submap? */
        /* boolean_t */         in_transition:1, /* Entry being changed */
        /* boolean_t */         needs_wakeup:1,  /* Waiters on in_transition */
        /* vm_behavior_t */     behavior:2,     /* user paging behavior hint */
                /* behavior is not defined for submap type */
        /* boolean_t */         needs_copy:1,   /* object need to be copied? */
                /* Only in task maps: */
        /* vm_prot_t */         protection:3,   /* protection code */
        /* vm_prot_t */         max_protection:3,/* maximum protection */
        /* vm_inherit_t */      inheritance:2,  /* inheritance */
        /* boolean_t */         use_pmap:1,     /* nested pmaps */
        /*
         * IMPORTANT:
         * The “alias” field can be updated while holding the VM map lock
         * “shared”.  It's OK as along as it's the only field that can be
         * updated without the VM map “exclusive” lock.
         */
        /* unsigned char */     alias:8,         /* user alias */
        /* boolean_t */         no_cache:1,      /* should new pages be cached? */
        /* boolean_t */         permanent:1,      /* mapping can not be removed */
        /* boolean_t */         superpage_size:3, /* use superpages of a certain size */
        /* boolean_t */         zero_wired_pages:1, // zero out wired pages on entry
                                                    // deletion 
        /* boolean_t */         used_for_jit:1,     // added for dynamic codesigning
                                                    // (iOS)
        /* unsigned char */     pad:1;            /* available bits */
        unsigned short          wired_count;      /* can be paged if = 0 */
        unsigned short          user_wired_count; /* for vm_wire */
};