// Listing 12-21: Using vm_statistics64 in vm_stat (from system_cmds-541/vm_stat.tproj/vm_stat.c)

void get_stats(vm_statistics64_t stat) {
    unsigned int count = HOST_VM_INFO64_COUNT;
    kern_return_t ret;
    if ((ret = host_statistics64(mach_host_self(), 
                                 HOST_VM_INFO64,
                                 (host_info64_t) stat,
                                 &count) != KERN_SUCCESS)) {
        fprintf(stderr, “%s: failed to get statistics. Error %d\n”, pgname,ret);
        exit(EXIT_FAILURE);
    }
}