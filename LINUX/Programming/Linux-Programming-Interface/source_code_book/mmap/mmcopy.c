/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Solution for Exercise 49-1 */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    if (argc != 3)
        usageErr("%s source-file dest-file\n", argv[0]);

    int fdSrc = open(argv[1], O_RDONLY);
    if (fdSrc == -1)
        errExit("open");

    /* Use fstat() to obtain size of file: we use this to specify the
       size of the two mappings */

    struct stat sb;
    if (fstat(fdSrc, &sb) == -1)
        errExit("fstat");

    /* Handle zero-length file specially, since specifying a size of
       zero to mmap() will fail with the error EINVAL */

    if (sb.st_size == 0)
        exit(EXIT_SUCCESS);

    char *src = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fdSrc, 0);
    if (src == MAP_FAILED)
        errExit("mmap");

    int fdDst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fdDst == -1)
        errExit("open");

    if (ftruncate(fdDst, sb.st_size) == -1)
        errExit("ftruncate");

    char *dst = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE,
                     MAP_SHARED, fdDst, 0);
    if (dst == MAP_FAILED)
        errExit("mmap");

    memcpy(dst, src, sb.st_size);       /* Copy bytes between mappings */

    if (msync(dst, sb.st_size, MS_SYNC) == -1)
        errExit("msync");

    exit(EXIT_SUCCESS);
}
