// Listing 8-7: Setting MSRs for SYSENTER and SYSCALL (osfmk/i386/mp_desc.c)

/*
 * Set MSRs for sysenter/sysexit and syscall/sysret for 64-bit.
 */
static void
fast_syscall_init64(__unused cpu_data_t *cdp)
{
    // Registers used for SYSENTER (32-bit mode on 64-bit architecture)
    wrmsr64(MSR_IA32_SYSENTER_CS, SYSENTER_CS);
    wrmsr64(MSR_IA32_SYSENTER_EIP, UBER64((uintptr_t) hi64_sysenter));
    wrmsr64(MSR_IA32_SYSENTER_ESP, UBER64(current_sstk()));
    /* Enable syscall/sysret */
    wrmsr64(MSR_IA32_EFER, rdmsr64(MSR_IA32_EFER) | MSR_IA32_EFER_SCE);
    /*
     * MSRs for 64-bit syscall/sysret
     * Note USER_CS because sysret uses this + 16 when returning to
     * 64-bit code.
     */
    wrmsr64(MSR_IA32_LSTAR, UBER64((uintptr_t) hi64_syscall));
    wrmsr64(MSR_IA32_STAR, (((uint64_t)USER_CS) << 48) |
                            (((uint64_t)KERNEL64_CS) << 32));
   ...
}