// Listing 17-2: The kern_ctl_reg structure, from sys/kern_control.h

struct kern_ctl_reg {
    /* control information */
    char            ctl_name[MAX_KCTL_NAME];
    u_int32_t       ctl_id;   // ignored, unless CTL_FLAG_REG_ID_UNIT is specified
    u_int32_t       ctl_unit;
    /* control settings */
    u_int32_t   ctl_flags; // CTL_FLAG_PRIVILEGED - uid 0 processes only
                           // CTL_FLAG_REG_SOCK_STREAM – SOCK_STREAM only, not DGRAM
                           // CTL_DATA_NOWAKEUP – Don't wake up process on data received
    u_int32_t   ctl_sendsize; // override default send size, or leave 0
    u_int32_t   ctl_recvsize; // override default recv size, or leave 0
    /* Dispatch functions  */   
    // all return errno. The kern_ctl_reg argument is returned by ctl_register()
    ctl_connect_func    ctl_connect;    //(kern_ctl_ref kcr,sockaddr_ctl *sac,void **unit);
    ctl_disconnect_func ctl_disconnect; //(kern_ctl_ref kcr,u_int32_t unit,void *unitinfo);
    ctl_send_func       ctl_send;       //kern_ctl_ref kcr,u_int32_t unit,void *unitinfo,
                                        //mbuf_t m, int flags);
    // ctl_setopt and ctl_getopt are used for get/setsockopts and share the same prototype:
    // kern_ctl_ref kcr, u_int32_t unit, void *unitinfo, int opt, void *data, size_t len)
    ctl_setopt_func     ctl_setopt; 
    ctl_getopt_func     ctl_getopt;
};