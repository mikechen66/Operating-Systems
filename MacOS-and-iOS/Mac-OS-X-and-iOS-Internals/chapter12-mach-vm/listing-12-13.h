// Listing 12-13: Memory objects, as defined in osfmk/memory_object_types.h

/*
 * Temporary until real EMMI version gets re-implemented
 */

#ifdef KERNEL_PRIVATE
struct memory_object_pager_ops; /* forward declaration */
typedef struct          memory_object {
        unsigned int    _pad1; /* struct ipc_object_header */
#ifdef __LP64__
        unsigned int    _pad2; /* pad to natural boundary */
#endif
        const struct memory_object_pager_ops    *mo_pager_ops;
} *memory_object_t;
typedef struct          memory_object_control {
        unsigned int    moc_ikot;  /* struct ipc_object_header. Must be 
                                   /* IKOT_MEM_OBJ_CONTROL */
#ifdef __LP64__
        unsigned int    _pad; /* pad to natural boundary */
#endif
        struct vm_object *moc_object;
} *memory_object_control_t;