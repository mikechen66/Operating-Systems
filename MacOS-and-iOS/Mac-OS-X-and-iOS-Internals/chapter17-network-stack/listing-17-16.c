// Listing 17-16: utun_ctl_connect(), demonstrating interface creation

static errno_t utun_ctl_connect(kern_ctl_ref kctlref,
                                struct sockaddr_ctl *sac,
                                void **unitinfo) {
    struct ifnet_init_params utun_init;
    struct utun_pcb         *pcb;
    errno_t                  result;
    struct ifnet_stats_param stats;
    /* kernel control allocates, interface frees */
    pcb = utun_alloc(sizeof(*pcb));
    if (pcb == NULL)
        return ENOMEM;
    /* Setup the protocol control block */
    bzero(pcb, sizeof(*pcb));
    *unitinfo = pcb;
    pcb->utun_ctlref = kctlref;
    pcb->utun_unit = sac->sc_unit;
    printf("utun_ctl_connect: creating interface utun%d\n", pcb->utun_unit - 1);
    /* Create the interface */
    // Name + unit will make up visible name (e.g. utun0)
    bzero(&utun_init, sizeof(utun_init));
    utun_init.name = “utun”;                
    utun_init.unit = pcb->utun_unit - 1;    
    utun_init.family = utun_family;
    utun_init.type = IFT_OTHER;
    utun_init.output = utun_output;
    utun_init.demux = utun_demux;
    utun_init.framer = utun_framer;
    utun_init.add_proto = utun_add_proto;
    utun_init.del_proto = utun_del_proto;
    utun_init.softc = pcb;
    utun_init.ioctl = utun_ioctl;
    utun_init.detach = utun_detached;
    result = ifnet_allocate(&utun_init, &pcb->utun_ifp);
    if (result != 0) {
        printf(”utun_ctl_connect - ifnet_allocate failed: %d\n”, result);
        utun_free(pcb);
        return result;
    }
    OSIncrementAtomic(&utun_ifcount);  // OSIncrementAtomic avoids having to lock
    /* Set flags and additional information.*/ // parameters which init cannot set
    ifnet_set_mtu(pcb->utun_ifp, 1500);
    // These flags are visible in ifconfig(8)
    ifnet_set_flags(pcb->utun_ifp,IFF_UP | IFF_MULTICAST | IFF_POINTOPOINT, 0xffff);
    /* The interface must generate its own IPv6 LinkLocal address,
     * if possible following the recommendation of RFC2472 to the 64bit interface ID
     */
    ifnet_set_eflags(pcb->utun_ifp, IFEF_NOAUTOIPV6LL, IFEF_NOAUTOIPV6LL);
    /* Reset the stats in case as the interface may have been recycled */
    bzero(&stats, sizeof(struct ifnet_stats_param));
    ifnet_set_stat(pcb->utun_ifp, &stats);
    /* Attach the interface */   // i.e. make it visible
    result = ifnet_attach(pcb->utun_ifp, NULL);
    if (result != 0) {
        printf(”utun_ctl_connect - ifnet_allocate failed: %d\n”, result);
        ifnet_release(pcb->utun_ifp);
        utun_free(pcb);
    }
    /* Attach to bpf */   // Must call bpfattach() if we want BPF (described later)
    if (result == 0)
        bpfattach(pcb->utun_ifp, DLT_NULL, 4);
    /* The interfaces resources allocated, mark it as running */
    if (result == 0)
        ifnet_set_flags(pcb->utun_ifp, IFF_RUNNING, IFF_RUNNING);
    return result;
}