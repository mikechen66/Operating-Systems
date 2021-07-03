// Listing 17-8: The protosw structure, from bsd/sys/protosw.h
struct protosw {
        short   pr_type;                /* socket type used for */
        struct  domain *pr_domain;      /* domain protocol a member of */
        short   pr_protocol;            /* protocol number */
        unsigned int pr_flags;          /* see below */
/* protocol-protocol hooks */
        void    (*pr_input)(struct mbuf *, int len);
                                        /* input to protocol (from below) */
        int     (*pr_output)(struct mbuf *m, struct socket *so);
                                        /* output to protocol (from above) */
        void    (*pr_ctlinput)(int, struct sockaddr *, void *);
                                        /* control input (from below) */
        int     (*pr_ctloutput)(struct socket *, struct sockopt *);
                                        /* control output (from above) */
/* user-protocol hook */
        void    *pr_ousrreq;            // deprecated
/* utility hooks */
        void    (*pr_init)(void);       /* initialization hook */
#if __APPLE__
        void    (*pr_unused)(void);     /* placeholder - fasttimo is removed */
#else
        void    (*pr_fasttimo)(void);
                                        /* fast timeout (200ms) */
#endif
        void    (*pr_slowtimo)(void);
                                        /* slow timeout (500ms) */
        void    (*pr_drain)(void);
                                        /* flush any excess space possible */
#if __APPLE__
        int     (*pr_sysctl)(int *, u_int, void *, size_t *, void *, size_t);
                                        /* sysctl for protocol */
#endif
        struct  pr_usrreqs *pr_usrreqs; /* supersedes pr_usrreq() */
#if __APPLE__
     int   (*pr_lock)(struct socket *so, int locktype, void *debug); /* lock function */
     int   (*pr_unlock)(struct socket *so, int locktype, void *debug); /* unlock  */
#ifdef _KERN_LOCKS_H_
        lck_mtx_t *     (*pr_getlock)   (struct socket *so, int locktype);
#else
        void *  (*pr_getlock)   (struct socket *so, int locktype);
#endif
#endif
#if __APPLE__
/* Implant hooks */
        TAILQ_HEAD(, socket_filter) pr_filter_head;
        struct protosw *pr_next;        /* Chain for domain */
        u_int32_t       reserved[1];            /* Padding for future use */
#endif
};