// Listing 13-2: Process group declaration in bsd/sys/proc_internal.h (implemented in bsd/kern/kern_proc.c)

// In the following, LL implies LIST_LOCK, and PGL implies Process Group Lock, which
// are system wide locks used to protect structure fields against concurrent access

struct  pgrp {
    LIST_ENTRY(pgrp)  pg_hash;      /* Hash chain. (LL) */
    LIST_HEAD(, proc) pg_members;   /* Pointer to pgrp members. (PGL) */
    struct  session * pg_session;   /* Pointer to session. (LL ) */
    pid_t             pg_id;        /* Pgrp id. (static) */
    int               pg_jobc;      /* # procs qualifying pgrp for job control (PGL) */
    int               pg_membercnt; /* Number of processes in the pgrocess group (PGL) */
    int               pg_refcount;  /* number of current iterators (LL) */
    unsigned int      pg_listflags; /* (LL) */
    lck_mtx_t         pg_mlock;     /* mutex lock to protect pgrp */
};

/* defns for pgrp_iterate */
#define PGRP_DROPREF            1
#define PGRP_BLOCKITERATE       2

// pgrp_iterate is used to iterate over the pgrp->pg_members list  
extern int pgrp_iterate(struct pgrp * pgrp, // pgrp to iterate over
                        int flags, 
                        int (*callout)(proc_t , void *), // function to execute on each item
                        void *arg,                       // 2nd argument to be passed to callout
                        int (*filterfn)(proc_t , void *),// function to decide callout execution
                        void *filterarg);                // 2nd argument to be passed to filterfn