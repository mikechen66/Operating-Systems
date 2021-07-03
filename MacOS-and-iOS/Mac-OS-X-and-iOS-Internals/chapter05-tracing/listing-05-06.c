// Listing 5-6: A simple memory leak demonstration

#include <stdio.h>

int f() {  
    char *c = malloc(24);
}

void main() {
    f();
    sleep(100);
}

/* 
Running leaks on the program produces an output similar to Output 5-8. Note the 
part in italic, which is displayed if MallocStackLogging is set.

Output 5-8: A leaks(1) generated report for the program from the previous listing
morpheus@ergo (/tmp)$ MallocStackLogging=1 ./m &
[1] 8368              # Run process in background to get PID.
m(8368) malloc: recording malloc stacks to disk using standard recorder
m(8368) malloc: stack logs being written into /tmp/stack-logs.8368.m.KaQPVh.index
morpheus@ergo (/tmp) $ leaks 8368
Process:         m [8368]
Path:            /tmp/m
Load Address:    0x100000000
Identifier:      m
Version:         ??? (???)
Code Type:       X86-64 (Native)
Parent Process:  bash [6519]
Date/Time:       2011-11-22 07:27:49.322 -0500
OS Version:      Mac OS X 10.6.8 (10K549)
Report Version:  7
leaks Report Version:  2.0
Process 8311: 3 nodes malloced for 1 KB
Process 8311: 1 leak for 32 total leaked bytes.
Leak: 0x100100080  size=32  zone: DefaultMallocZone_0x100004000
       0x00000000 0x00000000 0x00000000 0x00000000 ................
       0x00000000 0x00000000 0x00000000 0x00000000 ................
Call stack: [thread 0x7fff70ed8cc0]: | 0x1 | start | main | f | malloc | 
malloc_zone_malloc
Binary Images:
    0x100000000 -      0x100000ff7 +m (??? - ???) <18B7E067-D1EB-30CB-8097-04ED600B3628> 
/Users/morpheus/m
    0x7fff5fc00000 -   0x7fff5fc3bdef  dyld (132.1 - ???) <DB8B8AB0-0C97-B51C-BE8B-
B79895735A33> /usr/lib/dyld
...
 */