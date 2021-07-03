// Listing 8-3: hndl_alltraps, the common trap handler

Entry(hndl_alltraps)
    mov     %esi, %eax
    testb   $3, %al
    jz      trap_from_kernel
    TIME_TRAP_UENTRY
    movq    %gs:CPU_ACTIVE_THREAD,%rdi
    movq    %rsp, ACT_PCB_ISS(%rdi)         /* stash the PCB stack */
    movq    %rsp, %rdi                      /* also pass it as arg0 */
    movq    %gs:CPU_KERNEL_STACK,%rsp       /* switch to kernel stack */
    sti
    CCALL(user_trap)                        /* call user trap routine */
    // user_trap is very likely to generate a Mach exception, and NOT return
    // (it suspends the currently active thread). In some cases, however, it
    // does return, and execution falls through
    /* user_trap() unmasks interrupts */
    cli                                     /* hold off intrs - critical section */
    xorl    %ecx, %ecx                      /* don't check if we're in the PFZ */
    // Fall through to return_from_trap.