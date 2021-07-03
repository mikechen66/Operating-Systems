// Listing 12-19: unprotect_segment() from bsd/kern/mach_loader.c

#if CONFIG_CODE_DECRYPTION
#define APPLE_UNPROTECTED_HEADER_SIZE (3 * PAGE_SIZE_64)
static load_return_t 
unprotect_segment(
    uint64_t        file_off,
    uint64_t        file_size,
    struct vnode    *vp,
    off_t           macho_offset,
    vm_map_t        map,
    vm_map_offset_t map_addr,
    vm_map_size_t   map_size)
     
    struct pager_crypt_info crypt_info;
     
    crypt_info.page_decrypt = dsmos_page_transform;
    crypt_info.crypt_ops = NULL;
    crypt_info.crypt_end = NULL;
#pragma unused(vp, macho_offset) 
    crypt_info.crypt_ops = (void *)0x2e69cf40;
    kr = vm_map_apple_protected(map,
                                map_addr,
                                map_addr + map_size,
                                &crypt_info);
    if (kr != KERN_SUCCESS) {
            return LOAD_FAILURE;
    }
    return LOAD_SUCCESS;