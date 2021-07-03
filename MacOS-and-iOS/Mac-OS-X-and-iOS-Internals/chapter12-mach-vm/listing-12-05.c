// Listing 12-5: A simple implementation of vmmap(1)

// Region listing code adapted from GDB's macosx_debug_regions, from open source GDB
void show_regions (task_t task, mach_vm_address_t address) {
    kern_return_t kr;
    vm_region_basic_info_data_t info, prev_info;
    mach_vm_address_t prev_address;
    mach_vm_size_t size, prev_size;
    mach_port_t object_name;
    mach_msg_type_number_t count;
    int nsubregions = 0;
    int num_printed = 0;
    int done = 0;
    count = VM_REGION_BASIC_INFO_COUNT_64;
    // Call mach_vm_region, which obtains the vm_map_entry containing the address,
    // and populates the vm_region_basic_info_data_t with its statistics
    kr = mach_vm_region (task, &address, &size, VM_REGION_BASIC_INFO,
                        (vm_region_info_t) &info, &count, &object_name);
    if (kr != KERN_SUCCESS) {
        printf (”Error %d - %s”, kr, mach_error_string(kr));
        return;
    }
    memcpy (&prev_info, &info, sizeof (vm_region_basic_info_data_t));
    prev_address = address;
    prev_size = size;
    nsubregions = 1;
    while (!done) {
        int print = 0;
        address = prev_address + prev_size;
        /* Check to see if address space has wrapped around. */
        if (address == 0) { 
            print = done = 1;
        }
        if (!done) {
            // Even on iOS, we use VM_REGION_BASIC_INFO_COUNT_64. This works.
            count = VM_REGION_BASIC_INFO_COUNT_64;
            kr = mach_vm_region (task, &address, &size, VM_REGION_BASIC_INFO,
                                (vm_region_info_t) &info, &count, &object_name);
            if (kr != KERN_SUCCESS) {
                fprintf (stderr,”mach_vm_region failed for address %p - error %d\n”,
                address, kr);
                size = 0;
                print = done = 1; // bail on error, but still print
            }
        }
        if (address != prev_address + prev_size)
             print = 1;
        // Print if there has been any change in region settings
        if ((info.protection != prev_info.protection)
                || (info.max_protection != prev_info.max_protection)
                || (info.inheritance != prev_info.inheritance)
                || (info.shared != prev_info.reserved)
                || (info.reserved != prev_info.reserved))
            print = 1;
        if (print) {
            int   print_size;
            char *print_size_unit;
            if (num_printed == 0)
                printf (”Region “);
            else
                printf (”   ... “);
            /* Quick hack to show size of segment, which GDB does not */
            print_size = prev_size;
            if (print_size > 1024) { 
                print_size /= 1024; print_size_unit = “K”; 
            }
            if (print_size > 1024) { 
                print_size /= 1024; print_size_unit = “M”; 
            }
            if (print_size > 1024) { 
                print_size /= 1024; print_size_unit = “G”; 
            }
            /* End Quick hack */
            // the xxx_to_yyy functions merely change the flags/bits to a more readable
            // string representation. Their implementation is left as an exercise to
            // the reader
            printf (” %p-%p [%d%s](%s/%s; %s, %s, %s) %s”,
                    (prev_address),
                    (prev_address + prev_size),
                    print_size,
                    print_size_unit,
                    protection_bits_to_rwx (prev_info.protection),
                    protection_bits_to_rwx (prev_info.max_protection),
                    unparse_inheritance (prev_info.inheritance),
                    prev_info.shared ? “shared” : “private”,
                    prev_info.reserved ? “reserved” : “not-reserved”,
                    behavior_to_xxx (prev_info.behavior));
            if (nsubregions > 1)
                printf (” (%d sub-regions)”, nsubregions);
            printf (”\n”);
            prev_address = address;
            prev_size = size;
            memcpy (&prev_info, &info, sizeof (vm_region_basic_info_data_t));
            nsubregions = 1;
            num_printed++;
        }
        else {
            prev_size += size;
            nsubregions++;
        }
        if (done)
            break;
    }
} // end show_regions

void main(int argc, char **argv) {
    struct vm_region_basic_info vmr;
    kern_return_t   rc;
    mach_port_t     task;
    mach_vm_size_t  size = 8;
    vm_region_info_t        info = (vm_region_info_t) malloc(10000);
    mach_msg_type_number_t  info_count;
    mach_port_t             object_name;
    mach_vm_address_t       addr =1;
    int pid;
    if (!argv[1]) { 
        printf (”Usage: %s <PID>\n”); 
        exit (1);
    }
    pid = atoi(argv[1]);
    // Obtain task port, using task_for_pid().
    rc = task_for_pid(mach_task_self(),pid, &task);
    if (rc) { 
        fprintf (stderr, “task_for_pid() failed with error %d - %s (Am I entitled?)
        \n”, rc,
        mach_error_string(rc)); 
        exit(1); 
    }
    printf (”Task: %d\n”, task);
    show_regions (task, addr);
    printf(”Done\n”);
}