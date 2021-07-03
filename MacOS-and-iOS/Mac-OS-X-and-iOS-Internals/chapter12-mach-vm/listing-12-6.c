// Listing 12-6: The Intel pmap_t implementation:

struct pmap {
        decl_simple_lock_data(,lock)    /* lock on map */
        pmap_paddr_t    pm_cr3;         /* physical addr */
        boolean_t       pm_shared;
        pd_entry_t      *dirbase;       /* page directory pointer */
#ifdef __i386__
        pmap_paddr_t    pdirbase;       /* phys. address of dirbase */
        vm_offset_t     pm_hold;        /* true pdpt zalloc addr */
#endif
        vm_object_t     pm_obj;         /* object to hold pde's */
        task_map_t      pm_task_map;
        pdpt_entry_t    *pm_pdpt;       /* KVA of 3rd level page */
        pml4_entry_t    *pm_pml4;       /* VKA of top level */
        vm_object_t     pm_obj_pdpt;    /* holds pdpt pages */
        vm_object_t     pm_obj_pml4;    /* holds pml4 pages */
#define PMAP_PCID_MAX_CPUS      (48)    /* Must be a multiple of 8 */
        pcid_t          pmap_pcid_cpus[PMAP_PCID_MAX_CPUS];
        volatile uint8_t pmap_pcid_coherency_vector[PMAP_PCID_MAX_CPUS];
        struct pmap_statistics  stats;  /* map statistics */
        int             ref_count;      /* reference count */
        int             nx_enabled;     // Data Execution Prevention
};