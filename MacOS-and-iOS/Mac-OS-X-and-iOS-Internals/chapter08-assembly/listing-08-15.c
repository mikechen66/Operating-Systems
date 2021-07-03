// Listing 8-15: The Mach trap table and syscall_name_table (osfmk/kern/syscall_sw.c)

mach_trap_t     mach_trap_table[MACH_TRAP_TABLE_COUNT] = {
/* 0 */         MACH_TRAP(kern_invalid, 0, NULL, NULL),
// many invalid traps…
/* 26 */        MACH_TRAP(mach_reply_port, 0, NULL, NULL),
/* 27 */        MACH_TRAP(thread_self_trap, 0, NULL, NULL),
/* 28 */        MACH_TRAP(task_self_trap, 0, NULL, NULL),
/* 29 */        MACH_TRAP(host_self_trap, 0, NULL, NULL),
// many more traps, most invalid..
/* 127 */       MACH_TRAP(kern_invalid, 0, NULL, NULL),                 
};
const char * mach_syscall_name_table[MACH_TRAP_TABLE_COUNT] = {
/* 0 */         "kern_invalid",
// ..
/* 26 */        "mach_reply_port",
/* 27 */        "thread_self_trap",
/* 28 */        "task_self_trap",
/* 29 */        "host_self_trap",
// ..
/* 127 */       "kern_invalid",
};
int mach_trap_count = (sizeof(mach_trap_table) / sizeof(mach_trap_table[0]));
kern_return_t kern_invalid(
    __unused struct kern_invalid_args *args)
{
    if (kern_invalid_debug) Debugger("kern_invalid mach trap");
    return(KERN_INVALID_ARGUMENT);
}



/*
Output 8-1: Mach traps (and their names) on iOS 5.1
 10 _kernelrpc_mach_vm_allocate_trap         800132ac 
 11 _kernelrpc_vm_allocate_trap              80013318 
 12 _kernelrpc_mach_vm_deallocate_trap       800133b4 
 13 _kernelrpc_vm_deallocate_trap            80013374 
 14 _kernelrpc_mach_vm_protect_trap          8001343c 
 15 _kernelrpc_vm_protect_trap               800133f8 
 16 _kernelrpc_mach_port_allocate_trap       80013494 
 17 _kernelrpc_mach_port_destroy_trap        800134e4 
 18 _kernelrpc_mach_port_deallocate_trap     80013520 
 19 _kernelrpc_mach_port_mod_refs_trap       8001355c 
 20 _kernelrpc_mach_port_move_member_trap    8001359c 
 21 _kernelrpc_mach_port_insert_right_trap   800135e0 
 22 _kernelrpc_mach_port_insert_member_trap  8001363c 
 23 _kernelrpc_mach_port_extract_member_trap 80013680 
 26 mach_reply_port                          800198ac 
 27 thread_self_trap                         80019890
 28 task_self_trap                           80019870 
 29 host_self_trap                           80017db8 
 31 mach_msg_trap                            80013c1c 
 32 mach_msg_overwrite_trap                  80013ae4 
 33 semaphore_signal_trap                    800252d4 
 34 semaphore_signal_all_trap                80025354 
 35 semaphore_signal_thread_trap             80025260 
 36 semaphore_wait_trap                      800255e8 
 37 semaphore_wait_signal_trap               8002578c 
 38 semaphore_timedwait_trap                 800256c8 
 39 semaphore_timedwait_signal_trap          8002586c 
 43 map_fd                                   80025f50 
 44 task_name_for_pid                        801e0734 
 45 task_for_pid                             801e0598 
 46 pid_for_task                             801e054c 
 48 macx_swapon                              801e127c 
 49 macx_swapoff                             801e14cc 
 50 kern_invalid                             80025f50 
 51 macx_triggers                            801e1260 
 52 macx_backing_store_suspend               801e11f0 
 53 macx_backing_store_recovery              801e1198 
 58 pfz_exit                                 80025944 
 59 swtch_pri                                800259f4 
 60 swtch                                    80025948  
 61 thread_switch                            80025bb8 
 62 clock_sleep_trap                         800160f0 
 89 mach_timebase_info_trap                  80015318 
 90 mach_wait_until_trap                     80015934 
 91 mk_timer_create_trap                     8001d238 
 92 mk_timer_destroy_trap                    8001d428 
 93 mk_timer_arm_trap                        8001d46c
 94 mk_timer_cancel_trap                     8001d4f0 
100 iokit_user_client_trap (probably)        80234aa0
 */