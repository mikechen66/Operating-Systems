// Listing 14-9: the MAC_POLICY_SET macro from security/mac_policy.h

#define MAC_POLICY_SET(handle, mpops, mpname, mpfullname, lnames, lcount, slot, lfl ags, rflags) \
  static struct mac_policy_conf mpname##_mac_policy_conf = {      \
    .mpc_name               = #mpname,     /* Policy name */      \
    .mpc_fullname           = mpfullname,  /* Policy official name */   \
    .mpc_labelnames         = lnames,  /* Label names (char **) */     \
    .mpc_labelname_count    = lcount,  /* Count of label names */   \
    .mpc_ops                = mpops,  /* Policy operations (see below) */ \
    .mpc_loadtime_flags     = lflags, /* MPC_LOADTIME_FLAG_* constants */  \
    .mpc_field_off          = slot,   /* int * holding policy slot, or NULL */     \
    .mpc_runtime_flags      = rflags  /* only MPC_RUNTIME_FLAG_REGISTERED defined */ \
     };                                                              \
                                                                        \
        static kern_return_t                                            \
        kmod_start(kmod_info_t *ki, void *xd)                           \
        {                                                               \
                return mac_policy_register(&mpname##_mac_policy_conf,   \
                    &handle, xd);                                       \
        }                                                               \
                                                                        \
        static kern_return_t                                            \
        kmod_stop(kmod_info_t *ki, void *xd)                            \
        {                                                               \
                return mac_policy_unregister(handle);                   \
        }                                                               \
    extern kern_return_t _start(kmod_info_t *ki, void *data);       \
        extern kern_return_t _stop(kmod_info_t *ki, void *data);        \
                                                                        \
        KMOD_EXPLICIT_DECL(security.mpname, POLICY_VER, _start, _stop)  \
        kmod_start_func_t *_realmain = kmod_start;                      \
        kmod_stop_func_t *_antimain = kmod_stop;                        \
        int _kext_apple_cc = __APPLE_CC__