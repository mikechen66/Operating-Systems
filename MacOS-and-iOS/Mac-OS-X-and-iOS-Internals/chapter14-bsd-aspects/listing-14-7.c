// Listing 14-7: Auditing support in unix_syscall (bsd/dev/i386/systemcalls.c)
void unix_syscall(x86_saved_state_t *state) {
    // ... 
    AUDIT_SYSCALL_ENTER(code, p, uthread);
    error = (*(callp->sy_call))((void *) p, (void *) vt, &(uthread->uu_rval[0]));
    AUDIT_SYSCALL_EXIT(code, p, uthread, error);
    // ...
    }