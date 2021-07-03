// Listing 15-4: The LwVM header

#define MAX_PARTITIONS     12

struct LwVM_MBR {
    guid_t magic;             // One of two LwVM Magic “types”
    guid_t guid;              // 128-bit GUID for this device
    uint64_t mediaSize;       // Media size
    uint32_t numPartitions;   // Number of partitions defined (<= MAX_PARTITIONS)
    uint32_t crc32;           // CRC-32, if specified by a CRC-32 type.
    uint8_t padding[464];     // Padding to 512-byte block 
} ;

// First block is followed by up to MAX_PARTITIONS records (of which
// numPartitions are actually defined)
struct LwVMPartitionRecord {
    guid_t   magic;            // Magic of partition, as per GPT
    guid_t   guid;             // GUID of partition, generated per device
    uint64_t startSector;
    uint64_t endSector;
    uint64_t attributes;
    char partitionName[64];
} ;

// The two types defined in iOS 5.0 iPod4,1: (0x80887910, 0x80887920)
#define LWVM_MAGIC { 0x6A, 0x90, 0x88, 0xCF, 0x8A, 0xFD, 0x63, 0x0A, 0xE3, 0x51, 
0xE2, 0x48, 0x87, 0xE0, 0xB9, 0x8B } 

#define LWVM_NO_CRC_MAGIC { 0xB1, 0x89, 0xA5, 0x19, 0x4F, 0x59, 0x4B, 0x1D, 0xAD, 
0x44, 0x1E, 0x12, 0x7A, 0xAF, 0x45, 0x39 }