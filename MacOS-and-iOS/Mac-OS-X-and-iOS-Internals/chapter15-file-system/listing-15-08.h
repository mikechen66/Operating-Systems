// Listing 15-8: The vnode object, from bsd/sys/vnode_internal.h

struct vnode {
        lck_mtx_t v_lock;                     /* vnode mutex */
        TAILQ_ENTRY(vnode) v_freelist;        /* vnode freelist */
        TAILQ_ENTRY(vnode) v_mntvnodes;       /* vnodes for mount point */
        LIST_HEAD(, namecache) v_nclinks;     // names (hard links) of vnode
        LIST_HEAD(, namecache) v_ncchildren;  // cache of named children
        uint32_t v_listflag;                  // flags,(protected by list_lock) 
        uint32_t v_flag;                      // flags (unprotected)
        uint16_t v_lflag;                     // and more flags (local flags)
        uint8_t  v_iterblkflags;              /* buf iterator flags */
        uint8_t  v_references;                // reference of io_count 
        int32_t  v_kusecount;                 /* count of in-kernel refs */
        int32_t  v_usecount;                  /* reference count of users */
        int32_t  v_iocount;                   /* iocounters */
        void *   v_owner;                     /* act that owns the vnode */
        uint16_t v_type;                      /* vnode type */
        uint16_t v_tag;                       /* type of underlying data */
        uint32_t v_id;                        /* identity of vnode contents */
        union {
                struct mount    *vu_mountedhere;/* ptr to mounted vfs (VDIR) */
                struct socket   *vu_socket;     /* unix ipc (VSOCK) */
                struct specinfo *vu_specinfo;   /* device (VCHR, VBLK) */
                struct fifoinfo *vu_fifoinfo;   /* fifo (VFIFO) */
                struct ubc_info *vu_ubcinfo;    /* valid for (VREG) */
        } v_un;
        struct  buflists v_cleanblkhd;          /* clean blocklist head */
        struct  buflists v_dirtyblkhd;          /* dirty blocklist head */
        struct klist v_knotes;                  // knotes attached to vnode 
        /*
         * the following 4 fields are protected
         * by the name_cache_lock held in
         * excluive mode
         */
        kauth_cred_t    v_cred;               /* last authorized credential */
        kauth_action_t  v_authorized_actions; // current authorized actions */
        int             v_cred_timestamp;     //
        int             v_nc_generation;      //
        /*
         * back to the vnode lock for protection
         */
        int32_t         v_numoutput;       /* num of writes in progress */
        int32_t         v_writecount;      /* reference count of writers */
        const char *v_name;                /* name component of the vnode */
        vnode_t v_parent;                  /* pointer to parent vnode */
        struct lockf    *v_lockf;          /* advisory lock list head */
#ifndef __LP64__
        struct unsafe_fsnode *v_unsafefs;  /* pointer to struct used to lock */
#else 
        int32_t         v_reserved1;
        int32_t         v_reserved2;
#endif /* __LP64__ */
        int     (**v_op)(void *);          /* vnode operations vector */
        mount_t v_mount;                   /* ptr to vfs we are in */
        void *  v_data;                    /* private data for fs */
#if CONFIG_MACF 
        struct label *v_label;             /* MAC security label */
#endif
#if CONFIG_TRIGGERS
        vnode_resolve_t v_resolve; /* trigger vnode resolve info (VDIR only) */
#endif /* CONFIG_TRIGGERS */
};