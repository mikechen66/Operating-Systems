// Listing 13-15: catch_mach_exception_raise, in bsd/uxkern/ux_exception.c

kern_return_t catch_mach_exception_raise(__unused mach_port_t exception_port,
                                         mach_port_t thread, mach_port_t task,
                                         exception_type_t exception,
                                         mach_exception_data_t code,
                                        __unused mach_msg_type_number_t codeCnt) {
    mach_port_name_t thread_name = CAST_MACH_PORT_TO_NAME(thread);
    mach_port_name_t task_name = CAST_MACH_PORT_TO_NAME(task);
    if (th_act != THREAD_NULL) {
        /*
         *  Convert exception to unix signal and code.
         */
        ux_exception(exception, code[0], code[1], &ux_signal, &ucode);
        ut = get_bsdthread_info(th_act);
        sig_task = get_threadtask(th_act);
        p = (struct proc *) get_bsdtask_info(sig_task);
        /* Can't deliver a signal without a bsd process */
        if (p == NULL) {
            ux_signal = 0;
            result = KERN_FAILURE;
    }
    if (code[0] == KERN_PROTECTION_FAILURE && ux_signal == SIGBUS) {
        // handle specifically stack overflow
        // …
    }
        /*
         *  Send signal.
         */
    if (ux_signal != 0) {
        ut->uu_exception = exception;
        //ut->uu_code = code[0]; // filled in by threadsignal
        ut->uu_subcode = code[1];                       
        threadsignal(th_act, ux_signal, code[0]);
    }
    thread_deallocate(th_act);
    /*
     *  Delete our send rights to the task port.
     */
    (void)mach_port_deallocate(get_task_ipcspace(ux_handler_self), task_name);
}