// Listing 16-5: Finder Flags, from bsd/hfs/hfs_macos_defs.h

enum {
    /* Finder Flags */
    kHasBeenInited          = 0x0100,
    kHasCustomIcon          = 0x0400,
    kIsStationery           = 0x0800,
    kNameLocked             = 0x1000,
    kHasBundle              = 0x2000,
    kIsInvisible            = 0x4000,
    kIsAlias                = 0x8000
};