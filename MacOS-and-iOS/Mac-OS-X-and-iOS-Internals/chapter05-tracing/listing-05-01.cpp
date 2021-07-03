// Listing 5-1: A D script to trace system calls — all the way into kernel space

#pragma D option flowindent /* Auto-indent probe calls */
syscall::open:entry
{
    self->tracing = 1;    /* From now on, everything is traced */
    printf(”file at: %x  opened with mode %x”, arg0, arg1);
}
fbt:::entry
/self->tracing/
{
    printf(”%x %x %x”, arg0, arg1,arg2);  /* Dump arguments */
}
fbt::open:entry
/self->tracing/
{
    printf (”PID %d (%s) is opening \n”  ,  
       ((proc_t)arg0)->p_pid , ((proc_t)arg0)->p_comm);
}
fbt:::return
/self->tracing/
{
    printf (”Returned %x\n”, arg1);
}
syscall::open:return
/self->tracing/
{
    self->tracing = 0;   /* Undo tracing */
    exit(0);             /* finish script */
}



/*
Output 5-4: Running the example from Listing 5-1
CPU FUNCTION                                 
  3  => open                                  file at: 10f80bdf0  openeed with mode 4
  3    -> open                                PId 69 (mds) is opening 
  3     | open:entry                          ffffff801561aa80 ffffff80158ac6d4
                                              ffffff801837a608
  3      -> __pthread_testcancel              1 ffffff80158ac6d4 ffffff801837a608
  3      <- __pthread_testcancel              Returned ffffff801837a5c0
  3      -> vfs_context_current               ffffff8015fe0ec0 ffffff80158ac6d4 0
  3      <- vfs_context_current               Returned ffffff801837a718
  3      -> vfs_context_proc                  ffffff801837a718 ffffff80158ac6d4 0
  3        -> get_bsdthreadtask_info          ffffff8015fe0ec0 ffffff80158ac6d4 0
  3        <- get_bsdthreadtask_info          Returned ffffff801561aa80
  3      <- vfs_context_proc                  Returned ffffff801561aa80
...
   (output truncated for brevity)
... 
  3      -> proc_list_unlock                  ffffff8013ed5970 10 ffffff8013ed5970
  3      <- proc_list_unlock                  Returned ffffff80008d91b0
  3      -> lck_mtx_unlock                    ffffff8013ed5970 10 ffffff8013ed5970
  3      <- lck_mtx_unlock                    Returned 1f0000
  3    <- open
 */