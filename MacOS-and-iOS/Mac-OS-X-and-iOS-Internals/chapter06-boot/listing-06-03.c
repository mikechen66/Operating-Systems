// Listing 6-3: Boot_args (version 2.0) structure from Lion

typedef struct boot_args {
    uint16_t Revision;/* Revision of boot_args structure (Lion: 2, SL: 1) */
    uint16_t Version; /* Version of boot_args structure  (Lion: 0, SL: 6) */
    uint8_t  efiMode;    /* 32 = 32-bit, 64 = 64-bit */
    uint8_t  debugMode;  /* Bit field with behavior changes */
    uint8_t  __reserved1[2];
    char     CommandLine[BOOT_LINE_LENGTH];  /* Passed in command line */
    uint32_t MemoryMap;  /* Physical address of memory map */
    uint32_t MemoryMapSize;
    uint32_t MemoryMapDescriptorSize;
    uint32_t MemoryMapDescriptorVersion;
    Boot_Video  Video;          /* Video Information */
    uint32_t deviceTreeP; /* Physical address of flattened device tree */
    uint32_t deviceTreeLength; /* Length of flattened tree */
    uint32_t kaddr;       /* Physical address of beginning of kernel text */
    uint32_t ksize;       /* Size of combined kernel text+data+efi */
    uint32_t efiRuntimeServicesPageStart;
                           /* physical address of defragmented runtime pages */
    uint32_t efiRuntimeServicesPageCount;
    uint64_t efiRuntimeServicesVirtualPageStart; 
                          /* virtual address of defragmented runtime pages */
    uint32_t efiSystemTable; /* phys. Addr. of system table in runtime area */
    uint32_t __reserved2;      // defined in the user-mode header as efimode (32,64)
    uint32_t performanceDataStart; /* physical address of log */
    uint32_t performanceDataSize;
    uint32_t keyStoreDataStart; /* physical address of key store data */
    uint32_t keyStoreDataSize;
    uint64_t bootMemStart;
    uint64_t bootMemSize;
    uint64_t PhysicalMemorySize;
    uint64_t FSBFrequency;
    uint32_t __reserved4[734]; // padding to a page (2,936 bytes)
} boot_args;