/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter 35 */

#define _GNU_SOURCE
#include <sched.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pid mask\n", argv[0]);

    pid_t pid = getInt(argv[1], GN_NONNEG, "pid");
    unsigned long mask = getLong(argv[2], GN_ANY_BASE, "octal-mask");

    cpu_set_t set;
    CPU_ZERO(&set);

    for (int cpu = 0; mask > 0; cpu++, mask >>= 1)
        if (mask & 1)
            CPU_SET(cpu, &set);

    if (sched_setaffinity(pid, sizeof(set), &set) == -1)
        errExit("sched_setaffinity");

    exit(EXIT_SUCCESS);
}
