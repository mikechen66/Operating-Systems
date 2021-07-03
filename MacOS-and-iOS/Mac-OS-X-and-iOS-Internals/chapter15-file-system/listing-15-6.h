// Listing 15-6: vfs_fsadd and vfs_fsremove, as defined in bsd/sys/mount.h

// Add a File system to VFS — provide vfs_fsentry, get vfs_table_t  handle
int vfs_fsadd(_in_ struct vfs_fsentry *, _out_ vfstable_t *);
// Remove a File system from VFS, given the vfstable_t handle
int vfs_fsremove(_in_ vfstable_t);