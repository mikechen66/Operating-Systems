// Listing 18-6: kextstat(8)-style output of struct kmod_info_t's. Compile with –arch i386.

#include <mach/mach.h>
#include <mach/mach_host.h>

// Quick kextstat(8) like utility - using the 32-bit APIs of kmod_get_info();
// Compile with -arch i386

void main() {
    mach_port_t            mach_host;
    kern_return_t          rc;
    mach_msg_type_number_t modulesCount = 0;
    kmod_args_t            modules;
    int                    i;
    kmod_info_t           *mod;
    mach_host = mach_host_self();
    rc = kmod_get_info(mach_host,
                       &modules,
                       &modulesCount);
    if (rc != KERN_SUCCESS) { 
        mach_error ("kmod_get_info",rc);
        exit(2);
    }
    printf("Got %d bytes - %d modules\n", modulesCount, modulesCount/sizeof(kmod_info_t));

    mod = (kmod_info_t *) modules;
    for (i = 0; i < modulesCount / sizeof(kmod_info_t); i++) {
        printf("%d\t", mod->id);
        printf("%s\t", mod->name);
        printf("%x\t", mod->address);
        printf("%x\n", mod->size);

        // break after kpi.bsd, which is also #1
        if (mod->id ==1) break;
        mod++; // increments by sizeof(kmod_info_t)
    }
}