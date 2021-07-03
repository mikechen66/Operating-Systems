// Listing 13-8: execve

int execve(proc_t p, struct execve_args *uap, int32_t *retval) {
    struct __mac_execve_args muap;
    int err;
    muap.fname = uap->fname;
    muap.argp = uap->argp;
    muap.envp = uap->envp;
    muap.mac_p = USER_ADDR_NULL;
    err = __mac_execve(p, &muap, retval);
    return(err);
}