// Listing 10-14: The clock object, from osfmk/kern/clock.h

struct  clock_ops {
    int             (*c_config)(void);              /* configuration */
    int             (*c_init)(void);                /* initialize */
    kern_return_t   (*c_gettime)(   /* get time */
                            mach_timespec_t                 *cur_time);
    kern_return_t   (*c_getattr)(   /* get attributes */
                     clock_flavor_t           flavor,
                     clock_attr_t             attr,
                     mach_msg_type_number_t  *count); 
}

struct  clock {
    clock_ops_t                     cl_ops;                 /* operations list */
    struct ipc_port         *cl_service;    /* service port */
    struct ipc_port         *cl_control;    /* control port */
};