// Listing 8-16: Machine dependent calls, from osfmk/i386/machdep_call.c

machdep_call_t machdep_call_table[] = {
    MACHDEP_CALL_ROUTINE(kern_invalid,0),
    MACHDEP_CALL_ROUTINE(kern_invalid,0),
    MACHDEP_CALL_ROUTINE(kern_invalid,0),
    MACHDEP_CALL_ROUTINE(thread_fast_set_cthread_self,1),
    MACHDEP_CALL_ROUTINE(thread_set_user_ldt,3),
    MACHDEP_BSD_CALL_ROUTINE(i386_set_ldt,3),
    MACHDEP_BSD_CALL_ROUTINE(i386_get_ldt,3),
};
machdep_call_t machdep_call_table64[] = {
    MACHDEP_CALL_ROUTINE(kern_invalid,0),
    MACHDEP_CALL_ROUTINE(kern_invalid,0),
    MACHDEP_CALL_ROUTINE(kern_invalid,0),
    MACHDEP_CALL_ROUTINE64(thread_fast_set_cthread_self64,1),
    MACHDEP_CALL_ROUTINE(kern_invalid,0),
    MACHDEP_CALL_ROUTINE(kern_invalid,0),
    MACHDEP_CALL_ROUTINE(kern_invalid,0),
};