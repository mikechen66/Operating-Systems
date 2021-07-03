// Listing 13-9: load_machfile() , from bsd/kern/mach_loader.c

load_return_t load_machfile(
    struct image_params     *imgp,    // Image parameters as set by exec_mach_imgact
    struct mach_header      *header,  // Mach-O header (overlaid on imgp->ip_vdata)
    thread_t                thread,   // current_thread();
    vm_map_t                new_map,  // get_task_map() for vfexec or spawn, else NULL
    load_result_t           *result); // out parameter, returning load operation data