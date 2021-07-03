// Listing 13-12: ux_handler_init in bsd/uxkern/ux_exception.c

void ux_handler_init(void) {
    thread_t        thread = THREAD_NULL;
    ux_exception_port = MACH_PORT_NULL;  // global, defined ibid.
    // spin off ux_handler in a new Mach thread
    (void) kernel_thread_start((thread_continue_t)ux_handler, NULL, &thread);
    thread_deallocate(thread);
    // Lock the process list (not allowing any processes to be created,
    // including bsdinit_task(), which called us) until ux_exception_port
    //is registered by ux_handler
    proc_list_lock();
    if (ux_exception_port == MACH_PORT_NULL)  {
        (void)msleep(&ux_exception_port, proc_list_mlock, 0, “ux_handler_wait”, 0);
    }
    proc_list_unlock();
}