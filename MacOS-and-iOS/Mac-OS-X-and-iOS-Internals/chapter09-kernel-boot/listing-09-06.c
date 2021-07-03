// Listing 9-6: load_init_program (from bsd/kern/kern_exec.c)

// Note that launchd's path is hard-coded right into the kernel.
// This was "/mach_init" up to OS X 10.3
static char             init_program_name[128] = "/sbin/launchd";
struct execve_args      init_exec_args;
/*
 * load_init_program
 *
 * Description: Load the "init" program; in most cases, this will be "launchd"
 *
 * Parameters:  p                  Process to call execve() to create
 *                                 the "init" program
 *
 * Returns:     (void)
 *
 * Notes: The process that is passed in is the first manufactured
 * process on the system, and gets here via bsd_ast() firing
 * for the first time.  This is done to ensure that bsd_init()
 * has run to completion.
 */
void load_init_program(proc_t p) {
    vm_offset_t     init_addr;
    int             argc = 0;
    uint32_t argv[3];
    int                     error;
    int             retval[2];
    /*
     * Copy out program name.
     */
    init_addr = VM_MIN_ADDRESS;
    (void)vm_allocate(current_map(),&init_addr,PAGE_SIZE,VM_FLAGS_ANYWHERE);
    if (init_addr == 0)
        init_addr++;
    (void) copyout((caddr_t) init_program_name, CAST_USER_ADDR_T(init_addr),
                   (unsigned) sizeof(init_program_name)+1);
    argv[argc++] = (uint32_t)init_addr;
    init_addr += sizeof(init_program_name);
    init_addr = (vm_offset_t)ROUND_PTR(char, init_addr);
    /*
     * Put out first (and only) argument, similarly.
     * Assumes everything fits in a page as allocated
     * above.
     */
    if (boothowto & RB_SINGLE) {
        const char *init_args = "-s";
        copyout(init_args, CAST_USER_ADDR_T(init_addr),
                strlen(init_args));
        argv[argc++] = (uint32_t)init_addr;
        init_addr += strlen(init_args);
        init_addr = (vm_offset_t)ROUND_PTR(char, init_addr);
    }
    /*
     * Null-end the argument list
     */
    argv[argc] = 0;
    /*
     * Copy out the argument list.
     */
    (void) copyout((caddr_t) argv, CAST_USER_ADDR_T(init_addr),
                  (unsigned) sizeof(argv));
    /*
     * Set up argument block for fake call to execve.
     */
    init_exec_args.fname = CAST_USER_ADDR_T(argv[0]);
    init_exec_args.argp = CAST_USER_ADDR_T((char **)init_addr);
    init_exec_args.envp = CAST_USER_ADDR_T(0);

    /*
     * So that mach_init task is set with uid,gid 0 token
     */
    set_security_token(p);
    error = execve(p,&init_exec_args,retval);
    if (error)
        panic("Process 1 exec of %s failed, errno %d",
              init_program_name, error);
}