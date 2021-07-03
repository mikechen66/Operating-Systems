// Listing 13-13: bsdinit_task() exception handling

void bsdinit_task(void) {
    proc_t p = current_proc();
    struct uthread *ut;
    thread_t thread;
    process_name(”init”, p); // set our process name to “init” (this gets changed later
                             // in load_init_program() to launchd)
    ux_handler_init();       // spin off Unix exception handler thread
    thread = current_thread();
    // when ux_handler_init() returns, ux_handler() is executing in a separate thread
    // and registers the ux_exception_port.
    (void) host_set_exception_ports(host_priv_self(),
                                    EXC_MASK_ALL & ∼(EXC_MASK_RPC_ALERT),
                                    (mach_port_t) ux_exception_port,
                                    EXCEPTION_DEFAULT| MACH_EXCEPTION_CODES,
                                    0);
    ut = (uthread_t)get_bsdthread_info(thread);
    bsd_init_task = get_threadtask(thread);
    init_task_failure_data[0] = 0;
#if CONFIG_MACF
    mac_cred_label_associate_user(p->p_ucred);
    mac_task_label_update_cred (p->p_ucred, (struct task *) p->task);
#endif
    // go on to load the init program, launchD.
    load_init_program(p);
}