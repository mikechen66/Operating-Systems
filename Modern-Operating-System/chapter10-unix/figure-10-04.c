
// Figure 10-4. Process creation in Linux.

pid = fork( );              /* if the fork succeeds, pid > 0 in the parent */ 
if (pid < 0) {
    handle error( );        /* fork failed (e.g., memory or some table is full) */ 
} else if (pid > 0) {
                            /* parent code goes here. */
} else { 
                           /* child code goes here. */
}

