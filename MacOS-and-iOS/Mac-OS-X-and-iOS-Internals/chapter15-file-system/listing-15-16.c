// Listing 15-16: fstat1(), the implementation of fstat, from bsd/kern/kern_descrip.c

#define f_type f_fglob->fg_type 
#define f_data f_fglob->fg_data

static int fstat1(proc_t p, int fd, user_addr_t ub, user_addr_t xsecurity, 
       user_addr_t xsecurity_size, int isstat64) {
    struct fileproc *fp;
    // use fp_lookup to first get the fileproc
    if ((error = fp_lookup(p, fd, &fp, 0)) != 0) {
        return(error);
    }
    type = fp->f_type; // remember this is really fp->f_glob->f_type;
    data = fp->f_data; // .. and ditto for fp->f_glob->f_data;
    switch (type) {
        case DTYPE_VNODE: // data cast to a vnode_t
            if ((error = vnode_getwithref((vnode_t)data)) == 0) {
               /*
                * If the caller has the file open, and is not
                * requesting extended security information, we are
                * going to let them get the basic stat information.
                */
                if (xsecurity == USER_ADDR_NULL) {
                    error = vn_stat_noauth((vnode_t)data, sbptr, NULL, isstat64, ctx);
                } 
                else {
                    error = vn_stat((vnode_t)data, sbptr, &fsec, isstat64, ctx);
                }
                AUDIT_ARG(vnpath, (struct vnode *)data, ARG_VNODE1);
                (void)vnode_put((vnode_t)data);
            }
            break;
    #if SOCKETS
        case DTYPE_SOCKET:  // data cast to a struct socket *
            error = soo_stat((struct socket *)data, sbptr, isstat64);
            break;
    #endif /* SOCKETS */
        case DTYPE_PIPE: // data will be cast into a struct pipe (inside pipe_stat)
            error = pipe_stat((void *)data, sbptr, isstat64);
            break;
        case DTYPE_PSXSHM: // data will be case into a struct pshmnode (inside pshm_stat)
            error = pshm_stat((void *)data, sbptr, isstat64);
            break;
        case DTYPE_KQUEUE: // data actually ignored for a kqueue
            funnel_state = thread_funnel_set(kernel_flock, TRUE);
            error = kqueue_stat(fp, sbptr, isstat64, p);
            thread_funnel_set(kernel_flock, funnel_state);
            break;
}