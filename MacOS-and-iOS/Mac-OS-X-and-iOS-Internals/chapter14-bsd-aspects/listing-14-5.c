// Listing 14-5: The structure returned for PROC_PIDWORKQUEUEINFO

struct proc_workqueueinfo {
    uint32_t     pwq_nthreads;       /* total number of workqueue threads */
    uint32_t     pwq_runthreads;     /* total number of running workqueue threads */
    uint32_t     pwq_blockedthreads; /* total number of blocked workqueue threads */
    uint32_t     pwq_state;          // new in Lion and later
};
/*
 * workqueue state (pwq_state field)
 */
#define WQ_EXCEEDED_CONSTRAINED_THREAD_LIMIT    0x1
#define WQ_EXCEEDED_TOTAL_THREAD_LIMIT          0x2

// Listing 14-5: sysctl oid implementation
struct sysctl_oid {
    struct sysctl_oid_list *oid_parent;
    SLIST_ENTRY(sysctl_oid) oid_link;
    int             oid_number;
    int             oid_kind;
    void            *oid_arg1;
    int             oid_arg2;
    const char      *oid_name;
    int             (*oid_handler) SYSCTL_HANDLER_ARGS;
    const char      *oid_fmt;
    const char      *oid_descr; /* offsetof() field / long description */
    int             oid_version;
    int             oid_refcnt;
};