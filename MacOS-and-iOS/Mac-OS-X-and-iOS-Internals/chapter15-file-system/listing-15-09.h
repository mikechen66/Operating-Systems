// Listing 15-9: VNOP_LOOKUP (lookup a vnode in a directory), from bsd/sys/vnode_if.h

__BEGIN_DECLS
struct vnop_lookup_args {
        struct vnodeop_desc *a_desc;
        vnode_t a_dvp;
        vnode_t *a_vpp;
        struct componentname *a_cnp;        
        vfs_context_t a_context;
};
/*!
 @function VNOP_LOOKUP
 @abstract Call down to a file system to look for a directory entry by name.
 @discussion VNOP_LOOKUP is the key pathway through which VFS asks a 
   file system to find a file.  The vnode should be returned with an iocount 
   to be dropped by the caller.  A VNOP_LOOKUP() calldown can come without
   preceding VNOP_OPEN().
 @param dvp Directory in which to look up file.
 @param vpp Destination for found vnode.
 @param cnp Structure describing filename to find, reason for lookup, 
   and various other data.
 @param ctx Context against which to authenticate lookup request.
 @return 0 for success or a file system-specific error.
 */
#ifdef XNU_KERNEL_PRIVATE
extern errno_t VNOP_LOOKUP(vnode_t, vnode_t *, struct componentname *, vfs_context_t);
#endif /* XNU_KERNEL_PRIVATE */