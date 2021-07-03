// Listing 18-7: Using the IOKit-exposed OSKext APIs to provide kextstat(8)-like functionality

 /* A simple implementation of kextstat(8) which actually works on iOS, as well:
  * All the work is done by OSKextCopyLoadedKextInfo.
  *
  * Compile with –framework IOKit –framework CoreFoundation
  */

#include <CoreFoundation/CoreFoundation.h>

void printKexts(CFDictionaryRef dict){
    // Simple dump of an XML dictionary
    CFDataRef xml = CFPropertyListCreateXMLData(kCFAllocatorDefault,
                                                (CFPropertyListRef)dict);
    write(1, CFDataGetBytePtr(xml), CFDataGetLength(xml));
    CFRelease(xml);
}

int main (int argc, char **argv) {
    // OSKextCopyLoadedKextInfo does exactly that, i.e. obtains loaded kext
    // information from kernel, and return it as a CoreFoundation “dictionary" object.
    CFDictionaryRef kextDict =
        OSKextCopyLoadedKextInfo(NULL, // CFArrayRef kextIdentifiers,
        NULL);                         //CFArrayRef infoKeys)
    printKexts(kextDict);
}