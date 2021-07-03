// Listing 12-18: Apple Protect data request

kern_return_t apple_protect_pager_data_request(
        memory_object_t         mem_obj,
        memory_object_offset_t  offset,
        memory_object_cluster_size_t            length,
#if !DEBUG
    __unused
#endif
    vm_prot_t               protection_required,      
    memory_object_fault_info_t mo_fault_info) {
        ...
        /*
         * Decrypt the encrypted contents of the source page
         * into the destination page.
         */
        ret = pager->crypt.page_decrypt((const void *) src_vaddr,
                                        (void *) dst_vaddr,
                                        offset+cur_offset,
                                        pager->crypt.crypt_ops);
    if (ret) {
        /*
         * Decryption failed.  Abort the fault.
         */
        retval = KERN_ABORTED;
    } 
    else {
        /*
         * Validate the original page...
         */
        if (src_page->object->code_signed) {
            vm_page_validate_cs_mapped(src_page, 
                (const void *) src_vaddr);
        }
        /*
         * ... and transfer the results to the destination page.
         */
        UPL_SET_CS_VALIDATED(upl_pl, cur_offset / PAGE_SIZE,
                             src_page->cs_validated);
        UPL_SET_CS_TAINTED(upl_pl, cur_offset / PAGE_SIZE,
                           src_page->cs_tainted);
    }
}