// Listing 16-4: Finder Information, from bsd/hfs/hfs_format.h

/* Finder information */
struct FndrFileInfo {
        u_int32_t       fdType;         /* file type */
        u_int32_t       fdCreator;      /* file creator */
        u_int16_t       fdFlags;        /* Finder flags */
        struct {
            int16_t     v;              /* file's location */
            int16_t     h;
        } fdLocation;
        int16_t         opaque;
} __attribute__((aligned(2), packed));
typedef struct FndrFileInfo FndrFileInfo;
struct FndrDirInfo {
        struct {                        /* folder's window rectangle */
            int16_t     top;
            int16_t     left;
            int16_t     bottom;
            int16_t     right;
        } frRect;
        unsigned short  frFlags;        /* Finder flags */
        struct {
            u_int16_t   v;              /* folder's location */
            u_int16_t   h;
        } frLocation;
        int16_t         opaque;
} __attribute__((aligned(2), packed));
typedef struct FndrDirInfo FndrDirInfo;