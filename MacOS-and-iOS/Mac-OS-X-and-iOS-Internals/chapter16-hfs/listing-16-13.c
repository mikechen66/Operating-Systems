// Listing 16-13: The Hot-File B-Tree header

/* 
 * B-tree header node user info (on-disk).  // (hasn't changed from TN1150)
 */
struct HotFilesInfo {
    u_int32_t       magic;       // HFC_MAGIC, 0xFF28FF26
    u_int32_t       version;     // HFC_VERSION, 1
    u_int32_t       duration;    /* duration of sample period (secs) */
    u_int32_t       timebase;    /* start of recording period (GMT time in secs) */
    u_int32_t       timeleft;    /* time remaining in recording period (secs) */
    u_int32_t       threshold;
    u_int32_t       maxfileblks;
    u_int32_t       maxfilecnt;
    u_int8_t        tag[32];     // hfc_tag = "CLUSTERED HOT FILES B-TREE     "
};