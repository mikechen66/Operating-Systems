// Listing 9-5: bsdinit_task() (from bsd/kern/bsd_init.c)

bsdinit_task(void) {
    proc_t p = current_proc();
    struct uthread *ut;
    thread_t thread;
    process_name("init", p);  
    ux_handler_init();
    thread = current_thread();
    (void) host_set_exception_ports(host_priv_self(),
            EXC_MASK_ALL & ∼(EXC_MASK_RPC_ALERT),//pilotfish (shark) ..
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
    load_init_program(p);
    lock_trace = 1;
}