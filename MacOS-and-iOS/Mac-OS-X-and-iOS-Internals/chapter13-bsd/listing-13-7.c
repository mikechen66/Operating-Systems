// Listing 13-7: Image_params for execsw image activators

struct image_params {
    user_addr_t     ip_username_fname;          /* argument */
    user_addr_t     ip_user_argv;           /* argument */
    user_addr_t     ip_user_envv;           /* argument */
    int             ip_seg;                 /* segment for arguments */
    struct vnode    *ip_vp;                 /* file */
    struct vnode_attr       *ip_vattr;      /* run file attributes */
    struct vnode_attr       *ip_origvattr;  /* invocation file attributes */
    cpu_type_t      ip_origcputype;         /* cputype of invocation file */
    cpu_subtype_t   ip_origcpusubtype;      /* subtype of invocation file */
    char            *ip_vdata;              /* file data (up to one page) */
    int             ip_flags;               /* IMGPF_* bit flags specifying options */
    int             ip_argc;                /* argument count */
    int             ip_envc;                /* environment count */
    int             ip_applec;              /* apple vector count */
    char            *ip_startargv;          /* argument vector beginning */
    char            *ip_endargv;            /* end of argv/start of envv */
    char            *ip_endenvv;            /* end of envv/start of applev */
    char            *ip_strings;            /* base address for strings */
    char            *ip_strendp;         /* current end pointer */
    int             ip_argspace;         /* remaining space of NCARGS limit(argv+envv) */
    int             ip_strspace;         /* remaining total string space */
    // The following are used for fat binaries
    user_size_t     ip_arch_offset;         /* subfile offset in ip_vp */
    user_size_t     ip_arch_size;           /* subfile length in ip_vp */
    // The following two context;        /* VFS context */
        struct nameidata *ip_ndp;               /* are used for interpreters (!#)
    char            ip_interp_buffer[IMG_SHSIZE];   /* interpreter buffer space */
    int             ip_interp_sugid_fd;             /* fd for sugid script */
    /* Next two fields are for support of architecture translation... */
    char            *ip_p_comm;             /* optional alt p->p_comm */
        struct vfs_context      *ip_vfs_
    current nameidata */
        thread_t        ip_new_thread;          /* thread for spawn/vfork */
        struct label    *ip_execlabelp;         /* label of the executable */
        struct label    *ip_scriptlabelp;       /* label of the script */
        unsigned int    ip_csflags;             /* code signing flags */
        void            *ip_px_sa;
        void            *ip_px_sfa;
        void            *ip_px_spa;
};
