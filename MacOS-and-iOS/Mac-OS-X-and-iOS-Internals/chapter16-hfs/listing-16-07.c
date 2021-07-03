// Listing 16-7: Handling fragmented files, from hfs_vnop_open

int hfs_vnop_open(struct vnop_open_args *ap)
/*
 * On the first (non-busy) open of a fragmented
 * file attempt to de-frag it (if its less than 20MB).
 */
fp = VTOF(vp);
if (fp->ff_blocks &&
        fp->ff_extents[7].blockCount != 0 &&
        fp->ff_size <= (20 * 1024 * 1024)) {
    int no_mods = 0;
    struct timeval now;
    /*
    * Wait until system bootup is done (3 min).
    * And don't relocate a file that's been modified
    * within the past minute -- this can lead to
    * system thrashing.
    */
    if (!past_bootup) {
        microuptime(&tv);
        if (tv.tv_sec > (60*3)) {
            past_bootup = 1;
        }
    }
    microtime(&now);
    if ((now.tv_sec - cp->c_mtime) > 60) {
        no_mods = 1;
    }
    if (past_bootup && no_mods) {
        // relocate past volume next allocation hint, which is
        // very likely to be contiguous space
        (void) hfs_relocate(vp, hfsmp->nextAllocation + 4096,
        vfs_context_ucred(ap->a_context),
        vfs_context_proc(ap->a_context));
    }
    hfs_unlock(cp);
    return (0);
}