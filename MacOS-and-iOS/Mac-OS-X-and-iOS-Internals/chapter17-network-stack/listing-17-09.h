// Listing 17-9: The struct pr_usrreqs definition in bsd/sys/protosw.h

/*
 * If the ordering here looks odd, that's because it's alphabetical.
 * Having this structure separated out from the main protoswitch is allegedly
 * a big (12 cycles per call) lose on high-end CPUs.  We will eventually
 * migrate this stuff back into the main structure.
 */

struct pr_usrreqs {
        int     (*pru_abort)(struct socket *so);
        int     (*pru_accept)(struct socket *so, struct sockaddr **nam);
        int     (*pru_attach)(struct socket *so, int proto, struct proc *p);
        int     (*pru_bind)(struct socket *so, struct sockaddr *nam,
                                 struct proc *p);
        int     (*pru_connect)(struct socket *so, struct sockaddr *nam,
                                    struct proc *p);
        int     (*pru_connect2)(struct socket *so1, struct socket *so2);
        int     (*pru_control)(struct socket *so, u_long cmd, caddr_t data,
                                    struct ifnet *ifp, struct proc *p);
        int     (*pru_detach)(struct socket *so);
        int     (*pru_disconnect)(struct socket *so);
        int     (*pru_listen)(struct socket *so, struct proc *p);
        int     (*pru_peeraddr)(struct socket *so, struct sockaddr **nam);
        int     (*pru_rcvd)(struct socket *so, int flags);
        int     (*pru_rcvoob)(struct socket *so, struct mbuf *m, int flags);
        int     (*pru_send)(struct socket *so, int flags, struct mbuf *m,
                                 struct sockaddr *addr, struct mbuf *control,
                                 struct proc *p);
#define PRUS_OOB        0x1
#define PRUS_EOF        0x2
#define PRUS_MORETOCOME 0x4
        int     (*pru_sense)(struct socket void  *sb, int isstat64);
        int     (*pru_shutdown)(struct socket *so);
        int     (*pru_sockaddr)(struct socket *so, struct sockaddr **nam);
        /*
         * These three added later, so they are out of order.  They are used
         * for shortcutting (fast path input/output) in some protocols.
         * XXX - that's a lie, they are not implemented yet
         * Rather than calling sosend() etc. directly, calls are made
         * through these entry points.  For protocols which still use
         * the generic code, these just point to those routines.
         */
        int     (*pru_sosend)(struct socket *so, struct sockaddr *addr,
                                   struct uio *uio, struct mbuf *top,
                                   struct mbuf *control, int flags);
        int     (*pru_soreceive)(struct socket *so,
                                      struct sockaddr **paddr,
                                      struct uio *uio, struct mbuf **mp0,
                                      struct mbuf **controlp, int *flagsp);
        int     (*pru_sopoll)(struct socket *so, int events,
                                   struct ucred *cred, void *);
};