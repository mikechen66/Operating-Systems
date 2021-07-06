/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter 39 */

#include <sys/capability.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Fetch and display process capabilities */

    cap_t caps = cap_get_pid(atoi(argv[1]));
    if (caps == NULL)
        errExit("cap_get_pid");

    char *str = cap_to_text(caps, NULL);
    if (str == NULL)
        errExit("cap_to_text");

    printf("Capabilities: %s\n", str);

    cap_free(caps);
    cap_free(str);

    exit(EXIT_SUCCESS);
}
