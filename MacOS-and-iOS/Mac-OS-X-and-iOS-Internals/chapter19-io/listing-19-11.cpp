// Listing 19-11: The IOWorkloop implementation:
/* virtual */ void IOWorkLoop::threadMain()
{
restartThread:
    do {
        // Iterate through all work loop event sources. If we have none, bail.
        // runEventSources will also set “workToDo” to false, but the
        // IOWorkloop:signalWorkAvailable() may be called at any time and reset
        // it to true.
        if ( !runEventSources() )
            goto exitThread;
        IOInterruptState is = IOSimpleLockLockDisableInterrupt(workToDoLock);
        // If we get here and no more work (workToDo = FALSE), we check the
        // kLoopTerminate flag. If it is not set, we restart. Otherwise, we skip
        // this part and continue to exit.
        if ( !ISSETP(&fFlags, kLoopTerminate) && !workToDo) {
            assert_wait((void *) &workToDo, false);
            IOSimpleLockUnlockEnableInterrupt(workToDoLock, is);
            thread_continue_t cptr = NULL;
            // If possible, set threadMain as our own continuation and block
            // otherwise, leave continuation null and use “goto” for same effect
            if (!reserved || !(kPreciousStack & reserved->options))
                cptr = OSMemberFunctionCast(
                        thread_continue_t, this, &IOWorkLoop::threadMain);
            thread_block_parameter(cptr, this);
            goto restartThread;
            /* NOTREACHED */
        }
        // At this point we either have work to do or we need
        // to commit suicide.  But no matter
        // Clear the simple lock and retore the interrupt state
        IOSimpleLockUnlockEnableInterrupt(workToDoLock, is);
     } while(workToDo);
exitThread:
    // We get here if no sources, or no more work and loop flags had kLoopTerminate
    thread_t thread = workThread;
    workThread = 0;     // Say we don't have a loop and free ourselves
    free();
    thread_deallocate(thread);
    (void) thread_terminate(thread);
}