// Listing 17-19: The XNU socket filter implementation

struct sflt_filter {
    sflt_handle              sf_handle; // accessible to apps using SO_NKE setsockopt(2)
    int                      sf_flags;  // SFLT_GLOBAL, SFLT_PROG or SFLT_EXTENDED
    char                    *sf_name;
    sf_unregistered_func     sf_unregistered;
    sf_attach_func           sf_attach;      // called on successful sflt_attach()
    sf_detach_func           sf_detach;      // called on successful sflt_detach()
    sf_notify_func           sf_notify;      // called with an sflt_event_t specifying
                                            // connect/disconnect/bound/buffers full/etc
    sf_getpeername_func      sf_getpeername; // called on getpeername(2)
    sf_getsockname_func      sf_getsockname; // called on getsockname(2)
    sf_data_in_func          sf_data_in;     // called before data is delivered to thread
    sf_data_out_func         sf_data_out;    // called before data is queued for sending
    sf_connect_in_func       sf_connect_in;  // called for incoming connections - accept
    sf_connect_out_func      sf_connect_out; // called for outgoing connections – connect
    sf_bind_func             sf_bind;        // called on bind(2)
    sf_setoption_func        sf_setoption;   // called on setsockopt(2)
    sf_getoption_func        sf_getoption;   // called on getsockopt(2)
    sf_listen_func           sf_listen;      // called on listen(2)
    sf_ioctl_func            sf_ioctl;       // called on ioctl(2)
        /*
         * The following are valid only if SFLT_EXTENDED flag is set.
         * Initialize sf_ext_len to sizeof sflt_filter_ext structure.
         * Filters must also initialize reserved fields with zeroes.
         */
    struct sflt_filter_ext {
        unsigned int        sf_ext_len;
        sf_accept_func      sf_ext_accept;     // called before accept(2) returns
        void               *sf_ext_rsvd[5];    /* Reserved */
    } sf_ext;
#define sf_len          sf_ext.sf_ext_len
#define sf_accept       sf_ext.sf_ext_accept
};