// Listing 12-16: The implementation of the swapfile pager's data request (osfmk/vm/vm_swapfile_pager.c)

kern_return_t swapfile_pager_data_request(
    memory_object_t mem_obj,
    memory_object_offset_t offset,
    memory_object_cluster_size_t length,
#if !DEBUG
    __unused
#endif
    vm_prot_t               protection_required,
    __unused memory_object_fault_info_t mo_fault_info) {
        //...
        /*
        * Reserve a virtual page in the kernel address space to map each
        * destination physical page when it's its turn to be processed.
        */
        vm_object_reference(kernel_object);     /* ref. for mapping */
        kr = vm_map_find_space(kernel_map,
                               &kernel_mapping,
                               PAGE_SIZE_64,
                               0,
                               0,
                               &map_entry);
        // ...
        dst_vaddr = CAST_DOWN(vm_offset_t, kernel_mapping);
        dst_ptr = (char *) dst_vaddr;
        /*
        * Gather in a UPL all the VM pages requested by VM.
        */
        mo_control = pager->pager_control;
        upl_size = length;
        upl_flags =
            UPL_RET_ONLY_ABSENT |
            UPL_SET_LITE |
            UPL_NO_SYNC |
            UPL_CLEAN_IN_PLACE |    /* triggers UPL_CLEAR_DIRTY */
            UPL_SET_INTERNAL;
        pl_count = 0;
        kr = memory_object_upl_request(mo_control,
                                       offset, upl_size,
                                       &upl, NULL, NULL, upl_flags);
        // ...
        /*
         * Fill in the contents of the pages requested by VM.
         */
        upl_pl = UPL_GET_INTERNAL_PAGE_LIST(upl);
        pl_count = length / PAGE_SIZE;
        for (cur_offset = 0; cur_offset < length; cur_offset += PAGE_SIZE) {
            ppnum_t dst_pnum;
            if (!upl_page_present(upl_pl, (int)(cur_offset / PAGE_SIZE))) {
            /* this page is not in the UPL: skip it */
                continue;
            }    
            /*
             * Establish an explicit pmap mapping of the destination
             * physical page.
             * We can't do a regular VM mapping because the VM page
             * is “busy”.
             */
            dst_pnum = (ppnum_t)
                upl_phys_page(upl_pl, (int)(cur_offset / PAGE_SIZE));
            assert(dst_pnum != 0);
            pmap_enter(kernel_pmap,
                       kernel_mapping,
                       dst_pnum,
                       VM_PROT_READ | VM_PROT_WRITE,
                       0,
                       TRUE);
            memset(dst_ptr, '\0', PAGE_SIZE);  // explicit zeroing of pages
            /* add an end-of-line to keep line counters happy */
            dst_ptr[PAGE_SIZE-1] = ‘\n';
    }
}