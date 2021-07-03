// Listing 10-13: Rebooting the system, via the host API

#include <mach/mach.h>
void main() {
    mach_port_t     h = mach_host_self();
    mach_port_t     hp;
    kern_return_t   rc;
    /* request host privileged port. Will only work if we are root   */
    /* Note, this is the “right” way of doing it.. but we could also */
    /* use a short cut, left as an exercise                          */
    rc = host_get_host_priv_port (h, &hp);
    if (rc == KERN_SUCCESS) host_reboot(hp, 0);
        // If we are root, this won't even be reached.
        printf (”sorry\n”);
}