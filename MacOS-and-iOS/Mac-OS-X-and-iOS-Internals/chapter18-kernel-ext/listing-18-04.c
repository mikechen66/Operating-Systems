 // Listing 18-4: Automatically generated info for kexts

#include <mach/mach_types.h>

extern kern_return_t _start(kmod_info_t *ki, void *data);
extern kern_return_t _stop(kmod_info_t *ki, void *data);
__private_extern__ kern_return_t sampleKext_start(kmod_info_t *ki, void *data);
__private_extern__ kern_return_t sampleKext_stop(kmod_info_t *ki, void *data);

__attribute__((visibility("default"))) 
   KMOD_EXPLICIT_DECL(com.technologeeks.osx.sampleKext, “1.0.0d1", _start, _stop)
__private_extern__ kmod_start_func_t *_realmain = sampleKext_start;
__private_extern__ kmod_stop_func_t *_antimain = sampleKext_stop;
__private_extern__ int _kext_apple_cc = __APPLE_CC__ ;