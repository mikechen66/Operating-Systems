// Listing 19-4: A property getter function for an IOService

void listProperties(io_service_t     Service) {
    CFMutableDictionaryRef propertiesDict;
    kern_return_t kr = IORegistryEntryCreateCFProperties( Service,
                                                    &propertiesDict,
                                                    kCFAllocatorDefault,
                                                    kNilOptions );
    if (!kr) { 
        fprintf (stderr,”Error getting properties..\n”); 
        return; 
    }
    // If kr indicates success, we have the properties as a dict. From here,
    // it's just a matter of printing the CFDictionary, in this example, as XML
    CFDataRef xml = CFPropertyListCreateXMLData(kCFAllocatorDefault,
                                                (CFPropertyListRef)propertiesDict);
    if (xml) {
        write(1, CFDataGetBytePtr(xml), CFDataGetLength(xml));
        CFRelease(xml);
    }
}