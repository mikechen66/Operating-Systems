// Listing 6-5: A sample program to print all the NVRAM variables on a Mac

#include <efi.h>
#include <efilib.h>

#define PROTOCOL_ID_ID  \
    { 0x47c7b226, 0xc42a, 0x11d2, {0x8e, 0x57, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }

static EFI_GUID SProtId                = PROTOCOL_ID_ID;

// Simple EFI app to dump all variables, derived from one of the GNU EFI Samples
EFI_STATUS
efi_main (EFI_HANDLE image, EFI_SYSTEM_TABLE *systab) {
    EFI_STATUS status;
    CHAR16 name[256], *val, fmt[20];
    EFI_GUID vendor;
    UINTN size;
    InitializeLib(image, systab);
    name[0] = 0;
    vendor = NullGuid;
    Print(L"GUID                                Variable Name        Value\n");
    Print(L"=================================== ==================== ========\n");
    while (1) {
        StrCpy(fmt, L"%.-35g %.-20s %s\n");
        size = sizeof(name);
        status = uefi_call_wrapper(RT->GetNextVariableName, 3, 
                                   &size, name, &vendor);
        if (status != EFI_SUCCESS)
            break;
        val = LibGetVariable(name, &vendor);
        if (CompareGuid(&vendor, &SProtId) ==0) {
            StrCpy(fmt, L"%.-35g %.-20s %.-35g\n");
            Print (fmt, &vendor, name , &val);
        }
        else
            Print(fmt, &vendor, name, val);
            FreePool(val);
    }
    return EFI_SUCCESS;
}



/*
Output 6-2: A dump of the EFI Variables from a Mac Mini:
Shell> dir fs0:                     # either ls or dir work
Directory of: fs0:\
 04/01/12   09:30a                   48,354    printenv.efi
 03/23/10   01:07a <DIR>  r            352     EFI
Shell> fs0:\printenv.efi
GUID                                Variable Name        Value
=================================== ==================== ========
E6C2F70A-B604-4877-85BA-DEEC89E117E PchInit              <B0><FF><8E><D0>AˆC
Efi                                 MemoryConfig         RLEXˆK
4DFBBAAB-1392-4FDE-ABB8-C41CC5AD7D5 Setup                
05299C28-3953-4A5F-B7D8-F6C6A7150B2 SetupDefaults        
Efi                                 Timeout              ˆE<FF><8E><D0>AˆC
AF9FFD67-EC10-488A-9DFC-6CBF5EE22C2 AcpiGlobalVariable   P<FE><8E>
Efi                                 Lang                 eng<8E>
Efi                                 BootFFFF             ˆA
Efi                                 BootOrder            <80>
Efi                                 epid_provisioned     ˆA
Efi                                 lock_mch_s3          ˆA
7C436110-AB2A-4BBB-A880-FE41995C9F8 SystemAudioVolume    h
36C28AB5-6566-4C50-9EBD-CBB920F8384 preferred-networks   
36C28AB5-6566-4C50-9EBD-CBB920F8384 preferred-count      ˆA
36C28AB5-6566-4C50-9EBD-CBB920F8384 current-network      
4D1EDE05-38C7-4A6A-9CC6-4BCCA8B38C1 AAPL,PathProperties0 RˆA
7C436110-AB2A-4BBB-A880-FE41995C9F8 aht-results
<dict><key>_name</key><string>spdiags_aht_value</string><key>spdiags_last_run_key</key>
<date>4011-09-16T18:36:02Z</date><key>spdiags_result_key</key><string>
spdiags_passed_value</string><key>spdiags_version_key</key><string>3A224</string>
</dict>7C436110-AB2A-4BBB-A880-FE41995C9F8 fmm-computer-name    Minion
Efi                                 Boot0080             ˆA
7C436110-AB2A-4BBB-A880-FE41995C9F8 efi-boot-device-data ˆBˆAˆL<D0>AˆC
7C436110-AB2A-4BBB-A880-FE41995C9F8 efi-boot-device
<array><dict><key>IOMatch</key><dict><key>IOProviderClass</key><string>IOMedia</string>
<key>IOPropertyMatch</key><dict><key>UUID</key><string>50DD0659-0F10-4307-860B-
6908BD051907</string></dict></dict><key>BLLastBSDName</key><string>disk0s2</string>
</dict></array>
ShellAlias                          copy                 cp
...
 */