// Listing 10-16: Using processor_info()

#include <stdio.h>           // fprintf, stderr, and friends
#include <mach/mach.h>       // Generic Mach stuff, like kern_return_t
#include <mach/processor.h>  // For the processor_* APIs
#include <mach-o/arch.h>     // For NXArch

int main(void) {
    kern_return_t    kr;
    host_name_port_t host = mach_host_self();
    host_priv_t      host_priv;
    processor_port_array_t processors;
    natural_t              count, infoCount;
    processor_basic_info_data_t basicInfo;
    int                     p;
    // First, get the privileged port – otherwise we can't query the processors

    kr = host_get_host_priv_port(host, &host_priv); 
    if (kr != KERN_SUCCESS) { 
        fprintf(stderr, “host_get_host_priv_port %d (you should be root)”, kr);
        exit(1); 
    }
    // If we're here, we can try to get the process array
    kr = host_processors (host_priv, &processors, &count);
    if (kr != KERN_SUCCESS) { 
        fprintf(stderr, “host_processors %d”, kr); 
        exit(1); 
    }
    // And if we got this far, we have it! Iterate, then:
    for (p = 0; p < count; p++) {
        // infoCount is in/out, so we have to reset it on each iteration
        infoCount = PROCESSOR_BASIC_INFO_COUNT;
        // Ask for BASIC_INFO. It is left to the reader as an exercise
        // to implement CPU_LOAD_INFO
        kr = processor_info (processors[p],        // the processor_t
                             PROCESSOR_BASIC_INFO, // Information requested
                             &host,                // The host
                             (processor_info_t) &basicInfo, // Information returned here
                             &infoCount);          // Sizeof(basicInfo) (in/out)
  
        if (kr != KERN_SUCCESS) {
            fprintf(stderr, “?!\n”); 
            exit(3);
        }
        // Dump to screen. We use NX APIs to resolve the cpu type and subtype
        printf(”%s processor %s in slot %d\n”,
               (basicInfo.is_master ? “Master” : “Slave”),
               NXGetArchInfoFromCpuType(basicInfo.cpu_type,
                                        basicInfo.cpu_subtype)->description,
                                        basicInfo.slot_num);
    }
}