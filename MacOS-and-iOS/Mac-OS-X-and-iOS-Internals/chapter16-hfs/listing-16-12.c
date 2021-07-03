// Listing 16-12: Attribute B-Tree data structures

/*
 * Atrributes B-tree Data Record
 *
 * For small attributes, whose entire value is stored
 * within a single B-tree record.
 */
struct HFSPlusAttrData {
        u_int32_t    recordType;   /* == kHFSPlusAttrInlineData */
        u_int32_t    reserved[2];
        u_int32_t    attrSize;     /* size of attribute data in bytes */
        u_int8_t     attrData[2];  /* variable length */
} __attribute__((aligned(2), packed));
typedef struct HFSPlusAttrData HFSPlusAttrData;
/*      A generic Attribute Record*/
union HFSPlusAttrRecord {
        u_int32_t               recordType;
        HFSPlusAttrInlineData   inlineData;   /* NOT USED */
        HFSPlusAttrData         attrData;
        HFSPlusAttrForkData     forkData;
        HFSPlusAttrExtents      overflowExtents;
};
typedef union HFSPlusAttrRecord HFSPlusAttrRecord;
/* Attribute key */
enum { kHFSMaxAttrNameLen = 127 };
struct HFSPlusAttrKey {
        u_int16_t     keyLength;       /* key length (in bytes) */
        u_int16_t     pad;             /* set to zero */
        u_int32_t     fileID;          /* file associated with attribute */
        u_int32_t     startBlock;      /* first allocation block number for extents */
        u_int16_t     attrNameLen;     /* number of unicode characters */
        u_int16_t     attrName[kHFSMaxAttrNameLen];   /* attribute name (Unicode) */
} __attribute__((aligned(2), packed));
typedef struct HFSPlusAttrKey HFSPlusAttrKey;