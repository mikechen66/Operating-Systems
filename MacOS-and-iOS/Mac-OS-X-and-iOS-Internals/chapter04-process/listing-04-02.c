// Listing 4-2: Handling multiple architectures and universal (fat) binaries

#include <stdio.h>
#include <mach-o/arch.h>

const char *ByteOrder(enum NXByteOrder BO){
    switch (BO){
        case NX_LittleEndian: return (”Little-Endian”);
        case NX_BigEndian:    return (”Big-Endian”);
        case NX_UnknownByteOrder: return (”Unknown”);
        default: return (”!?!”);
    }
}

int main(){
const NXArchInfo *local = NXGetLocalArchInfo();
const NXArchInfo *known = NXGetAllArchInfos();

while (known && known->description){
    printf (”Known: %s\t%x/%x\t%s\n”, known->description,
            known->cputype, known->cpusubtype,
            ByteOrder(known->byteorder));
    known++;
}

if (local) {
    printf (”Local - %s\t%x/%x\t%s\n”, local->description,
            local->cputype, local->cpusubtype,
            ByteOrder(local->byteorder));
}
return(0);
}