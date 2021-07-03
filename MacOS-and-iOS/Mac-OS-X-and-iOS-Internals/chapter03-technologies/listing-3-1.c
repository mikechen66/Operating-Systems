// Listing 3-1: Using kqueues and kevents to filter process events
void main (int argc, char **argv)
{
    pid_t pid;  // PID to monitor
    int kq;     // The kqueue file descriptor
    int rc;     // collecting return values
    int done;
    struct kevent ke;
    pid = atoi(argv[1]);
    kq = kqueue();
    if (kq == -1) { perror(”kqueue”); exit(2); }
    // Set process fork/exec notifications
    EV_SET(&ke, pid, EVFILT_PROC, EV_ADD,
       NOTE_EXIT | NOTE_FORK | NOTE_EXEC , 0, NULL);
    // Register event

    rc = kevent(kq, &ke, 1, NULL, 0, NULL);
    if (rc < 0) { perror (”kevent”); exit (3); }
    done = 0;
    
    while (!done) {
        memset(&ke, ‘\0', sizeof(struct kevent));
        // This blocks until an event matching the filter occurs           
        rc = kevent(kq, NULL, 0, &ke, 1, NULL);
        if (rc < 0) { perror (”kevent”); exit (4); }
       
        if (ke.fflags & NOTE_FORK)
            printf(”PID %d fork()ed\n”, ke.ident);
        if (ke.fflags & NOTE_EXEC)
            printf(”pid %d has exec()ed\n”, ke.ident);
        if (ke.fflags & NOTE_EXIT)
           {
             printf(”pid %d has exited\n”, ke.ident);
             done++;
           }
      } // end while 
}