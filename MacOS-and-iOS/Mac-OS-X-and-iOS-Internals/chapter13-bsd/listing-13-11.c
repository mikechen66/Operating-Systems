// Listing 13-11: load_result returned from load_machfile

typedef struct _load_result {
    user_addr_t             mach_header;
    user_addr_t             entry_point;          // set by load_unixthread()
    user_addr_t             user_stack;           // set by load_unixthread()
    mach_vm_address_t       all_image_info_addr;
    mach_vm_size_t          all_image_info_size;
    int                     thread_count;
    unsigned int
            /* boolean_t */ unixproc        :1, // by load_unixthread()
                            dynlinker       :1, // by load_dylinker()
                            customstack     :1, // by load_unixthread()
                            validentry      :1, // by load_segment()
                     /* unused */           :0;
    unsigned int          csflags;  // code-signing flags, by load_code_signature();
    unsigned char   uuid[16];       // parse_machfile, on LC_UUID
    mach_vm_address_t       min_vm_addr;
    mach_vm_address_t       max_vm_addr;
} load_result_t;