// Listing 15-13: The filedesc structure, from bsd/sys/filedesc.h

struct filedesc {
    struct  fileproc **fd_ofiles;   /* file structures for open files */
    char    *fd_ofileflags;         /* per-process open file flags */
    struct  vnode *fd_cdir;         /* current directory */
    struct  vnode *fd_rdir;         /* root directory */
    int     fd_nfiles;              /* number of open files allocated */
    int     fd_lastfile;            /* high-water mark of fd_ofiles */
    int     fd_freefile;            /* approx. next free file */
    u_short   fd_cmask;             /* mask for file creation */
    uint32_t  fd_refcnt;            /* reference count */
    int     fd_knlistsize;          /* size of knlist */
    struct  klist *fd_knlist;       /* list of attached knotes */
    u_long  fd_knhashmask;          /* size of knhash */
    struct  klist *fd_knhash;       /* hash table for attached knotes */
    int     fd_flags;
};