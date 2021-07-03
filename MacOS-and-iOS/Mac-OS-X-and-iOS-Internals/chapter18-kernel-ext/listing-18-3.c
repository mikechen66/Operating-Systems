// Listing 18-3: The definition of the kmod_info_t , which abstracts kexts

#define KMOD_MAX_NAME    64

typedef struct kmod_info {
    struct kmod_info  * next;
    int32_t             info_version;           // version of this structure
    uint32_t            id;
    char                name[KMOD_MAX_NAME];
    char                version[KMOD_MAX_NAME];
    int32_t             reference_count;        // # linkage refs to this 
    kmod_reference_t  * reference_list;         // who this refs (links on)
    vm_address_t        address;                // starting address
    vm_size_t           size;                   // total size
    vm_size_t           hdr_size;               // unwired hdr size
    kmod_start_func_t * start;
    kmod_stop_func_t  * stop;
} kmod_info_t;