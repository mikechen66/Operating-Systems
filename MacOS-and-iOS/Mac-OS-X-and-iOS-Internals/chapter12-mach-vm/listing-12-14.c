// Listing 12-14: The Universal Page List
struct upl {
        decl_lck_mtx_data(,     Lock)   /* Synchronization */
        int             ref_count;
        int             ext_ref_count;
        int             flags;
        vm_object_t     src_object; /* object derived from */
        vm_object_offset_t offset;
        upl_size_t      size;       /* size in bytes of the address space */
        vm_offset_t     kaddr;      /* secondary mapping in kernel */
        vm_object_t     map_object;
        ppnum_t         highest_page;
        void*           vector_upl;
#if     UPL_DEBUG
        uintptr_t       ubc_alias1;
        uintptr_t       ubc_alias2;
        queue_chain_t   uplq;       /* List of outstanding upls on an obj */
        thread_t        upl_creator;
        uint32_t        upl_state;
        uint32_t        upl_commit_index;
        void    *upl_create_retaddr[UPL_DEBUG_STACK_FRAMES];
        struct  ucd     upl_commit_records[UPL_DEBUG_COMMIT_RECORDS];
#endif  /* UPL_DEBUG */
};