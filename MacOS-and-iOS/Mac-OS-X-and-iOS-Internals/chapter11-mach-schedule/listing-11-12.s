// Listing 11-12: AST checks on return from trap in osfmk/s86_64/idt64.s

Entry(return_from_trap)
    movq    %gs:CPU_ACTIVE_THREAD,%rsp
    movq    TH_PCB_ISS(%rsp), %rsp  /* switch back to PCB stack */
    movl    %gs:CPU_PENDING_AST,%eax
    testl   %eax,%eax
    je      EXT(return_to_user)     /* branch if no AST */

// otherwise we fall through to here:
L_return_from_trap_with_ast:
               …
               …
2:      
    STI                      /* interrupts always enabled on return to user mode */
    xor     %edi, %edi              /* zero %rdi */
    xorq    %rbp, %rbp              /* clear framepointer */
    CCALL(i386_astintr)             /* take the AST */
    CLI
    xorl    %ecx, %ecx              /* don't check if we're in the PFZ */
    jmp     EXT(return_from_trap)   /* and check again (rare) */