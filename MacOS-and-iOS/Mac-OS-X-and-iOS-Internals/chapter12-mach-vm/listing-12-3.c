// Listing 12-3: mach_vm_wire, from osfmk/vm/vm_user.c:

/*
 * NOTE: these routine (and this file) will no longer require mach_host_server.h
 * when mach_vm_wire and vm_wire are changed to use ledgers.
 */
#include <mach/mach_host_server.h>
/*
 * mach_vm_wire
 * Specify that the range of the virtual address space
 * of the target task must not cause page faults for
 * the indicated accesses.
 *
 * [ To unwire the pages, specify VM_PROT_NONE. ]
 */

kern_return_t
mach_vm_wire(
    host_priv_t             host_priv,
    vm_map_t                map,
    mach_vm_offset_t        start,
    mach_vm_size_t  size,
    vm_prot_t               access)