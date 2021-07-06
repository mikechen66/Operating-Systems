/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter Z */

#include <sys/wait.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        usageErr("%s num-children [parent-sleep-secs [child-sleep-secs]]\n",
                argv[0]);
    }

    int numChildren = atoi(argv[1]);
    int parentSleepTime = (argc > 2) ? atoi(argv[2]) : 0;
    int childSleepTime = (argc > 3) ? atoi(argv[3]) : 300;

    printf("Parent PID = %ld\n", (long) getpid());

    /* If a parent sleep time was specified, show the user the parent's
       PID in case they want to write it to a cgroup.procs file */

    if (parentSleepTime > 0) {
        printf("Parent sleeping for %d seconds\n", parentSleepTime);
        sleep(parentSleepTime);
    }

    printf("Creating %d children that will sleep %d seconds\n",
            numChildren, childSleepTime);

    int failed = 0;
    for (int j = 1; j <= numChildren && !failed; j++) {
        pid_t childPid = fork();
        switch (childPid) {
        case -1:
            errMsg("fork");
            failed = 1;
            break;
        case 0:
            sleep(childSleepTime);
            exit(EXIT_SUCCESS);
        default:
            printf("Child %d: PID = %ld\n", j, (long) childPid);
            break;
        }
    }

    printf("Waiting for all children to terminate\n");

    while (waitpid(-1, NULL, 0) > 0)
        continue;

    printf("All children terminated; bye!\n");

    exit(EXIT_SUCCESS);
}
