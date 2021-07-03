// Listing 15-17: fo_read from bsd/kern/kern_descript.c

int fo_read(struct fileproc *fp, struct uio *uio, int flags, vfs_context_t ctx) {
    // simple pass through. Remember that by f_ops we mean f_fglob->f_ops
    return ((*fp->f_ops->fo_read)(fp, uio, flags, ctx));
}