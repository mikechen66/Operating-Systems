// Listing 13-6: "Image activators" for executable formats in bsd/kern/kern_exec.c

/*
 * Our image activator table; this is the table of the image types we are
 * capable of loading.  We list them in order of preference to ensure the
 * fastest image load speed.
 *
 * XXX hardcoded, for now; should use linker sets
 */

struct execsw {
        int (*ex_imgact)(struct image_params *);
        const char *ex_name;
} execsw[] = {
        { exec_mach_imgact,             “Mach-o Binary” },
        { exec_fat_imgact,              “Fat Binary” },
#ifdef IMGPF_POWERPC   /* Deprecated as of Leopard, unsupported in Lion */
        { exec_powerpc32_imgact,        “PowerPC binary” },
#endif  /* IMGPF_POWERPC */
        { exec_shell_imgact,            “Interpreter Script” },
        { NULL, NULL}
};