// Listing 14-10: mac_vnode_check_signature, from security/mac_vfs.h

int mac_vnode_check_signature(struct vnode *vp, unsigned char *sha1,
                              void * signature, size_t size)
{
    int error;
    // if either security.mac.vnode_enforce or security.mac.proc_enforce sysctls
    // are 0 (false), we just return 0 as well, never getting to the check.
    if (!mac_vnode_enforce || !mac_proc_enforce)
            return (0);
    
   // Otherwise, walk policy module list,execute mpo_vnode_check_signature for each
    MAC_CHECK(vnode_check_signature, vp, vp->v_label, sha1, signature, size);
    return (error);
}