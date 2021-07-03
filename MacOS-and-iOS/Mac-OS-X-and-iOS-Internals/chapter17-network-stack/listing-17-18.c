// Listing 17-18: udp_send (from bsd/netinet/udp_usrreq.c)

static int udp_send(struct socket *so, __unused int flags, 
                    struct mbuf *m, struct sockaddr *addr,
                    struct mbuf *control, struct proc *p) {
    struct inpcb *inp;
    inp = sotoinpcb(so);
    if (inp == 0) {
        m_freem(m);
        return EINVAL;
    }
    return udp_output(inp, m, addr, control, p);
}

// Note retro style function definition of udp_output (if it ain't broken, don't fix it)
static int udp_output(inp, m, addr, control, p) {
    register struct inpcb *inp;
    struct mbuf *m;
    struct sockaddr *addr;
    struct mbuf *control;
    struct proc *p;

    // ...
    int soopts = 0;
    struct mbuf *inpopts;
    struct ip_moptions *mopts;
    struct route ro;
    struct ip_out_args ipoa = { IFSCOPE_NONE, 0 };
    // ...
    inpopts = inp->inp_options;
    soopts |= (inp->inp_socket->so_options & (SO_DONTROUTE | SO_BROADCAST));
    mopts = inp->inp_moptions;
    error = ip_output_list(m, 0, inpopts, &ro, soopts, mopts, &ipoa);
    // ...
}