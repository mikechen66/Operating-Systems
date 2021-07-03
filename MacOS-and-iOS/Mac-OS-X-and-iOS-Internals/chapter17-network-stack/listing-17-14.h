// Listing 17-14: struct ifnet (abridged) from bsd/net/if_var.h

/*
 * Structure defining a network interface.
 *
 * (Would like to call this struct “if'', but C isn't PL/1.) // and luckily so!
 *
 */

struct ifnet { 
    void            *if_softc;      /* pointer to driver state */
    const char      *if_name;       /* name, e.g. “en” or “lo” */
    TAILQ_ENTRY(ifnet) if_link;     /* all struct ifnets are chained */
    struct ifaddrhead if_addrhead;  /* linked list of addresses per if */
    struct ifaddr    *if_lladdr;    /* link address (first/permanent) */
    int               if_pcount;    /* number of promiscuous listeners */
    struct bpf_if    *if_bpf;       /* packet filter structure */
                                   // ties BPF to ifnet
    u_short           if_index;     // sprintf()ed with if_name(%s%d),form instance name
    short             if_unit;      /* sub-unit for lower level driver */
    short             if_timer;     /* time ‘til if_watchdog called */
    short             if_flags;     /* up/down, broadcast, etc. */
    u_int32_t         if_eflags;    /* see <net/if.h> */
    int               if_capabilities;/* interface features & capabilities */
    int               if_capenable;   /* enabled features & capabilities */
    // ...MIB and internal if data
    ifnet_family_t          if_family;       /* value assigned by Apple */
    uintptr_t               if_family_cookie;
    // Interface handling functions. Note, unlike BSD, no if_input() handler
    ifnet_output_func       if_output;    // called to send frame through interface
    ifnet_ioctl_func        if_ioctl;     // set ioctl on interface
    ifnet_set_bpf_tap       if_set_bpf_tap;// Required for BPF support (see later)
    ifnet_detached_func     if_free;      //
    ifnet_demux_func        if_demux;     // Demux layer III protocol from incoming frame
    ifnet_event_func        if_event;     // Miscellaneous event handler
    ifnet_framer_func       if_framer;    // Build layer II frame for outgoing frame
    ifnet_add_proto_func    if_add_proto; // Add a layer III protocol binding
    ifnet_del_proto_func    if_del_proto; // Remove a layer III protocol binding
    ifnet_check_multi       if_check_multi;// Approve multicast address for interface
    struct proto_hash_entry *if_proto_hash;// link to bound layer III protocol hash
    void                   *if_kpi_storage;// reserved for NKEs
       
    // busy state and number of waiters ...
    struct ifnet_filter_head if_flt_head;  // list of interface filters (described later)
    // ... Multicast address tables and parameters
    // Unlike BSD, every interface has its own dedicated input thread (hence no if_input)
    struct dlil_threading_info *if_input_thread;
    // broadcast support
    #if CONFIG_MACF_NET
    struct label            *if_label;      /* interface MAC label */
    #endif
    u_int32_t               if_wake_properties;
    #if PF
    struct thread           *if_pf_curthread;
    struct pfi_kif          *if_pf_kif;
    #endif /* PF */
    // cached source and forward route entries
    // link layer reachability tree and bridge glues
    // flags, route reference count, if_traffic_class (QoS)
    // Extensions for IGMPv3 (IPv4) and MLDv2 (IPv6)
};