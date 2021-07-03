// Listing 17-4: An abbreviated socket structure, from bsd/sys/socketvar.h

struct socket {
    int     so_zone;                /* zone we were allocated from */
    short   so_type;                /* generic type, see socket.h */
    short   so_options;             /* from socket call, see socket.h */
    short   so_linger;              /* time to linger while closing */
    short   so_state;               /* internal state flags SS_*, below */
    void    *so_pcb;                /* protocol control block */
    struct  protosw *so_proto;      /* protocol handle */

    struct  sockbuf {... } so_rcv,  /* Receive queue (incoming) */
                           so_snd;  /* Send queue    (outgoing) */
    // 
    // ...  Many many more fields ..
    struct  label *so_label;        /* MAC label for socket */
    struct  label *so_peerlabel;    /* cached MAC label for socket peer */
    // ….
    // last process to interact with this socket
    u_int64_t       last_upid;
    pid_t           last_pid;
}