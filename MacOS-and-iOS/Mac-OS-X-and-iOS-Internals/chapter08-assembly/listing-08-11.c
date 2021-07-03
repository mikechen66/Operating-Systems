// Listing 8-11: The sysent table

struct sysent {                 /* system call table */
    int16_t     sy_narg;        /* number of args */
    int8_t      sy_resv;        /* reserved  */
    int8_t      sy_flags;       /* flags */
    sy_call_t  *sy_call;        /* implementing function */
    sy_munge_t *sy_arg_munge32; 
    /* system call arguments munger for 32-bit process */
    sy_munge_t *sy_arg_munge64; 
    /* system call arguments munger for 64-bit process */
    int32_t     sy_return_type; /* system call return types */
    uint16_t    sy_arg_bytes;   /* Total size of arguments in bytes for
                                 * 32-bit system calls
                                 */
};

#ifndef __INIT_SYSENT_C__
extern struct sysent sysent[];
#endif  /* __INIT_SYSENT_C__ */
extern int nsysent;
#define NUM_SYSENT      439     // # of syscalls (+1) in Lion. (SL: 434, ML: 440, iOS5: 43