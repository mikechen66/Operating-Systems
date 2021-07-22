
# POSIX with GNU C Library v2.33 - 2021

## GNU C Library 2.33

The GNU C Library version 2.33 is now available. The GNU C Library is used as the C library in the GNU system and
in GNU/Linux systems, as well as many other systems that use Linux as the kernel. The GNU C Library is primarily designed to be a portable and high performance C library.  It follows all relevant standards including ISO C11 and POSIX.1-2017.

## Changes for POSIX

On Linux, the posix_openpt and getpt functions no longer attempt to use legacy (BSD) pseudo-terminals and assume that if /dev/ptmx exists (and pseudo-terminals are supported), a devpts file system is mounted on /dev/pts.  Current systems already meet these requirements.


https://sourceware.org/pipermail/libc-alpha/2021-February/122207.html
