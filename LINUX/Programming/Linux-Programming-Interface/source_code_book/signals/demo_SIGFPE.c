/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter 22 */

#define _GNU_SOURCE     /* Get strsignal() declaration from <string.h> */
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include "tlpi_hdr.h"

static void
sigfpeCatcher(int sig)
{
    printf("Caught signal %d (%s)\n", sig, strsignal(sig));
                                /* UNSAFE (see Section 21.1.2) */
    sleep(1);                   /* Slow down execution of handler */
}

int
main(int argc, char *argv[])
{
    /* If no command-line arguments specified, catch SIGFPE, else ignore it */

    if (argc > 1 && strchr(argv[1], 'i') != NULL) {
        printf("Ignoring SIGFPE\n");
        if (signal(SIGFPE, SIG_IGN) == SIG_ERR)     errExit("signal");
    } else {
        printf("Catching SIGFPE\n");

        struct sigaction sa;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = sigfpeCatcher;
        if (sigaction(SIGFPE, &sa, NULL) == -1)
            errExit("sigaction");
    }

    bool blocking = argc > 1 && strchr(argv[1], 'b') != NULL;
    sigset_t prevMask;
    if (blocking) {
        printf("Blocking SIGFPE\n");

        sigset_t blockSet;
        sigemptyset(&blockSet);
        sigaddset(&blockSet, SIGFPE);
        if (sigprocmask(SIG_BLOCK, &blockSet, &prevMask) == -1)
            errExit("sigprocmask");
    }

    printf("About to generate SIGFPE\n");
    int x, y;
    y = 0;
    x = 1 / y;
    y = x;      /* Avoid complaints from "gcc -Wunused-but-set-variable" */

    if (blocking) {
        printf("Sleeping before unblocking\n");
        sleep(2);
        printf("Unblocking SIGFPE\n");
        if (sigprocmask(SIG_SETMASK, &prevMask, NULL) == -1)
            errExit("sigprocmask");
    }

    printf("Shouldn't get here!\n");
    exit(EXIT_FAILURE);
}
