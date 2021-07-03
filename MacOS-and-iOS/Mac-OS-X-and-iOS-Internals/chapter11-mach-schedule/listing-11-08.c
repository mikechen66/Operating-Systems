// Listing 11-8 kernel_thread_create and its use of continuations

kern_return_t kernel_thread_create(
    thread_continue_t       continuation,
    void                   *parameter,
    integer_t               priority,
    thread_t               *new_thread)
{
    kern_return_t           result;
    thread_t                thread;
    task_t                  task = kernel_task;
// thread_create_internal sets the thread.continuation
    result = thread_create_internal
             (task, priority, continuation, TH_OPTION_NONE, &thread);
    if (result != KERN_SUCCESS)
        return (result);
    task_unlock(task);
    lck_mtx_unlock(&tasks_threads_lock);
    stack_alloc(thread);
    assert(thread->kernel_stack != 0);
#if CONFIG_EMBEDDED
    if (priority > BASEPRI_KERNEL) // Set kernel stack for high priority threads
#endif
    thread->reserved_stack = thread->kernel_stack;
    // and the parameter is set manually here
    thread->parameter = parameter;
    if(debug_task & 1)
        kprintf("kernel_thread_create: thread = %p continuation = %p\n", thread, continuation);
        *new_thread = thread;
        return (result);
}
// ...
kern_return_t kernel_thread_start_priority(
    thread_continue_t       continuation,
    void                   *parameter,
    integer_t               priority,
    thread_t               *new_thread)
{
    kern_return_t   result;
    thread_t        thread;
    result = kernel_thread_create(continuation, parameter, priority, &thread);
    if (result != KERN_SUCCESS)
        return (result);
    *new_thread = thread;   
    thread_mtx_lock(thread);
    thread_start_internal(thread);
    thread_mtx_unlock(thread);
    return (result);
}