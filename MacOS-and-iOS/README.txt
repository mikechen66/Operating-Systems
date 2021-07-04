macOS and iOS

## Overview

macOS is a proprietary graphical operating system developed and marketed by Apple Inc. since 2001. It is the primary operating system for Apple's Mac computers. macOS succeeded the classic Mac OS, a Macintosh operating system with nine releases from 1984 to 1999. During this time. The first desktop version, Mac OS X 10.0, was released in March 2001. Releases from Mac OS X 10.5 Leopard and thereafter are UNIX 03 certified. Apple's mobile operating system, iOS, has been considered a variant of macOS. Apple shortened the name to "OS X" in 2012 and then changed it to macOS in 2016 to align with the branding of iOS 14 with NPU based AI technologies. After 16 distinct versions of macOS 10, macOS Big Sur was presented as v11 in 2020, and macOS Monterey was presented as version 12 in 2021. Apple began the Apple silicon transition, using self-designed, 64-bit ARM-based Apple M1 processors on new Mac computers.

## XNU

The view of OS X and iOS Walks you through the phases of system startup--both Mac (EFi) and mobile (iBoot) Explains how processes, threads, virtual memory, and filesystems are maintained Covers the security architecture Reviews the internal Apis used by the system—BSD and Mach Dissects the kernel, XNU, into its sub components: Mach, the BSD Layer, and I/O kit, and explains each in detail Explains the inner workings of device drivers From architecture to implementation, this book is essential reading if you want to get serious about the internal workings of mac OS X and iOS.

## macOS

macOS originally was based on Unix-like NEXTSTEP (NeXT) with the Mach kernel compiance with BSD. At macOS's core is a POSIX-compliant operating system built on top of the XNU kernel, with standard Unix facilities available from the command line interface. Apple has released the family of software as a free and open source operating system named darwin/xnu. On top of the darwin/xnu with BSD/Mach, Apple layered a number of components, including Core OS for CPU/NPU/GPU, Core Services, Media and App Kit and Aqua Interface, the NPU-supported AI, and the support to  iOS and iPadOS apps based on the 64-bit ARM-based Apple M1(the Apple SoC). 


## iOS

iOS is really Mac OS X, but with some significant differences: The architecture for which the kernel and binaries are compiled is ARM-based, rather than Intel x86_64. The processors may be different (A4, A5,..., A14), but all are based on designs by ARM. The main advantage of ARM over Intel is in power management, which makes their processor designs attractive for mobile operating systems such as iOS, as well as its arch-nemesis, Android. The kernel sources remain closed — even though Apple promised to maintain XNU, the OS X Kernel, as open source, it apparently frees itself from that pledge for its mobile version. Occasionally, some of the iOS modifications leak into the publicly available sources (as can be seen by various #ifdef,__arm__, and ARM_ARCH conditionals), though these generally diminish in number with new kernel versions.





Resources:

http://newosxbook.com/index.php?page=book

https://developer.apple.com/videos/play/wwdc2020/10686/

https://en.wikipedia.org/wiki/Darwin_(operating_system)

https://en.wikipedia.org/wiki/XNU

https://en.wikipedia.org/wiki/MacOS

https://en.wikipedia.org/wiki/MacOS_Big_Sur

https://en.wikipedia.org/wiki/IOS

https://en.wikipedia.org/wiki/List_of_Apple_operating_systems

https://www.quora.com/What-is-the-difference-between-macOS-and-iOS

https://en.wikipedia.org/wiki/List_of_Apple_operating_systems

https://en.wikipedia.org/wiki/Apple_M1

https://www.macrumors.com/guide/apple-silicon/

https://zh.wikipedia.org/wiki/Apple_Silicon
