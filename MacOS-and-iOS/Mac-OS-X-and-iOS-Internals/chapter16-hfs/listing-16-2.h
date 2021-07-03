// Listing 16-2: Decompression logic exported in bsd/sys/decmpfs.h

#define DECMPFS_REGISTRATION_VERSION 1
typedef struct {
    int  decmpfs_registration; // "1"
    decmpfs_validate_compressed_file_func validate;
    decmpfs_adjust_fetch_region_func      adjust_fetch;
    decmpfs_fetch_uncompressed_data_func  fetch;
    decmpfs_free_compressed_data_func     free_data;
} decmpfs_registration;

/* hooks for kexts to call */
errno_t register_decmpfs_decompressor
    (uint32_t compression_type, decmpfs_registration *registration);
errno_t unregister_decmpfs_decompressor
    (uint32_t compression_type, decmpfs_registration *registration);