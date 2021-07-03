// Listing 3-3: Using the SystemConfiguration APIs to query values

#include <SystemConfiguration/SCPreferences.h>
// Also implicitly uses CoreFoundation/CoreFoundation.h

void dumpDict(CFDictionaryRef dict){
    // Quick and dirty way of dumping a dictionary as XML
    CFDataRef xml = CFPropertyListCreateXMLData(kCFAllocatorDefault,
                                                (CFPropertyListRef)dict);
    if (xml) {
        write(1, CFDataGetBytePtr(xml), CFDataGetLength(xml));        
        CFRelease(xml);
    }
}

void main (int argc, char **argv) {
    CFStringRef myName = CFSTR(”com.technologeeks.SystemConfigurationTest”);
    CFArrayRef  keyList;
    SCPreferencesRef prefs = NULL; 
    char *val;
    CFIndex i;
    CFDictionaryRef global;
    // Open a preferences session
    prefs = SCPreferencesCreate(NULL,   // CFAllocatorRef allocator,
                                myName, // CFStringRef name,
                                NULL);  // CFStringRef prefsID
    if (!prefs) { 
        fprintf (stderr,”SCPreferencesCreate”); 
        exit(1); 
    }
    // retrieve preference namespaces
    keyList =  SCPreferencesCopyKeyList (prefs);
    if (!keyList) { 
        fprintf (stderr,”CopyKeyList failed\n”); 
        exit(2);
    }
    // dump ‘em
    for (i = 0; i < CFArrayGetCount(keyList); i++) {
       dumpDict(SCPreferencesGetValue(prefs, CFArrayGetValueAtIndex(keyList, i)));
    }
}