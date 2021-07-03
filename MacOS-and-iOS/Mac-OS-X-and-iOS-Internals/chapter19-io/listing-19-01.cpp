// Listing 19-1: I/O Kit thread creation and exit APIs, from I/O Kit/Kernel/IOLib.cpp

IOThread IOCreateThread(IOThreadFunc fcn, void *arg) {
    kern_return_t   result;
    thread_t                thread;
    result = kernel_thread_start((thread_continue_t)fcn, arg, &thread);
    if (result != KERN_SUCCESS)
            return (NULL);
    thread_deallocate(thread);
    return (thread);
}
void IOExitThread(void) {
    (void) thread_terminate(current_thread());
}