// Listing 15-5: The vfs_fsentry structure, as defined in bsd/sys/mount.h

struct vfs_fsentry {
    struct vfsops *vfe_vfsops;     /* vfs operations */
    int            vfe_vopcnt;     
    /* # of vnodeopv_desc being registered (reg, spec, fifo...)*/
    vnodeopv_desc **vfe_opvdescs;  /* null terminated;  */
    int            vfe_fstypenum;  /* historic file system type number */
    char           vfe_fsname[MFSNAMELEN]; /* file system type name */
    uint32_t       vfe_flags;      /* defines the FS capabilities */
    void *         vfe_reserv[2];  /* reserved for future use; set this to zero*/
 };