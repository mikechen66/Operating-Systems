// Listing 10-10: Host special ports and the macros to get them (osfmk/mach/host_special_ports.h)

/*
 * Always provided by kernel (cannot be set from user-space).
 */
#define HOST_PORT                        1
#define HOST_PRIV_PORT                   2
#define HOST_IO_MASTER_PORT              3 // used by IOKit (see chapter 13)
#define HOST_MAX_SPECIAL_KERNEL_PORT     7 /* room to grow */

/*
 * Not provided by kernel
 */
#define HOST_DYNAMIC_PAGER_PORT         (1 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_AUDIT_CONTROL_PORT         (2 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_USER_NOTIFICATION_PORT     (3 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_AUTOMOUNTD_PORT            (4 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_LOCKD_PORT                 (5 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_SEATBELT_PORT              (7 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_KEXTD_PORT                 (8 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_CHUD_PORT                  (9 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_UNFREED_PORT               (10 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_AMFID_PORT                 (11 + HOST_MAX_SPECIAL_KERNEL_PORT)
#define HOST_GSSD_PORT                  (12 + HOST_MAX_SPECIAL_KERNEL_PORT) // Lion
#define HOST_MAX_SPECIAL_PORT           (13 + HOST_MAX_SPECIAL_KERNEL_PORT)
                                        /* room to grow here as well */
/*
 * Special node identifier to always represent the local node.
 */
#define HOST_LOCAL_NODE                  -1
                        
/*
 * Definitions for ease of use.
 *
 * In the get call, the host parameter can be any host, but will generally
 * be the local node host port. In the set call, the host must the per-node
 * host port for the node being affected.
 */
#define host_get_host_port(host, port)  \
        (host_get_special_port((host),  \
        HOST_LOCAL_NODE, HOST_PORT, (port)))
#define host_set_host_port(host, port) (KERN_INVALID_ARGUMENT)
#define host_get_host_priv_port(host, port)     \
        (host_get_special_port((host),          \
        HOST_LOCAL_NODE, HOST_PRIV_PORT, (port)))
#define host_set_host_priv_port(host, port) (KERN_INVALID_ARGUMENT)
#define host_get_io_master_port(host, port)     \
        (host_get_special_port((host),          \
        HOST_LOCAL_NODE, HOST_IO_MASTER_PORT, (port)))
#define host_set_io_master_port(host, port) (KERN_INVALID_ARGUMENT)
// ... (others defined similarly)…