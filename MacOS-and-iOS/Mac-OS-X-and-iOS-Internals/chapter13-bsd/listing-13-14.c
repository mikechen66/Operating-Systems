// Listing 13-14: ux_handler(), in bsd/uxkern/ux_exception.c

void ux_handler(void) {
    task_t              self = current_task();
    mach_port_name_t    exc_port_name;
    mach_port_name_t    exc_set_name;
    /* self->kernel_vm_space = TRUE; */
    ux_handler_self = self;
    /*
     *  Allocate a port set that we will receive on.
     */
    if (mach_port_allocate(get_task_ipcspace(ux_handler_self), 
            MACH_PORT_RIGHT_PORT_SET, 
            &exc_set_name) != MACH_MSG_SUCCESS)
        panic(”ux_handler: port_set_allocate failed”);
    /*
     *  Allocate an exception port and use object_copyin to
     *  translate it to the global name.  Put it into the set.
     */
    if (mach_port_allocate(get_task_ipcspace(ux_handler_self),
            MACH_PORT_RIGHT_RECEIVE, 
            &exc_port_name) != MACH_MSG_SUCCESS)
        panic(”ux_handler: port_allocate failed”);
    if (mach_port_move_member(get_task_ipcspace(ux_handler_self),
            exc_port_name,  exc_set_name) != MACH_MSG_SUCCESS)
        panic(”ux_handler: port_set_add failed”);
    if (ipc_object_copyin(get_task_ipcspace(self), exc_port_name,
            MACH_MSG_TYPE_MAKE_SEND,
            (void *) &ux_exception_port) != MACH_MSG_SUCCESS)
        panic(”ux_handler: object_copyin(ux_exception_port) failed”);
    proc_list_lock();
    thread_wakeup(&ux_exception_port);
    proc_list_unlock();
    /* Message handling loop. */
    // No problem with getting into an endless loop here, since ux_handler() runs in its
    // own thread, and the mach_msg_receive() function blocks anyway.
    for (;;) {
        // inline structure definitions make for great readability.. This
        // is likely a vestige of MIG's automatic code generation
        struct rep_msg {
            mach_msg_header_t Head;
            NDR_record_t NDR;
            kern_return_t RetCode;
        } rep_msg;
        struct exc_msg {
            mach_msg_header_t Head;
            /* start of the kernel processed data */
            mach_msg_body_t msgh_body;
            mach_msg_port_descriptor_t thread;
            mach_msg_port_descriptor_t task;
            /* end of the kernel processed data */
            NDR_record_t NDR;
            exception_type_t exception;
            mach_msg_type_number_t codeCnt;
            mach_exception_data_t code;
            /* some times RCV_TO_LARGE probs */
            char pad[512];
        } exc_msg;
        mach_port_name_t        reply_port;
        kern_return_t    result;
        exc_msg.Head.msgh_local_port = CAST_MACH_NAME_TO_PORT(exc_set_name);
        exc_msg.Head.msgh_size = sizeof (exc_msg);
        result = mach_msg_receive(&exc_msg.Head, MACH_RCV_MSG,
                                  sizeof (exc_msg), exc_set_name,
                                  MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL,
                                  0);
        if (result == MACH_MSG_SUCCESS) {
            reply_port = CAST_MACH_PORT_TO_NAME(exc_msg.Head.msgh_remote_port);
            // mach_exc_server will call mach_exception_raise(), which will be caught
            // by mach_catch_exception_raise() – where the signal handling logic is.
            if (mach_exc_server(&exc_msg.Head, &rep_msg.Head)) {
                result = mach_msg_send(&rep_msg.Head, MACH_SEND_MSG,
                   sizeof (rep_msg),MACH_MSG_TIMEOUT_NONE,MACH_PORT_NULL);
                if (reply_port != 0 && result != MACH_MSG_SUCCESS)
                    mach_port_deallocate(get_task_ipcspace(ux_handler_self), reply_port);
            }
        }
        else if (result == MACH_RCV_TOO_LARGE)
            /* ignore oversized messages */;
        else // any other result is unexpected, and thereby constitutes a panic 
            panic(”exception_handler”);
    } // end message loop
} // end ux_handler()