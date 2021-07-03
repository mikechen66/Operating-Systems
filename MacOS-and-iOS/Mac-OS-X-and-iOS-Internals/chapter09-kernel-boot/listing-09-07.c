// Listing 9-7: panic_dialog_test, from osfmk/console/panic_dialog.c

void panic_dialog_test( void ) {
    boolean_t o_panicDialogDrawn = panicDialogDrawn;
    boolean_t o_panicDialogDesired = panicDialogDesired;
    unsigned int o_logPanicDataToScreen = logPanicDataToScreen;
    unsigned long o_panic_caller = panic_caller;
    unsigned int o_panicDebugging = panicDebugging;
    panicDebugging = TRUE;
    panic_caller = (unsigned long)(char *)__builtin_return_address(0);
    logPanicDataToScreen = FALSE;
    panicDialogDesired = TRUE;
    panicDialogDrawn = FALSE;
    draw_panic_dialog();
    panicDebugging = o_panicDebugging;
    panic_caller = o_panic_caller;
    logPanicDataToScreen = o_logPanicDataToScreen;
    panicDialogDesired = o_panicDialogDesired;
    panicDialogDrawn = o_panicDialogDrawn;
}