// Listing 15-7: A partial detail of the struct mount, from bsd/sys/mount_internal.h

struct mount {
        TAILQ_ENTRY(mount) mnt_list;            /* mount list */
        int32_t         mnt_count;              /* reference on the mount */
        lck_mtx_t       mnt_mlock;              // mutex protecting mount point
        struct vfsops   *mnt_op;                /* operations on fs */
        struct vfstable *mnt_vtable;            /* configuration info */
        struct vnode   *mnt_vnodecovered;       /* vnode we mounted on */
        struct vnodelst mnt_vnodelist;          /* list of vnodes this mount */
        struct vnodelst mnt_workerqueue;        /* list of vnodes this mount */
        struct vnodelst mnt_newvnodes;          /* list of vnodes this mount */
        uint32_t        mnt_flag;               /* flags */
        uint32_t        mnt_kern_flag;          /* kernel only flags */
        uint32_t        mnt_compound_ops;       // Available compound ops 
        uint32_t        mnt_lflag;              /* mount life cycle flags */
        uint32_t        mnt_maxsymlinklen;      /* max size of short symlink */
        struct vfsstatfs  mnt_vfsstat;          /* cache of file system stats */
        qaddr_t         mnt_data;               /* private data */
        /* Cached values of the IO constraints for the device */
        // ...
        // ...
#if CONFIG_TRIGGERS 
        // TRIGGERS is a compile time option which allows the setting of
        // callbacks on mount operations and specific vnodes
        int32_t         mnt_numtriggers;   /* num of trigger vnodes for this mount */
        vfs_trigger_callback_t *mnt_triggercallback;
        void            *mnt_triggerdata;
#endif
        /* XXX 3762912 hack to support HFS file system ‘owner' */
        uid_t           mnt_fsowner;
        gid_t           mnt_fsgroup;
        struct label    *mnt_mntlabel;          /* MAC mount label */
        struct label    *mnt_fslabel;           /* MAC default fs label */
       // Other various cached elements ..
}