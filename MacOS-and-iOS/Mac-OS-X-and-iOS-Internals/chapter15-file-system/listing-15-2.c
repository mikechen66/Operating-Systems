// Listing 15-2: Using <sys/disk.h> ioctls to query information on a disk

#include <sys/disk.h> // disk ioctls are here..
#include <errno.h>    // errno!
#include <stdio.h>    // printf, etc..
#include <string.h>   // strncpy..
#include <fcntl.h>    // O_RDONLY
#include <stdlib.h>   // exit(), etc..

#define BUFSIZE 1024

// Simple program to demonstrate use of DKIO* ioctls:
// Usage: ... /dev/disk1 or ... disk1
void main (int argc, char **argv) {
    uint64_t bs, bc,rc;
    char fp[BUFSIZE];
    char p[BUFSIZE];
    strncpy (p, argv[1], BUFSIZE);
    if(p[0] != '/') {
        snprintf(p, BUFSIZE -10,  "/dev/%s", p);
    }
    int fd = open(p, O_RDONLY);
    if(fd == -1) {
        fprintf(stderr, “%s: unable to open %s\n”, argv[0], p);
        perror (”open”);
        exit (1);
    }
    rc = ioctl(fd, DKIOCGETBLOCKSIZE, &bs);
    if (rc < 0) {
        fprintf (stderr, “DKIOCGETBLOCKSIZE failed\n”); exit(2); 
    }
    else {
        fprintf (stderr, “Block size:\t%d\n”,bs);
    }
    rc = ioctl(fd, DKIOCGETBLOCKCOUNT, &bc);
    fprintf (stderr, “Block count:\t%ld\n”, bc);
    rc = ioctl(fd, DKIOCGETFIRMWAREPATH, &fp);
    fprintf (stderr, “Fw Path:\t%s\nTotal size:\t%ldM\n”, fp, (bs * bc) / (1024 * 1024));
}


/*
You can then follow along on your device using the commands shown here in Output 15-2:

Output 15-2: Creating and attaching an Apple Partition Map formatted disk image
root@Minion (/)# hdiutil create -layout SPUD -megabytes 256 /tmp/testAPM.dmg
...............................................................................
created: /tmp/xx.dmg
root@Minion (/)# ls -l /tmp/testAPM.dmg 
-rw-r--r--@ 1 root  wheel  268435456 Jun 19 07:13 /tmp/testAPM.dmg
root@Minion (/)# hdid –nomount /tmp/testAPM.dmg
/dev/disk4               Apple_partition_scheme              
/dev/disk4s1             Apple_partition_map                 
/dev/disk4s2             Apple_HFS
root@Minion (/)# diskutil partitionDisk disk4 APM HFS+ “Test HFS+” 25% hfsx \
                      “Test HFSX” 25% jhfs+ “Journaled+” 25% free “ignored” 25%
Started partitioning on disk4
Unmounting disk
[  \   \   \   \   \   \   \   \   \   \   \   \   \   \  ] 
[  \   \   \   \   \   \   \   \   \   \   \   \   \   \  ] 
Creating partition map
Waiting for disks to reappear
Formatting disk4s2 as Mac OS Extended with name Test HFS+
Formatting disk4s3 as Mac OS Extended (Case-sensitive) with name Test HFSX
Formatting disk4s4 as Mac OS Extended (Journaled) with name Journaled+
[ / 0%..10%..20%..30%..40%..50%..60%..70%..80%........... ] 
Finished partitioning on disk4
/dev/disk4
   #:                       TYPE NAME                    SIZE       IDENTIFIER
   0:     Apple_partition_scheme                        *268.4 MB   disk4
   1:        Apple_partition_map                         32.3 KB    disk4s1
   2:                  Apple_HFS Test HFS+               67.1 MB    disk4s2
   3:                 Apple_HFSX Test HFSX               67.1 MB    disk4s3
   4:                  Apple_HFS Journaled+              67.1 MB    disk4s4
root@Minion (/)# hdid -nomount /tmp/testAPM.dmg/dev/disk4
               Apple_partition_scheme 
/dev/disk4s1             Apple_partition_map                 
/dev/disk4s2             Apple_HFS                           /Volumes/Test HFS+
/dev/disk4s3             Apple_HFSX                          /Volumes/Test HFSX
/dev/disk4s4             Apple_HFS                           /Volumes/Journaled+
 */