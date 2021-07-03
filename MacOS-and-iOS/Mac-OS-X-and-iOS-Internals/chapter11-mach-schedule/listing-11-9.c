// Listing 11-9: thread_block_reason() in osfmk/kern/sched_prim.c

/*
 * thread_block_reason:
 *
 * Forces a reschedule, blocking the caller if a wait
 * has been asserted.
 *
 * If a continuation is specified, then thread_invoke will
 * attempt to discard the thread's kernel stack.  When the
 * thread resumes, it will execute the continuation function
 * on a new kernel stack.
 */

thread_block_reason(thread_continue_t continuation, void *parameter, ast_t reason) {
    register thread_t     self = current_thread();
    register processor_t  processor;
    register thread_t     new_thread;
    spl_t s;
    counter(++c_thread_block_calls);
    s = splsched();
    if (!(reason & AST_PREEMPT))
        funnel_release_check(self, 2);
    processor = current_processor();
    /* If we're explicitly yielding, force a subsequent quantum */
    if (reason & AST_YIELD)
        processor->timeslice = 0;
    /* We're handling all scheduling AST's */
    ast_off(AST_SCHEDULING);
    // Save continuation and its relevant parameter, if any, on our own uthread
    self->continuation = continuation;
    self->parameter = parameter;
    // improbable kernel debug stuff omitted here
    do {
        thread_lock(self);
        new_thread = thread_select(self, processor);
        thread_unlock(self);
    } while (!thread_invoke(self, new_thread, reason)); // thread_invoke will switch context                                                    
    funnel_refunnel_check(self, 5);
    splx(s);
    return (self->wait_result);
}