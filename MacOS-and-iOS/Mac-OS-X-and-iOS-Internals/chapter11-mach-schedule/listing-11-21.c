// Listing 11-21: Mach sample exception handling program, step 2

// Adding an exception message listener:
static void *exc_handler(void *ignored) {
    // Exception handler – runs a message loop. Refactored into a standalone function
    // so as to allow easy insertion into a thread (can be in same program or different)
    mach_msg_return_t rc;
    fprintf(stderr, "Exc handler listening\n");
    // The exception message, straight from mach/exc.defs (following MIG processing)
    // copied here for ease of reference.
    typedef struct {
        mach_msg_header_t Head;
        /* start of the kernel processed data */
        mach_msg_body_t msgh_body;
        mach_msg_port_descriptor_t thread;
        mach_msg_port_descriptor_t task;
        /* end of the kernel processed data */
        NDR_record_t NDR;
        exception_type_t exception;
        mach_msg_type_number_t codeCnt;
        integer_t code[2];
        int flavor;
        mach_msg_type_number_t old_stateCnt;
        natural_t old_state[144];
    } Request;
    Request exc;
    for(;;) {
        // Message Loop: Block indefinitely until we get a message, which has to be
        // an exception message (nothing else arrives on an exception port)
        rc = mach_msg(
            &exc.Head,
            MACH_RCV_MSG|MACH_RCV_LARGE,
            0,
            sizeof(Request),
            myExceptionPort,       // Remember this was global – that's why.
            MACH_MSG_TIMEOUT_NONE,
            MACH_PORT_NULL);
        if(rc != MACH_MSG_SUCCESS) {
            /*... */ 
            return; 
        };     
        // Normally we would call exc_server or other. In this example, however, we wish
        // to demonstrate the message contents:
        printf("Got message %hd. Exception : %d Flavor: %d. Code %d/%d. State count is %d\n" , 
               exc.Head.msgh_id, exc.exception, exc.flavor, 
               exc.code[0], exc.code[1], // can also print as 64-bit quantity 
               exc.old_stateCnt);
        #ifdef IOS
            // The exception flavor on iOS is 1
            // The arm_thread_state (defined in the SDK's <mach/arm/_structs.h>)
            // and contains r0-r12, sp, lr, pc and cpsr (total 17 registers). Its count is 17
            // In this example, we print out CPSR and PC.
            struct arm_thread_state *atsh   = &exc.old_state;
            printf ("CPSR is %p, PC is %p, etc.\n", atsh->cpsr, atsh->pc);
        #else // OS X
            struct x86_thread_state *x86ts = &exc.old_state;
            printf("State flavor: %d Count %d\n", x86ts->tsh.flavor, x86ts->tsh.count);
            // x86_THREAD_STATE64 
            if (x86ts->tsh.flavor == 4) {
               printf ("RIP: %p, RAX: %p, etc.\n", x86ts->uts.ts64.__rip, x86ts->uts.ts64.__rax);
            }
            else {
            // Could be x86_THEAD_STATE32 on older systems or 32-bit binaries
            ...
            }
        #endif
            // You are encouraged to extend this example further, to call on exc_server and
            // perform actual exception handling. But for our purposes, q.e.d.
            exit(1);
    }
} // end exc_handler
// …
// …
void catchMACHExceptions(mach_port_t  TargetTask) {
// …
    // at the end of catchMachExceptions, spawn the exception handling thread
    pthread_t     thread;
    pthread_create(&thread,NULL,exc_handler,NULL);
} // end catchMACHExceptions
// and simplify the main to be:
int main() { 
    int rc;
    mach_port_t  task;
    // Note: Requires entitlements on iOS, or root on OS X!
    rc = task_for_pid(mach_task_self(),atoi(argv[argc -1]), &task);
    catchMACHExceptions(task);
    sleep (1000);  // Can also loop endlessly. Processing will be in another thread
}