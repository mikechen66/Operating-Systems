// Listing 14-4: Setting a work queue thread's state

int setup_wqthread(proc_t p, thread_t th, user_addr_t item, int reuse_thread, 
                   struct threadlist *tl)
{
#if defined(__i386__) || defined(__x86_64__) {
    int isLP64 = 0;
    isLP64 = IS_64BIT_PROCESS(p);
    /*
     * Set up i386 registers & function call.
     */
          // very similar to x86_64 case, so omitted
    } else {  
        x86_thread_state64_t state64;
        x86_thread_state64_t *ts64 = &state64;
        ts64->rip = (uint64_t)p->p_wqthread; // Thread will resume from this point
        ts64->rdi = (uint64_t)(tl->th_stackaddr + PTH_DEFAULT_STACKSIZE + 
                                                  PTH_DEFAULT_GUARDSIZE);
        ts64->rsi = (uint64_t)(tl->th_thport);
        ts64->rdx = (uint64_t)(tl->th_stackaddr + PTH_DEFAULT_GUARDSIZE);
        ts64->rcx = (uint64_t)item;
        ts64->r8 = (uint64_t)reuse_thread;
        ts64->r9 = (uint64_t)0;
        /*
         * set stack pointer aligned to 16 byte boundary
         */
        ts64->rsp = (uint64_t)((tl->th_stackaddr + PTH_DEFAULT_STACKSIZE + 
                                 PTH_DEFAULT_GUARDSIZE) - C_64_REDZONE_LEN);
        // This had better work, or else..
        if ((reuse_thread != 0) && (ts64->rdi == (uint64_t)0))
            panic("setup_wqthread: setting reuse thread with null pthread\n");
        // Call architecture specific thread state setting (osfmk/i386/pcb_native.c)
        thread_set_wq_state64(th, (thread_state_t)ts64);
    }
#else
#error setup_wqthread not defined for this architecture //unless you have iOS sources.
#endif
    return(0);
}