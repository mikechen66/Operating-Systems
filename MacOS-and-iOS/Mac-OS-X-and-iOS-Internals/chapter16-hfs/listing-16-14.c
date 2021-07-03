// Listing 16-14: The Hot-File B-Tree key format

struct HotFileKey {
    u_int16_t       keyLength;      /* length of key, excluding this field */
    u_int8_t        forkType;       /* 0 = data fork, FF = resource fork */
    u_int8_t        pad;            /* make the other fields align on 32-bit boundary */
    u_int32_t       temperature;    /* temperature recorded  - set to HFC_LOOKUPTAG */
    u_int32_t       fileID;         /* file ID */
};