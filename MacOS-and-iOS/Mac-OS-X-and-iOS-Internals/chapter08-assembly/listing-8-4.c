// Listing 8-4: hndl_allintrs, the common interrupt handler

#define HNDL_ALLINTRS           EXT(hndl_allintrs)
Entry(hndl_allintrs)
       /*
        * test whether already on interrupt stack
        */
       movq    %gs:CPU_INT_STACK_TOP,%rcx
       cmpq    %rsp,%rcx
       jb      1f
       leaq    -INTSTACK_SIZE(%rcx),%rdx
       cmpq    %rsp,%rdx
       jb      int_from_intstack
1:     
       xchgq   %rcx,%rsp               /* switch to interrupt stack */
       mov     %cr0,%rax               /* get cr0 */
       orl     $(CR0_TS),%eax          /* or in TS bit */
       mov     %rax,%cr0               /* set cr0 */
       subq    $8, %rsp                /* for 16-byte stack alignment */
       pushq   %rcx                    /* save pointer to old stack */
       movq    %rcx,%gs:CPU_INT_STATE  /* save intr state */
       
       TIME_INT_ENTRY                  /* do timing */
incl   %gs:CPU_PREEMPTION_LEVEL
       incl    %gs:CPU_INTERRUPT_LEVEL
       movq    %gs:CPU_INT_STATE, %rdi
       
       CCALL(interrupt)                /* call generic interrupt routine */
       cli                             /* just in case we returned with intrs enabled */
       xor     %rax,%rax
       movq    %rax,%gs:CPU_INT_STATE  /* clear intr state pointer */
// Falls through to return_to_iret, which returns to user mode via an iret instruction