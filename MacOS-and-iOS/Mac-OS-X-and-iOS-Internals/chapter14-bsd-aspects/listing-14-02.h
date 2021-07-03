// Listing 14-2: BSD kmzones defined in bsd/sys/malloc.h

/*
 * Types of memory to be allocated (not all are used by us)
 */
#define M_FREE          0       /* should be on free list */
#define M_MBUF          1       /* mbuf */
#define M_DEVBUF        2       /* device driver memory */
#define M_SOCKET        3       /* socket structure */
#define M_PCB           4       /* protocol control block */
#define M_RTABLE        5       /* routing tables */
#define M_HTABLE        6       /* IMP host tables */
#define M_FTABLE        7       /* fragment reassembly header */
#define M_ZOMBIE        8       /* zombie proc status */
#define M_IFADDR        9       /* interface address */
#define M_SOOPTS        10      /* socket options */
#define M_SONAME        11      /* socket name */
#define M_NAMEI         12      /* namei path name buffer */
#define M_GPROF         13      /* kernel profiling buffer */
#define M_IOCTLOPS      14      /* ioctl data buffer */
#define M_MAPMEM        15      /* mapped memory descriptors */
#define M_CRED          16      /* credentials */
#define M_PGRP          17      /* process group header */
#define M_SESSION       18      /* session header */
#define M_IOV32         19      /* large iov's for 32 bit process */
#define M_MOUNT         20      /* vfs mount struct */
#define M_FHANDLE       21      /* network file handle */
#define M_NFSREQ        22      /* NFS request header */
#define M_NFSMNT        23      /* NFS mount structure */
#define M_NFSNODE       24      /* NFS vnode private part */
#define M_VNODE         25      /* Dynamically allocated vnodes */
#define M_CACHE         26      /* Dynamically allocated cache entries */
#define M_DQUOT         27      /* UFS quota entries */
#define M_UFSMNT        28      /* UFS mount structure */
#define M_SHM           29      /* SVID compatible shared memory segments */
#define M_PLIMIT        30      /* plimit  structures */
#define M_SIGACTS       31      /* sigacts structures */
#define M_VMOBJ         32      /* VM object structure */
#define M_VMOBJHASH     33      /* VM object hash structure */
#define M_VMPMAP        34      /* VM pmap */
#define M_VMPVENT       35      /* VM phys-virt mapping entry */
#define M_VMPAGER       36      /* XXX: VM pager struct */
#define M_VMPGDATA      37      /* XXX: VM pager private data */
#define M_FILEPROC      38      /* Open file structure */
#define M_FILEDESC      39      /* Open file descriptor table */
#define M_LOCKF         40      /* Byte-range locking structures */
#define M_PROC          41      /* Proc structures */
#define M_PSTATS        42      /* pstats  proc sub-structures */
#define M_SEGMENT       43      /* Segment for LFS */
#define M_LFSNODE       44      /* LFS vnode private part */
#define M_FFSNODE       45      /* FFS vnode private part */
#define M_MFSNODE       46      /* MFS vnode private part */
#define M_NQLEASE       47      /* XXX: Nqnfs lease */
#define M_NQMHOST       48      /* XXX: Nqnfs host address table */
#define M_NETADDR       49      /* Export host address structure */
#define M_NFSSVC        50      /* NFS server structure */
#define M_NFSUID        51      /* XXX: NFS uid mapping structure */
#define M_NFSD          52      /* NFS server daemon structure */
#define M_IPMOPTS       53      /* internet multicast options */
#define M_IPMADDR       54      /* internet multicast address */
#define M_IFMADDR       55      /* link-level multicast address */
#define M_MRTABLE       56      /* multicast routing tables */
#define M_ISOFSMNT      57      /* ISOFS mount structure */
#define M_ISOFSNODE     58      /* ISOFS vnode private part */
#define M_NFSRVDESC     59      /* NFS server socket descriptor */
#define M_NFSDIROFF     60      /* NFS directory offset data */
#define M_NFSBIGFH      61      /* NFS version 3 file handle */
#define M_MSDOSFSMNT    62      /* MSDOS FS mount structure */
#define M_MSDOSFSFAT    63      /* MSDOS FS fat table */
#define M_MSDOSFSNODE   64      /* MSDOS FS vnode private part */
#define M_TTYS          65      /* allocated tty structures */
#define M_EXEC          66      /* argument lists & other mem used by exec */
#define M_MISCFSMNT     67      /* miscfs mount structures */
#define M_MISCFSNODE    68      /* miscfs vnode private part */
#define M_ADOSFSMNT     69      /* adosfs mount structures */
#define M_ADOSFSNODE    70      /* adosfs vnode private part */
#define M_ANODE         71      /* adosfs anode structures and tables. */
#define M_BUFHDR        72      /* File buffer cache headers */
#define M_OFILETABL     73      /* Open file descriptor table */
#define M_MCLUST        74      /* mbuf cluster buffers */
#define M_HFSMNT        75      /* HFS mount structure */
#define M_HFSNODE       76      /* HFS catalog node */
#define M_HFSFORK       77      /* HFS file fork */
#define M_ZFSMNT        78      /* ZFS mount data */
#define M_ZFSNODE       79      /* ZFS inode */
#define M_TEMP          80      /* misc temporary data buffers */
#define M_SECA          81      /* security associations, key management */
#define M_DEVFS         82
#define M_IPFW          83      /* IP Forwarding/NAT */
#define M_UDFNODE       84      /* UDF inodes */
#define M_UDFMNT        85      /* UDF mount structures */
#define M_IP6NDP        86      /* IPv6 Neighbour Discovery*/
#define M_IP6OPT        87      /* IPv6 options management */
#define M_IP6MISC       88      /* IPv6 misc. memory */
#define M_TSEGQ         89      /* TCP segment queue entry, unused */
#define M_IGMP          90
#define M_JNL_JNL       91  /* Journaling: "struct journal" */
#define M_JNL_TR        92  /* Journaling: "struct transaction" */ 
#define M_SPECINFO      93      /* special file node */
#define M_KQUEUE        94      /* kqueue */
#define M_HFSDIRHINT    95      /* HFS directory hint */
#define M_CLRDAHEAD     96      /* storage for cluster read-ahead state */
#define M_CLWRBEHIND    97      /* storage for cluster write-behind state */
#define M_IOV64         98      /* large iov's for 64 bit process */
#define M_FILEGLOB      99      /* fileglobal */
#define M_KAUTH         100     /* kauth subsystem */
#define M_DUMMYNET      101     /* dummynet */
#ifndef __LP64__
#define M_UNSAFEFS      102     /* storage for vnode lock state for unsafe FS */
#endif /* __LP64__ */
#define M_MACPIPELABEL  103     /* MAC pipe labels */
#define M_MACTEMP       104     /* MAC framework */
#define M_SBUF          105     /* string buffers */
#define M_EXTATTR       106     /* extended attribute */
#define M_LCTX          107     /* process login context */
/* M_TRAFFIC_MGT 108 */
#if HFS_COMPRESSION
#define M_DECMPFS_CNODE 109     /* decmpfs cnode structures */
#endif /* HFS_COMPRESSION */
#define M_INMFILTER     110     /* IPv4 multicast PCB-layer source filter */
#define M_IPMSOURCE     111     /* IPv4 multicast IGMP-layer source filter */
#define M_IN6MFILTER    112     /* IPv6 multicast PCB-layer source filter */
#define M_IP6MOPTS      113     /* IPv6 multicast options */
#define M_IP6MSOURCE    114     /* IPv6 multicast MLD-layer source filter */
#define M_LAST          115     /* Must be last type + 1 */