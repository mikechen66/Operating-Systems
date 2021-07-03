// Listing 4-3: Listing all Mach-O Images in the process

#include <dlfcn.h>        // for dladdr(3)
#include <mach-o/dyld.h>  // for _dyld_ functions

void listImages (void) {
    // List all mach-o images in a process
    uint32_t i;
    uint32_t ic = _dyld_image_count();
    printf (”Got %d images\n”,ic);
    for (i = 0; i < ic; i++) {
        printf ("%d: %p\t%s\t(slide: %p)\n", 
                i, 
                _dyld_get_image_header(i), 
                _dyld_get_image_name(i),
                _dyld_get_image_slide(i));
    }
}

void add_callback(const struct mach_header* mh, intptr_t vmaddr_slide) {
    // Using callbacks from dyld, we can get the same functionality
    // of enumerating the images in a binary
    Dl_info info;
    // Should really check return value of dladdr here...
    dladdr(mh, &info);
    printf ("Callback invoked for image: %p %s (slide: %p)\n", 
            mh, info.dli_fname, vmaddr_slide);
}

void main (int argc, char **argv) {
    // Calling listImages will enumerate all Mach-O objects loaded into
    // our address space, using the _dyld functions from mach-o/dyld.h
    listImages();  
    // Alternatively, we can register a callback on add. This callback
    // will also be invoked for existing images at this point.
    _dyld_register_func_for_add_imag
}



/*
Output 4-7: Running the code from Listing 4-3
morpheus@Ergo (∼) morpheus$ ./lsimg 
Got 3 images
0: 0x100000000         /Users/morpheus/./lsimg       (slide: 0x0)
1: 0x7fff87869000      /usr/lib/libSystem.B.dylib    (slide: 0x0)
2: 0x7fff8a2cb000      /usr/lib/system/libmathCommon.A.dylib       (slide: 0x0)
Callback invoked for image: 0x100000000 /Users/morpheus/./lsimg (slide: 0x0)
Callback invoked for image: 0x7fff87869000 /usr/lib/libSystem.B.dylib (slide: 0x0)
Callback invoked for image: 0x7fff8a2cb000 /usr/lib/system/libmathCommon.A.dylib (slide:
0x0)
 */

/*
Output 4-8: Running the code from Listing 4-3 on iOS 5
root@Podicum (∼)# ./lsimg
Got 24 images
0: 0x1000       /private/var/root/./lsimg       (slide: 0x0)
1: 0x304c9000   /usr/lib/libgcc_s.1.dylib       (slide: 0x353000)
2: 0x3660f000   /usr/lib/libSystem.B.dylib      (slide: 0x353000)
3: 0x362c6000   /usr/lib/system/libcache.dylib  (slide: 0x353000)
4: 0x33e60000   /usr/lib/system/libcommonCrypto.dylib   (slide: 0x353000)
5: 0x34a79000   /usr/lib/system/libcompiler_rt.dylib    (slide: 0x353000)
6: 0x30698000   /usr/lib/system/libcopyfile.dylib       (slide: 0x353000)
7: 0x3718d000   /usr/lib/system/libdispatch.dylib       (slide: 0x353000)
8: 0x34132000   /usr/lib/system/libdnsinfo.dylib        (slide: 0x353000)
9: 0x3660d000   /usr/lib/system/libdyld.dylib   (slide: 0x353000)
10: 0x321a3000  /usr/lib/system/libkeymgr.dylib (slide: 0x353000)
11: 0x360b4000  /usr/lib/system/liblaunch.dylib (slide: 0x353000)
12: 0x3473b000  /usr/lib/system/libmacho.dylib  (slide: 0x353000)
13: 0x362f6000  /usr/lib/system/libnotify.dylib (slide: 0x353000)
14: 0x3377a000  /usr/lib/system/libremovefile.dylib     (slide: 0x353000)
15: 0x357c7000  /usr/lib/system/libsystem_blocks.dylib  (slide: 0x353000)
16: 0x36df7000  /usr/lib/system/libsystem_c.dylib       (slide: 0x353000)
17: 0x33ccc000  /usr/lib/system/libsystem_dnssd.dylib   (slide: 0x353000)
18: 0x32aa9000  /usr/lib/system/libsystem_info.dylib    (slide: 0x353000)
19: 0x32ac7000  /usr/lib/system/libsystem_kernel.dylib  (slide: 0x353000)
20: 0x3473f000  /usr/lib/system/libsystem_network.dylib (slide: 0x353000)
21: 0x34433000  /usr/lib/system/libsystem_sandbox.dylib (slide: 0x353000)
22: 0x339d9000  /usr/lib/system/libunwind.dylib (slide: 0x353000)
23: 0x32272000  /usr/lib/system/libxpc.dylib    (slide: 0x353000)
... (callback output is same, and is omitted for brevity) ...
 */