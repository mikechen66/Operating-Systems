// Listing 8-14: mach_call_munger64, from osfmk/i386/bsd_i386.c

void mach_call_munger64(x86_saved_state_t *state) {
    int call_number;
    int argc;
    mach_call_t mach_call;
    x86_saved_state64_t     *regs;
    assert(is_saved_state64(state));
    regs = saved_state64(state);
    // In mach_call_munger (the 32-bit version), the call_number is obtained
    // by: call_number = -(regs->eax);
    call_number = (int)(regs->rax & SYSCALL_NUMBER_MASK);
       
DEBUG_KPRINT_SYSCALL_MACH(
    "mach_call_munger64: code=%d(%s)\n",
    call_number, mach_syscall_name_table[call_number]);
    // Kdebug trace of function entry (see chapter 5)
    KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_EXCP_SC,
                                       (call_number)) | DBG_FUNC_START,
                                       regs->rdi, regs->rsi,
                                       regs->rdx, regs->r10, 0);
    // if this is an obviously invalid call, raise syscall exception
    if (call_number < 0 || call_number >= mach_trap_count) {
        i386_exception(EXC_SYSCALL, regs->rax, 1);
        /* NOTREACHED */
    }
    // Get entry from mach_trap_table. We need the entry to validate the call
    // is a valid one, as well as get the number of arguments
    mach_call = (mach_call_t)mach_trap_table[call_number].mach_trap_function;
    // Quite a few entries in the table are marked as invalid, for deprecated calls.
    // If we stumbled upon one of those, generate an exception
    if (mach_call == (mach_call_t)kern_invalid) {
        i386_exception(EXC_SYSCALL, regs->rax, 1);
        /* NOTREACHED */
    }
    argc = mach_trap_table[call_number].mach_trap_arg_count;
    // In 32-bit, we would need to prepare the arguments, copying them from
    // the stack to a mach_call_args struct. This is where we would need to
    // call a helper, mach_call_arg_munger32:
    //  if (argc)
    //   retval = mach_call_arg_munger32(regs->uesp, argc, call_number, &args);
    //
    //  In 64-bit, up to six arguments may be directly passed in registers,
    //  so the following code is only necessary for cases of more than 6
    if (argc > 6) {
        int copyin_count;
        copyin_count = (argc - 6) * (int)sizeof(uint64_t);
        if (copyin((user_addr_t)(regs->isf.rsp + sizeof(user_addr_t)), (char *)&regs->v_arg6, copyin_count)) {
            regs->rax = KERN_INVALID_ARGUMENT;
            thread_exception_return();
            /* NOTREACHED */
        }
    }
        if (retval != KERN_SUCCESS) {
            regs->eax = retval;
            DEBUG_KPRINT_SYSCALL_MACH("mach_call_munger: retval=0x%x\n", retval);
            thread_exception_return();
            /* NOTREACHED */
        }
// Execute the call, collect return value straight into RAX
regs->rax = (uint64_t)mach_call((void *)(&regs->rdi));
DEBUG_KPRINT_SYSCALL_MACH("mach_call_munger64: retval=0x%llx\n", regs->rax);
// Kdebug trace of function exit (see chapter 5)
KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_EXCP_SC,
                                   (call_number)) | DBG_FUNC_END,
                      regs->rax, 0, 0, 0, 0);
throttle_lowpri_io(TRUE);
// return to user mode
thread_exception_return();
/* NOTREACHED */
}