// Listing 10-12: host_get_special_port(), as defined in osfmk/kern/host.c

host_get_special_port(
    host_priv_t     host_priv,
    __unused int    node,
    int             id,
    ipc_port_t      *portp)
{
    ipc_port_t      port;
    if (host_priv == HOST_PRIV_NULL ||
      id == HOST_SECURITY_PORT || id > HOST_MAX_SPECIAL_PORT || id < 0)
        return KERN_INVALID_ARGUMENT;
    host_lock(host_priv);
    port = realhost.special[id];
    *portp = ipc_port_copy_send(port);
    host_unlock(host_priv);
    return KERN_SUCCESS;
}