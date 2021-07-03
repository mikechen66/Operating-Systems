// Listing 11-4: Using task_info with various flavors from Lion and iOS

doTaskInfo(task_t Task) {
    // proper code does validation checking on calls. 
    // Omitted here for brevity
    mach_msg_type_number_t infoSize;
    char infoBuf[TASK_INFO_MAX];
    struct task_basic_info_64     *tbi;
    struct task_events_info       *tei;
#if LION  // Will also work on iOS 5.x or later
    struct task_kernelmemory_info *tkmi;
    struct task_extmod_info       *texi;
    struct vm_extmod_statistics *ves;
#endif
    kern_return_t kr;
    infoSize = TASK_INFO_MAX;
    kr = task_info(Task,
                   TASK_BASIC_INFO_64,
                   (task_info_t)infoBuf,
                   &infoSize);
    tbi = (struct task_basic_info_64 *) infoBuf;
    printf ("\tSuspend Count: %d\n", tbi->suspend_count);
    printf ("\tMemory:  %dM virtual, %dK resident\n",
            tbi->virtual_size / (1024 * 1024), tbi->resident_size / 1024);
    printf ("\tSystem/User Time: %ld/%ld\n", tbi->system_time, tbi->user_time);
    infoSize = TASK_INFO_MAX; // need to reset (this is an in/out parameter)
    kr = task_info(Task,
                   TASK_EVENTS_INFO,
                   (task_info_t)infoBuf,
                   &infoSize);
    tei = (struct task_events_info *) infoBuf;
    printf("Faults: %d, Page-Ins: %d, COW: %d\n", tei->faults, tei->pageins,            
         tei->cow_faults);
    printf ("Messages: %d sent, %d received\n", tei->messages_sent, tei->messages_received);
    printf ("Syscalls: %d Mach, %d UNIX\n", tei->syscalls_mach, tei->syscalls_unix);
#if LION
    infoSize = TASK_INFO_MAX; // need to reset (this is an in/out parameter)
    kr = task_info(Task,
                   TASK_KERNELMEMORY_INFO, // defined as of Lion
                   (task_info_t)infoBuf,
                   &infoSize);
    tkmi = (struct task_kernelmemory_info *) infoBuf;
    printf("Kernel memory: Private: %dK allocated %dK freed,  Shared: %dK allocated, %dK freed\n",
           tkmi->total_palloc/ 1024, tkmi->total_pfree  /1024,
           tkmi->total_salloc/ 1024, tkmi->total_sfree  /1024);
// Lion and later offer the VM external modification information – really
// useful to detect all sorts of attacks certain tools (like gdb and corerupt, presented
// in the next chapter) utlize to debug/trace processes
    infoSize = TASK_INFO_MAX; // need to reset (this is an in/out parameter)
    kr = task_info(Task,
                   TASK_EXTMOD_INFO, // defined as of Lion
                   (task_info_t)infoBuf,
                   &infoSize);
if (kr == KERN_SUCCESS) {
    printf("--OK\n");
}
    texi = (struct vm_extmod_statistics *) infoBuf;
    ves = &(texi->extmod_statistics);
    if (ves->task_for_pid_count){ 
        printf ("Task has been looked up %ld times\n", ves->task_for_pid_count); 
    }
    if (ves->task_for_pid_caller_count){ 
        printf ("Task has looked up others %ld times\n", ves->task_for_pid_caller_count); 
    }
    if (ves->thread_creation_count || ves->thread_set_state_count){  
        printf ("Task has been tampered with\n"); 
    }
    if (ves->thread_creation_caller_count || ves->thread_set_state_caller_count){  
        printf ("Task has tampered with others\n"); 
    }
#endif
}