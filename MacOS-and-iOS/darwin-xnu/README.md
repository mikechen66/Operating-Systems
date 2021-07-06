
XNU

XNU is the computer operating system (OS) kernel developed at Apple Inc. since December 1996 for use in the Mac OS X (now macOS) operating system and released as free and open-source software as part of the Darwin OS, which is the basis for the Apple TV Software, iOS, iPadOS, watchOS, and tvOS OSes. XNU is an abbreviation of X is Not Unix. Please have a look at the repository as follows. 

https://github.com/apple/darwin-xnu

Originally developed by NeXT for the NeXTSTEP operating system, XNU was a hybrid kernel derived from version 2.5 of the Mach kernel developed at Carnegie Mellon University, itself a descendant of 4.3BSD and incorporating the bulk of the 4.3BSD kernel, with and an application programming interface (API) in Objective-C for writing drivers named Driver Kit.

After Apple acquired NeXT, the kernel was updated with code derived from OSFMK 7.3 from OSF, the FreeBSD project, and the Driver Kit was replaced with a C++ API for writing drivers named I/O Kit.

Kernel

XNU is a hybrid kernel, containing features of both monolithic kernels and microkernels, attempting to make the best use of both technologies, such as the message passing ability of microkernels enabling greater modularity and larger portions of the OS to benefit from memory protection, and retaining the speed of monolithic kernels for some critical tasks. As of 2021, XNU runs on ARM64 and x86-64 processors, both one processor and symmetric multiprocessing (SMP) models. 

Mach

The basis of the XNU kernel is a heavily modified (hybrid) Open Software Foundation Mach kernel (OSFMK) 7.3. Due to the reason, it is able to run the core of an operating system as separated processes, which allows a great flexibility, but reduces performance. With macOS, the designers have attempted to streamline some tasks and then BSD functions were built into the core with Mach. The result is a heavily modified (hybrid) OSFMK 7.3 kernel, Apple licensed OSFMK 7.3, which is a microkernel from the OSF. OSFMK 7.3 includes applicable code from the University of Utah Mach 4 kernel and from the many Mach 3.0 variants forked from the original Carnegie Mellon University Mach 3.0 microkernel.

BSD

The BSD part of the kernel provides the POSIX API, the Unix process model atop Mach tasks, basic security policies, user and group ids, permissions, the network protocol stack (protocols), the virtual file system code, several local file systems such as Hierarchical File System (HFS, HFS+) and Apple File System (APFS), the Network File System (NFS) client and server, cryptographic framework, UNIX System V IPC, audit subsystem, mandatory access control, and some of the locking primitives. The BSD code present in XNU has been most recently synchronised with that from the FreeBSD kernel. Although much of it has been significantly modified, code sharing still occurs between Apple and the FreeBSD Project as of 2009.

For the building Dev kernal, please read the documents inside of the zipped file.
