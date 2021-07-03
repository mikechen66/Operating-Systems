// Listing 6-1: The EFI system table
typedef struct { 
    EFI_TABLE_HEADER {   
        UINT64 Signature; // Constant 
        UINT32 Revision; 
        UINT32 HeaderSize; // Sizeof the entire table; 
        UINT32 CRC32;      // CRC-32 of table
        UINT32 Reserved;   // set to 0
    } Hdr;
    CHAR16 *FirmwareVendor;                    // For Apple EFI, "Apple"
    UINT32 FirmwareRevision;                     // Model dependent
    EFI_HANDLE ConsoleInHandle;                // stdin handle for binary
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;     // output operations
    EFI_HANDLE ConsoleOutHandle;               // stdout handle for binary 
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*ConOut;   // output operations
    EFI_HANDLE StandardErrorHandle;            // stderr handle for binary
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;   // output operations (q.v ConOut)
    EFI_RUNTIME_SERVICES *RuntimeServices        // Pointer to Runtime servers
    EFI_BOOT_SERVICES*BootServices            // Pointer to boot time services
    UINTN NumberOfTableEntries;                // entries in configuration table
    EFI_CONFIGURATION_TABLE*ConfigurationTable // system configuration table
} EFI_SYSTEM_TABLE;



/*
Output 6-1: A hex dump of Lion's boot.efi
morpheus@minion (/)> od -A x -t x4 /System/Library/CoreServices/boot.efi
0000000          0ef1fab9        00000002        01000007        00000003
0000010          00000030        0006c840        00000000        00000007
0000020          00000003        0006c870        00064e40        00000000
---------------------------------------------------------------------------
0000030          00905a4d        00000003        00000004        0000ffff
...
0000070          0eba1f0e        cd09b400        4c01b821        685421cd
0000080          70207369        72676f72        63206d61        6f6e6e61
0000090          65622074        6e757220        206e6920        20534f44
...
...
006c860          624de04e        bd2b36a3        238d05f5        29d04881
--------------------------------------------------------------------------
006c870          00905a4d        00000003        00000004        0000ffff
006c880          000000b8        00000000        00000040        00000000
006c890          00000000        00000000        00000000        00000000 
 */