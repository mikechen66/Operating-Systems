// Listing 12-15: Redirection of swap mmap(2) requests, from bsd/kern/kern_mman.c:

int mmap(proc_t p, struct mmap_args *uap, user_addr_t *retval) {
    struct fileproc *fp;
    register struct vnode *vp;
    // ...
    int fd = uap->fd;
    // ...
    err = fp_lookup(p, fd, &fp, 0);
    // ...
    vp = (struct vnode *)fp->f_fglob->fg_data;
    // ...
    if (vnode_isswap(vp)) {
        /*
        * Map swap files with a special pager
        * that returns obfuscated contents.
        */
        control = NULL;
        pager = swapfile_pager_setup(vp);
        if (pager != MEMORY_OBJECT_NULL) {
             control = swapfile_pager_control(pager);
        }
    //...
}