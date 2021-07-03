// Listing 14-6: The implementation of kqueue(2), from bsd/sys/kern_event.c

int kqueue(struct proc *p, __unused struct kqueue_args *uap, int32_t *retval) {
    struct kqueue *kq;
    struct fileproc *fp;
    int fd, error;
    // allocate file structure fp as file descriptor fd
    error = falloc(p, &fp, &fd, vfs_context_current());
    if (error) {
        return (error);
    }
    // allocate actual kqueue
    kq = kqueue_alloc(p);
    if (kq == NULL) {
        fp_free(p, fd, fp);
        return (ENOMEM);
    }
    fp->f_flag = FREAD | FWRITE; // make descriptor readable/writable
    fp->f_type = DTYPE_KQUEUE;   // mark descriptor type as a queue
    fp->f_ops = &kqueueops;      // tie kqueue operations to file operations
    fp->f_data = (caddr_t)kq;    // tie kqueue to file structure
    // kqueue is not really backed by a file, so release unnecessary parts
    proc_fdlock(p);
    procfdtbl_releasefd(p, fd, NULL);
    fp_drop(p, fd, fp, 1);
    proc_fdunlock(p);
    *retval = fd;                // return fd to user
    return (error);
}