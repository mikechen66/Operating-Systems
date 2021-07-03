// Listing 11-19: Mach architecture-independent exceptions from <mach/exception_types.h>

#define EXC_BAD_ACCESS          1       /* Could not access memory */
                /* Code contains kern_return_t describing error. */
                /* Subcode contains bad memory address. */
#define EXC_BAD_INSTRUCTION     2       /* Instruction failed */
                /* Illegal or undefined instruction or operand */
#define EXC_ARITHMETIC          3       /* Arithmetic exception */
                /* Exact nature of exception is in code field */
#define EXC_EMULATION           4       /* Emulation instruction */
                /* Emulation support instruction encountered */
                /* Details in code and subcode fields   */
#define EXC_SOFTWARE            5       /* Software generated exception */
                /* Exact exception is in code field. */
                /* Codes 0 - 0xFFFF reserved to hardware */
                /* Codes 0x10000 - 0x1FFFF reserved for OS emulation (Unix) */
#define EXC_BREAKPOINT          6       /* Trace, breakpoint, etc. */
                /* Details in code field. */
#define EXC_SYSCALL             7       /* System calls. */
#define EXC_MACH_SYSCALL        8       /* Mach system calls. */
#define EXC_RPC_ALERT           9       /* RPC alert */
#define EXC_CRASH               10      /* Abnormal process exit */

// Mountain Lion/iOS Add code 11 (constant unknown) for ledger resource exceptions