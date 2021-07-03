// Listing 15-14: fp_lookup (from bsd/kern/kern_descrip.c)

/*
 * fp_lookup
 *
 * Description: Get fileproc pointer for a given fd from the per process
 *              open file table of the specified process and if successful,
 *              increment the f_iocount
 *
 * Parameters:  p                               Process in which fd lives
 *              fd                              fd to get information for
 *              resultfp                        Pointer to result fileproc
 *                                              pointer area, or 0 if none
 *              locked                          !0 if the caller holds the
 *                                              proc_fdlock, 0 otherwise
 *
 * Returns:     0                       Success
 *              EBADF                   Bad file descriptor
 *
 * Implicit returns:
 *              *resultfp (modified)            Fileproc pointer
 *
 * Locks:       If the argument ‘locked' is non-zero, then the caller is
 *              expected to have taken and held the proc_fdlock; if it is
 *              zero, than this routine internally takes and drops this lock.
 */ 

int fp_lookup(proc_t p, int fd, struct fileproc **resultfp, int locked) {
    struct filedesc *fdp = p->p_fd;
    struct fileproc *fp;
    if (!locked)  // take lock to prevent race conditions
            proc_fdlock_spin(p);
    // A negative file descriptor, one that is larger than the count of open files,
    // one that has no fileproc * entry, or one that is reserved — all return EBADF
    if (fd < 0 || fdp == NULL || fd >= fdp->fd_nfiles ||
                    (fp = fdp->fd_ofiles[fd]) == NULL ||
                    (fdp->fd_ofileflags[fd] & UF_RESERVED)) {
        if (!locked) // failure. Drop lock first
            proc_fdunlock(p);
            // and return error..
            return (EBADF);
    }
    fp->f_iocount++;
    // If we found an entry, fp points to it. This is also what we return to caller.
    if (resultfp)
        *resultfp = fp;
    // can safely let go of the lock
    if (!locked)
        proc_fdunlock(p);
        return (0); // success
}