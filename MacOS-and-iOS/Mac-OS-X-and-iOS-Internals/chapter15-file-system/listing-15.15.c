// /* file types */ 
// these are the types allowable for fg_type

typedef enum {
    DTYPE_VNODE = 1, /* file */
    DTYPE_SOCKET, /* communications endpoint */
    DTYPE_PSXSHM, /* POSIX Shared memory */
    DTYPE_PSXSEM, /* POSIX Semaphores */
    DTYPE_KQUEUE, /* kqueue */
    DTYPE_PIPE, /* pipe */
DTYPE_FSEVENTS /* fsevents */
} file_type_t;

struct fileglob {
    LIST_ENTRY(fileglob) f_list;/* list of active files */
    LIST_ENTRY(fileglob) f_msglist;/* list of active files */
    int32_t fg_flag; /* see fcntl.h */
    file_type_t fg_type; /* descriptor type */
    int32_t fg_count; /* reference count */
    int32_t fg_msgcount; /* references from message queue */
    kauth_cred_t fg_cred; /* credentials associated with descriptor */
    struct fileops { // generic file operations
        int (*fo_read) (struct fileproc *fp, struct uio *uio,
        int flags, vfs_context_t ctx);
        int (*fo_write) (struct fileproc *fp, struct uio *uio,
        int flags, vfs_context_t ctx);

#define FOF_OFFSET 0x00000001 /* offset supplied to vn_write */
#define FOF_PCRED 0x00000002 /* cred from proc, not current thread */

int (*fo_ioctl) (struct fileproc *fp, u_long com,
caddr_t data, vfs_context_t ctx);
int (*fo_select) (struct fileproc *fp, int which,
void *wql, vfs_context_t ctx);
int (*fo_close) (struct fileglob *fg, vfs_context_t ctx);
int (*fo_kqfilter) (struct fileproc *fp, struct knote *kn,
vfs_context_t ctx);
int (*fo_drain) (struct fileproc *fp, vfs_context_t ctx);
} *fg_ops;
off_t fg_offset;
void *fg_data; /* vnode or socket or SHM or semaphore */
lck_mtx_t fg_lock;
int32_t fg_lflags; /* file global flags */
#if CONFIG_MACF
    struct label *fg_label; /* JMM - use the one in the cred? */
#endif
};