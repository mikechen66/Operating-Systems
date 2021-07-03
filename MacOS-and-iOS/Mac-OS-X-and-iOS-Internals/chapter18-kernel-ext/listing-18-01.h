// Listing 18-1: The mkext header, from libkern/mkext.h

* Core Header
*
* All versions of mkext files have this basic header:
*
* - magic & signature - always ‘MKXT' and ‘MOSX' as defined above.
* - length - the length of the whole file
* - adler32 - checksum from &version to end of file
* - version - a ‘vers' style value
* - numkexts - how many kexts are in the archive (only needed in v.1)
* - cputype & cpusubtype - in version 1 could be CPU_TYPE_ANY
*     and CPU_SUBTYPE_MULTIPLE if the archive contained fat kexts;
*     version 2 does not allow this and all kexts must be of a single
*     arch. For either version, mkexts of specific arches can be
*     embedded in a fat Mach-O file to combine them.