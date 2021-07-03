// Listing 10-17: A program to stop all but the main processor on a system

#include <mach/mach.h>
#include <stdio.h>

void main(int argc, char **argv) { 
    host_t        myhost = mach_host_self();
    host_t        mypriv;
    int           proc;
    kern_return_t kr;
    processor_port_array_t processorPorts;
    mach_msg_type_number_t        procCount;
    kr = host_get_host_priv_port(myhost,&mypriv);
    if (kr ) { 
        printf (”host_get_host_priv_port: %d\n”, kr); 
        exit(1);
    }
    // Get the ports of all the processors in the system
    kr = host_processors(mypriv,         // host_t host,
                         &processorPorts, // processor_port_array_t *out_processor_ports,
                         &procCount);     // mach_msg_type_number_t *out_processorCnt
                        
    if (kr) { 
        printf (”host_processors: %d\n”, kr); 
        exit(2);
    }
    printf(”Got %d processors . kr %d\n”, procCount, kr);
    for (proc = 0 ; proc <procCount; proc++) { 
        printf(”Processor %d\n”, processorPorts[proc]);
        // You really want to leave proc 0 active!
        if (proc > 0) { 
            if (kr != KERN_SUCCESS) 
                printf (”Unable to stop %d\n”, proc);
        }
}