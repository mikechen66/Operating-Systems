// Listing 3-5: A bare bones FSEvents-based file monitor

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>     // for _IOW, a macro required by FSEVENTS_CLONE
#include <sys/types.h>     // for uint32_t and friends, on which fsevents.h relies
#include <sys/fsevents.h>

// The struct definitions are taken from bsd/vfs/vfs_events.c
// since they are no long public in <sys/fsevents.h>
#pragma pack(1)
typedef struct kfs_event_a {
  uint16_t type;
  uint16_t refcount;
  pid_t    pid;
} kfs_event_a;

typedef struct kfs_event_arg {
  uint16_t type;
  uint16_t pathlen;
  char data[0];
} kfs_event_arg;

#pragma pack()
int print_event (void *buf, int off) {
    // Simple function to print event – currently a simple printf of "event!”.
    // The reader is encouraged to improve this, as an exercise.
    // This book's website has a much better (and longer) implementation
    printf(”Event!\n”);
    return (off);
}

void main (int argc, char **argv) {
    int fsed, cloned_fsed;
    int i; 
    int rc;
    fsevent_clone_args  clone_args;
    char buf[BUFSIZE];
    fsed = open (”/dev/fsevents”, O_RDONLY);
    int8_t  events[FSE_MAX_EVENTS];
    if (fsed < 0) {
        perror (”open”); 
        exit(1);
    }
    // Prepare event mask list. In our simple example, we want everything
    // (i.e. all events, so we say "FSE_REPORT” all). Otherwise, we
    // would have to specifically toggle FSE_IGNORE for each:
    //
    // e.g.
    //       events[FSE_XATTR_MODIFIED] = FSE_IGNORE;
    //       events[FSE_XATTR_REMOVED]  = FSE_IGNORE;
    // etc..
    for (i = 0; i < FSE_MAX_EVENTS; i++) {
        events[i] = FSE_REPORT; 
    }
    memset(&clone_args, '\0', sizeof(clone_args));
    clone_args.fd = &cloned_fsed; // This is the descriptor we get back
    clone_args.event_queue_depth = 10;
    clone_args.event_list = events;
    clone_args.num_events = FSE_MAX_EVENTS;
    
    // Request our own fsevents handle, cloned
    rc = ioctl (fsed, FSEVENTS_CLONE, &clone_args);
    
    if (rc < 0) { 
        perror ("ioctl"); 
        exit(2);
    }
    printf ("So far, so good!\n");
    close (fsed);
    while ((rc = read(cloned_fsed, buf, BUFSIZE)) > 0) {
        // rc returns the count of bytes for one or more events:
        int offInBuf = 0;
        while (offInBuf < rc) {
            struct kfs_event_a *fse = (struct kfs_event_a *)(buf + offInBuf);
            struct kfs_event_arg *fse_arg;
            struct fse_info *fse_inf;
            if (offInBuf) { 
                printf (”Next event: %d\n”, offInBuf);
            };
            offInBuf += print_event(buf,offInBuf); // defined elsewhere
        } // end while offInBuf..
        if (rc != offInBuf) { 
            fprintf (stderr, "***Warning: Some events may be lost\n"); 
        }
    } // end while rc = ..
} // end main