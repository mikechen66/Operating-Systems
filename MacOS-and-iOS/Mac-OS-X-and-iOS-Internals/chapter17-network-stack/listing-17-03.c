// Listing 17-3: A simple PF_SYSTEM/SYSPROTO_EVENT listener

#include <sys/socket.h>     // for socket(2) and friends
#include <sys/kern_event.h> // for kev_* and kern_event_* types

/*
 * A rudimentary PF_SYSTEM event listener, in 50 lines or less. Works on iOS too
 */
void main (int argc, char **argv) {
    struct kev_request req;
    char buf[1024];
    int rc;
    struct kern_event_msg *kev;
    // Setup the system socket
    int ss = socket(PF_SYSTEM, SOCK_RAW, SYSPROTO_EVENT);
    // Set filtering parameters. Only interested in Apple, but not filtering on
    // classes for now
    req.vendor_code  = KEV_VENDOR_APPLE;  // Apple is pretty much the only vendor
    req.kev_class    = KEV_ANY_CLASS;     // No class filtering (show all)
    req.kev_subclass = KEV_ANY_SUBCLASS;  // No subclass filtering (show all)
    // Use ioctl(2) to set the filter on the socket
    if (ioctl(fd, SIOCSKEVFILT, &req)) {
        perror(”Unable to set filter\n”); 
        exit(1); 
    }
    while (1) {
     // can use if (ioctl(fd, SIOCGKEVID, &id)) to get next ID
     // or simply read and block until an event occurs..
     rc = read (ss, buf, 1024);
     kev = (struct kern_event_msg *)buf;
     // Print event class and class (data is event dependent)
     // A better implementation would convert class, subclass and code to text
     // and is left as an exercise to the reader.
     printf (”Event %d: (%d bytes). Vendor: %d Class: %d/%d\n”,
        kev->id, kev->total_size, kev->vendor_code, kev->kev_class, kev->kev_subclass);
     printf (”Code: %d\n”,kev->event_code);
    } // end while
}