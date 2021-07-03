// Listing 13-3: The struct uthread, from bsd/sys/user.h

struct  uthread {
    /* syscall parameters, results and catches */
    u_int64_t uu_arg[8]; /* arguments to current system call */
    int     *uu_ap;      /* pointer to arglist */
    int uu_rval[2];

    /* thread exception handling */
    int     uu_exception;
    mach_exception_code_t uu_code;  /* “code” to trap */
    mach_exception_subcode_t uu_subcode;
    char uu_cursig;               /* p_cursig for exc. */
    /* support for syscalls which use continuations */
    struct _select { .. } uu_select;
    union {
    struct _kqueue_scan { } ss_kqueue_scan; /* saved state for kevent_scan() */
    struct _kevent { }   ss_kevent;         /* saved state for kevent()      */
    } uu_kevent;
    struct _kauth { } uu_kauth;          
    /* internal support for continuation framework */
    int (*uu_continuation)(int);
    int uu_pri;
    int uu_timo;
    caddr_t uu_wchan;                /* sleeping thread wait channel */
    const char *uu_wmesg;            /* ... wait message             */
    int uu_flag;
    int uu_iopol_disk;               /* disk I/O policy */ // iOS only
    struct proc * uu_proc;           // parent to owning process
    void * uu_userstate;
    // ...
    // signal stuff (uu_sig* fields)
    struct vfs_context uu_context;   /* thread + cred */
    sigset_t  uu_vforkmask;          /* saved signal mask during vfork */
    TAILQ_ENTRY(uthread) uu_list;    /* List of uthreads in proc */
    struct kaudit_record    *uu_ar;  /* audit record */
    struct task*    uu_aio_task;     /* target task for async io */
    lck_mtx_t       *uu_mtx;
    // throttled I/O support…
    struct kern_sigaltstack uu_sigstk;
    int             uu_defer_reclaims;
    int             uu_notrigger;    // should this thread trigger automount?
    vnode_t         uu_cdir;         /* per thread CWD */
    int             uu_dupfd;        /* fd in fdesc_open/dupfdopen */
    // JOE_DEBUG's stuff..
    // DTRACE support ..
    void *          uu_threadlist;
    char *          pth_name;        // used for pthread_setname_np (over proc_info)
    struct ksyn_waitq_element  uu_kwe;     // use*d* for pthread synch 
};