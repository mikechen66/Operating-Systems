// Listing 15-12: libFuse's do_write (from fuse's lib/fuse_lowlevel.c)

static void do_write(fuse_req_t req, fuse_ino_t nodeid, const void *inarg) {
    struct fuse_write_in *arg = (struct fuse_write_in *) inarg;
    struct fuse_file_info fi;
    memset(&fi, 0, sizeof(fi));
    fi.fh = arg->fh;
    fi.fh_old = fi.fh;
    fi.writepage = arg->write_flags & 1;

    // If there is a registered write handler, execute it
    if (req->f->op.write)
        req->f->op.write(req, nodeid, PARAM(arg), 
                         arg->size, arg->offset, &fi);
    else // no handler – deny system call
        fuse_reply_err(req, ENOSYS);
}
// This is LibFUSE's handler for “low level” operations:
static struct {
void (*func)(fuse_req_t, fuse_ino_t, const void *);
const char *name;
} fuse_ll_ops[] = {
[FUSE_LOOKUP] = { do_lookup, “LOOKUP” },
[FUSE_FORGET] = { do_forget, “FORGET” },
[FUSE_GETATTR] = { do_getattr, “GETATTR” },
[FUSE_SETATTR] = { do_setattr, “SETATTR” },
[FUSE_READLINK] = { do_readlink, “READLINK” },
[FUSE_SYMLINK] = { do_symlink, “SYMLINK” },
[FUSE_MKNOD] = { do_mknod, “MKNOD” },
[FUSE_MKDIR] = { do_mkdir, “MKDIR” },
[FUSE_UNLINK] = { do_unlink, “UNLINK” },
[FUSE_RMDIR] = { do_rmdir, “RMDIR” },
[FUSE_RENAME] = { do_rename, “RENAME” },
[FUSE_LINK] = { do_link, “LINK” },
[FUSE_OPEN] = { do_open, “OPEN” },
[FUSE_READ] = { do_read, “READ” },
[FUSE_WRITE] = { do_write, “WRITE” },
[FUSE_STATFS] = { do_statfs, “STATFS” },
[FUSE_RELEASE] = { do_release, “RELEASE” },
// many other operations
}