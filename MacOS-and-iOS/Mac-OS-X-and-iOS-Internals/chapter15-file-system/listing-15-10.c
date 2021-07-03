// Listing 15-10: VNode operations

// in bsd/vfs/vfs_vnops.
struct fileops vnops =
    { vn_read, vn_write, vn_ioctl, vn_select, vn_closefile, vn_kqfilt_add, NULL };