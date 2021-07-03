// Listing 18-5: kmod_get_info() falling through to kext_get_kmod_info for 32-bit clients

kern_return_t kmod_get_info(
    host_t host __unused,
    kmod_info_array_t * kmod_list KMOD_MIG_UNUSED,
    mach_msg_type_number_t * kmodCount KMOD_MIG_UNUSED)
{
#if __ppc__ || __i386__
    if (current_task() != kernel_task && task_has_64BitAddr(current_task())) {
            NOT_SUPPORTED_USER64();
        return KERN_NOT_SUPPORTED;
 }  return kext_get_kmod_info(kmod_list, kmodCount);
#else
    NOT_SUPPORTED_KERNEL();
    return KERN_NOT_SUPPORTED;
#endif /* __ppc__ || __i386__ */
}

// kext_get_kmod_info is defined in libkern/OSKextLib.cpp:
/*********************************************************************
* Compatibility implementation for kmod_get_info() host_priv routine.
* Only supported on old 32-bit architectures.
*********************************************************************/

#if __i386__
kern_return_t
kext_get_kmod_info(
    kmod_info_array_t      * kmod_list,
    mach_msg_type_number_t * kmodCount)
{
    return OSKext::getKmodInfo(kmod_list, kmodCount);
}
#endif /* __i386__ */