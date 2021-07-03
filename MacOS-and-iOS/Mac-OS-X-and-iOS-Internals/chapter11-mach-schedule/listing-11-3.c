// Listing 11-3: The implementation of task_priority(), from osfmk/kern/task_policy.c

static void task_priority(
    task_t                  task,
    integer_t               priority,
    integer_t               max_priority)
{
    thread_t                thread;
    task->max_priority = max_priority;
    if (priority > task->max_priority)
            priority = task->max_priority;
    else
    if (priority < MINPRI)
            priority = MINPRI;
    task->priority = priority;
    queue_iterate(&task->threads, thread, thread_t, task_threads) {
            thread_mtx_lock(thread);
            if (thread->active)
                    thread_task_priority(thread, priority, max_priority);
            thread_mtx_unlock(thread);
    }
}