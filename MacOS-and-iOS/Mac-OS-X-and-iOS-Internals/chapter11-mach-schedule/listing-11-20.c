// Listing 11-20: Mach sample exception handling program, step 1

#include <mach/mach.h>
#include <mach/port.h>            // port rights
#include <mach/exception.h>
#include <mach/exception_types.h> // EXC_MASK_*
#include <mach/task.h>            // mach_task_self, etc
#include <stdio.h>                // fprintf..

mach_port_t      myExceptionPort; // Global, for reasons which will become clear later
void signalHandler (int SigNum) {
    printf("Got signal %d\n", SigNum);
    exit(1);
} // signalHandler
void causeSomeException(int WantUNIXSignals) {
    char *nullPtr = NULL;
    // If we want UNIX signals, also install a signal handler
    if (WantUNIXSignals) signal(11, signalHandler);
    // Null pointer dereference will result in SIGSEGV, 11.
    // You can try other exceptions (e.g. zero-divide), but
    // remember to change the signal number (e.g. SIGFPE, 8)
    nullPtr[0] = 1;
} // end causeSomeException
void catchMACHExceptions(mach_port_t  TargetTask) {
    // Simple code to catch exceptions occuring in TargetTask.
    // In step 1, code simply catches, and does nothing.
    kern_return_t  rc;

    exception_mask_t myExceptionMask;
    // create an exception port
    rc = mach_port_allocate (mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &myExceptionPort);

    if (rc != KERN_SUCCESS) { 
        fprintf (stderr, "Unable to allocate exception port\n"); 
        exit(1); 
    }
    // We next call port_insert_right to allow MAKE_SEND, which is required for
    // set_exception_ports
    rc = mach_port_insert_right(mach_task_self(),
                                myExceptionPort, // mach_port_name_t
                                myExceptionPort, // mach_port_poly_t
                                MACH_MSG_TYPE_MAKE_SEND);
    if (rc != KERN_SUCCESS) { 
        fprintf(stderr,"Unable to insert right\n"); 
        exit(2); 
    }

    myExceptionMask = EXC_MASK_ALL;
    // Now set this port as the target task's exception port
    rc = task_set_exception_ports(TargetTask,
                                  myExceptionMask,
                                  myExceptionPort,
                                  EXCEPTION_DEFAULT_IDENTITY, // Msg 2403
                                  MACHINE_THREAD_STATE);
    if (rc != KERN_SUCCESS) { 
        fprintf(stderr,"Unable to set exception\n"); 
        exit(3); 
    }
    // For now, do nothing.
} // end catchMACHExceptions

void main (int argc, char **argv) {
    int arg, wantUNIXSignals = 0, wantMACHExceptions = 0;
    for (arg = 1; arg < argc; arg++) {
        if (strcmp(argv[arg], “-m") == 0) wantMACHExceptions++;
        if (strcmp(argv[arg], “-u") == 0) wantUNIXSignals++;
    }
    // Example first starts capturing our own exceptions. Step 2 will soon
    // illustrate other tasks, so pass ourself as parameter for now
    if (wantMACHExceptions) catchMACHExceptions(mach_task_self());
    causeSomeException(wantUNIXSignals);
    fprintf(stderr,"Done\n"); // not reached
}