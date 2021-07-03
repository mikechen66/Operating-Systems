// Listing 10-19: Displaying the tasks on the default processor set

void main(int argc, char **argv) {
  
    host_t                 myhost = mach_host_self();
    mach_port_t            psDefault;
    mach_port_t            psDefault_control;
    task_array_t           tasks; 
    mach_msg_type_number_t numTasks;
    int                    t;                  // a task index 

    kern_return_t kr;
    // Get default processor set
    kr = processor_set_default(myhost, &psDefault);
    // Request control port
    kr = host_processor_set_priv(myhost, psDefault, &psDefault_control); 
    if (kr != KERN_SUCCESS) { 
        fprintf(stderr, “host_processor_set_priv - %d”, kr); 
        exit(1); 
    }
    // Get tasks. Note this behaves a bit differently on iOS.
    // On OS X, you can also get the threads directly (processor_set_threads)
    kr = processor_set_tasks(psDefault_control, &tasks, &numTasks); 
    if (kr != KERN_SUCCESS) { 
        fprintf(stderr,”processor_set_tasks - %d\n”,kr); 
        exit(2); 
    }
    // Iterate through tasks. For now, just display the task ports and their PIDs
    // We use “pid_for_task” to map a task port to its BSD process identifier
    for (t = 0; t < numTasks; i++) {
        int pid;
        pid_for_task(tasks[t], &pid);
        printf(”Task: %d pid: %d\n”, tasks[i],pid);
    }
    // Stay tuned:
    // In the next chapter, this experiment will be expanded to list task
    // information, as well as the threads of each task
}