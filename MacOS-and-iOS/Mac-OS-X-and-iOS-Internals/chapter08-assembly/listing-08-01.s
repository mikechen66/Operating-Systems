// Listing 8-1: osfmk/x86_64/start.s 

Entry(real_mode_bootstrap_base)
    cli
    LGDT(EXT(protected_mode_gdtr))
    /* set the PE bit of CR0 */
    mov     %cr0, %eax      ; can't operate on CRs directly
    inc %eax                ; add 1 toggles on the least significant bit
    mov     %eax, %cr0      ; update CR0