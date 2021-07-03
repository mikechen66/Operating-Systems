// Listing 10-9: The source of a hostinfo(1) like utility.c

#include <mach/mach.h>
#include <stdio.h>

// A quick & dirty hostinfo(1) like utility
int main(int argc, char **argv) {
    mach_port_t     self = host_self();
    kern_return_t   rc;
    char            buf[1024]; // suffices. Better code would sizeof(..info)
    host_basic_info_t hi;
    int len = 1024;
    // Getting the host info is simply a matter of calling host_info
    // on the host_self(). We do not need the privileged host port for
    // this..
    rc = host_info (self,              // host_t host,
                    HOST_BASIC_INFO,   // host_flavor_t flavor,
                    (host_info_t) buf, // host_info_t host_info_out,
                     &len); // mach_msg_type_number_t *host_info_outCnt
    if (rc != 0) { 
        fprintf(stderr,”Nope\n”); return(1);
    }
    hi = (host_basic_info_t) buf; // type cast, so we can print fields
    // And print fields..
    printf("CPUs:\t\t %d/%d\n",  hi->avail_cpus, hi->max_cpus);
    printf("Physical CPUs:\t %d/%d\n",  hi->physical_cpu, hi->physical_cpu_max);
    printf("Logical CPUs:\t %d/%d\n",   hi->logical_cpu,  hi->logical_cpu_max);
    printf("CPU type:\t %d/%d, Threadtype: %d\n", hi->cpu_type,
           hi->cpu_subtype, hi->cpu_threadtype);
    // Note memory_size is a signed 32-bit! Max value is 2GB, then it flips to negative
    printf("Memory size:\t %d/%ld\n", hi->memory_size, hi->max_mem);
    return(0);
}