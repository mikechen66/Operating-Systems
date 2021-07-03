// Listing 18-2: The skeleton code generated for a new kernel extension

#include <mach/mach_types.h>

kern_return_t SampleKext_start(kmod_info_t * ki, void *d);
kern_return_t SampleKext_stop(kmod_info_t *ki, void *d);
kern_return_t SampleKext_start(kmod_info_t * ki, void *d)
{
    return KERN_SUCCESS;
}
kern_return_t SampleKext_stop(kmod_info_t *ki, void *d)
{
    return KERN_SUCCESS;
}