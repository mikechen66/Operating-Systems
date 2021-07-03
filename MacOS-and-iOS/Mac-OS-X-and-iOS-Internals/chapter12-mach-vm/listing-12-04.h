// Listing 12-4: The VM_REGION_BASIC_INFO_64 struct, from <mach/vm_region.h>

struct vm_region_basic_info_64 {
    vm_prot_t               protection;     // VM_PROT_* flags
    vm_prot_t               max_protection; // likewise, for max possible
    vm_inherit_t            inheritance;    // VM_INHERIT_[SHARE|COPY|NONE]
    boolean_t               shared;          
    boolean_t               reserved;
    memory_object_offset_t  offset;
    vm_behavior_t           behavior;       // VM_BEHAVIOR_*, like madvise(2)
    unsigned short          user_wired_count;
};