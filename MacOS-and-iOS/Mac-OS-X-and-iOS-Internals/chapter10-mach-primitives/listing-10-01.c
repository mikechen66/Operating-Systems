// Listing 10-1: A simple Mach port dumper

kern_return_t lsPorts(task_t TargetTask) {
    kern_return_t               kr;
    mach_port_name_array_t      portNames            = NULL;
    mach_msg_type_number_t      portNamesCount;
    mach_port_type_array_t      portRightTypes       = NULL;
    mach_msg_type_number_t      portRightTypesCount;
    mach_port_right_t           portRight;
    unsigned int                p;
    // Get all of task's ports
    kr = mach_port_names(TargetTask,
                        &portNames,
                        &portNamesCount,
                        &portRightTypes,
                        &portRightTypesCount);
    if (kr != KERN_SUCCESS) {
        fprintf (stderr,”Error getting mach_port_names.. %d\n”, kr);return (kr); 
    }
    // Ports will be dumped in hex, like GDB, which is somewhat limited. This can be
    // extended to recognize the well known global ports (left as an exercise for the
    // reader)
    for (p = 0; p < portNamesCount; p++) {
        printf( “0x%x 0x%x\n”,  portNames[p], portRightTypes[p]);
    } // end for
    // end lsPorts
}

int main(int argc, char * argv[]) {
    task_t              targetTask;
    kern_return_t       kr;
    int pid = atoi (argv[1]);
    // task_for_pid() is required to obtain a task port from a given
    // BSD PID. This is discussed in the next chapter
    kr  = task_for_pid(mach_task_self(),pid, &targetTask);
    lsPorts (targetTask);
    // Not strictly necessary, but be nice
    kr = mach_port_deallocate(mach_task_self(), targetTask);
}
