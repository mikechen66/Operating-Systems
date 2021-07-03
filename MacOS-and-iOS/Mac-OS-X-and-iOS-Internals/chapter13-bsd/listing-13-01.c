// Listing 13-1: proclists in XNU, from bsd/sys/proc_internal.h (implementation in bsd/kern/kern_proc.c)

LIST_HEAD(proclist, proc);
/* defns for proc_iterate */
#define PROC_ALLPROCLIST        1   /* walk the allproc list (procs not exited yet) */
#define PROC_ZOMBPROCLIST       2   /*  walk the zombie list */
#define PROC_NOWAITTRANS        4   /* do not wait for transitions (checkdirs only)  */

extern struct proclist allproc;     /* List of all processes. */
extern struct proclist zombproc;    /* List of zombie processes. */

int proc_iterate(int flags,                     //  PROC_* flags, above
                 int (*callout)(proc_t,void *), // funciton to execute on each item
                 void *arg,                     // 2nd argument to callout
                 int (*filterfn)(proc_t,void *),// function to decide callout execution 
                 void *filterarg);              // 2nd argument to be passed to filterfn