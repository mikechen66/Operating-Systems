// Listing 17-6: The implementation of socket(2)

int socket(struct proc *p, struct socket_args *uap, int32_t *retval) {
    struct socket *so;
    struct fileproc *fp;
    int fd, error;
    // call AUDIT_ARG to record call in audit subsytem
    AUDIT_ARG(socket, uap->domain, uap->type, uap->protocol);
#if CONFIG_MACF_SOCKET_SUBSET
    // call on MAC subsystem to check if sockets are allowed (q.v. Chapter 13)
    if ((error = mac_socket_check_create(kauth_cred_get(), uap->domain,
            ap->type, uap->protocol)) != 0)
        return (error);
#endif /* MAC_SOCKET_SUBSET */
    // allocate file descriptor
    error = falloc(p, &fp, &fd, vfs_context_current());
    // Mark as a socket, read writable, with standard socket operations
    fp->f_flag = FREAD|FWRITE;
    fp->f_type = DTYPE_SOCKET;
    fp->f_ops = &socketops;
    // Create domain (family) and type/protocol specific socket
    error = socreate(uap->domain, &so, uap->type, uap->protocol);
    if (error) {
        fp_free(p, fd, fp);
    } 
    else {   
        /* if this is a backgrounded thread then throttle all new sockets */
        // connect socket data
        fp->f_data = (caddr_t)so;
        proc_fdlock(p);
        procfdtbl_releasefd(p, fd, NULL);
        fp_drop(p, fd, fp, 1);
        proc_fdunlock(p);
        *retval = fd;
    }
    return (error);
}