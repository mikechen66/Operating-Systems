/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter 23 */

#define _GNU_SOURCE
#include <sys/syscall.h>
#include <sched.h>
#include <sys/times.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include "tlpi_hdr.h"

#if !defined(__GLIBC__) || __GLIBC_MINOR__ < 30

/* glibc 2.30 has a gettid() wrapper */

static pid_t
gettid(void)
{
    return syscall(SYS_gettid);
}
#endif

#define NANO 1000000000

static void *
threadFunc(void *arg)
{
    float period;       /* Interval (in CPU seconds) for displaying statistics
                           on consumed CPU time */
    char *sarg = arg;
    sscanf(sarg, "%f", &period);

    struct timespec prev_rt;
    if (clock_gettime(CLOCK_REALTIME, &prev_rt) == -1)
        errExit("clock_gettime");

    long long nloops = 0;
    int prev_step = 0;  /* Number of intervals of consumed CPU time calculated
                           in previous loop iteration */
    while (1) {

        /* Burn some user-mode CPU time */

        int j, k;
        for (j = 0, k = 0; j < 1000; j++)
            k = j;
        if (k >= 0)     /* Use k, to prevent gcc moaning about unused var */
            k++;

        nloops++;

        struct timespec curr_cpu;
        if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &curr_cpu) == -1)
            errExit("clock_gettime");

        /* Calculate current number of intervals of consumed CPU time */

        int curr_step = curr_cpu.tv_sec / period +
                        curr_cpu.tv_nsec / period / NANO;

        struct timespec curr_rt;
        if (clock_gettime(CLOCK_REALTIME, &curr_rt) == -1)
            errExit("clock_gettime");

        /* Calculate elapsed real microseconds for current CPU interval */

        int elapsed_rt_us = (curr_rt.tv_sec - prev_rt.tv_sec) * 1000000 +
                     (curr_rt.tv_nsec - prev_rt.tv_nsec) / 1000;

        if (curr_step > prev_step) {
            printf("[%ld]  CPU: %.3f; elapsed/cpu = %0.3f; %%CPU = %.3f "
                    "(nloops/sec = %lld)\n",
                    (long) gettid(),
                    (float) curr_step * period,
                    elapsed_rt_us / 1000000.0 / period,
                    period / (elapsed_rt_us / 1000000.0) * 100.0,
                    nloops * 1000000 / elapsed_rt_us);
            prev_step = curr_step;
            prev_rt = curr_rt;
            nloops = 0;
        }
    }

    return NULL;
}

int
main(int argc, char *argv[])
{
    pthread_t thr;
    int j, s;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s [period]...\n"
                "Creates one thread per argument that reports "
                "CPU time each 'period' CPU seconds\n"
                "'period' can be a floating-point number\n", argv[0]);

    /* Create one thread per command-line argument */

    for (j = 1; j < argc; j++) {
        s = pthread_create(&thr, NULL, threadFunc, argv[j]);
        if (s != 0)
            errExitEN(s, "pthread_create");
    }

    pause();

    exit(EXIT_SUCCESS);
}
