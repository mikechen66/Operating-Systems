// Listing 19-3: Traversing I/O Kit's service plane in search of a specific device

//
// Simple I/O Kit Registry walker
// Compile with -framework IOKit
#include <stdio.h>
#include <mach/mach.h>
#include <CoreFoundation/CoreFoundation.h> // For CFDictionary
#include <device/device_types.h> // for io_name, io_string

// In OS X, you can just #include <IOKit/IOKitLib.h>. Not so on iOS
// in which the following need to be included directly
#define IOKIT   // to unlock device/device_types..

// from IOKit/IOKitLib.h
extern const mach_port_t kIOMasterPortDefault;

// from IOKit/IOTypes.h
typedef io_object_t     io_connect_t;
typedef io_object_t     io_enumerator_t;
typedef io_object_t     io_iterator_t;
typedef io_object_t     io_registry_entry_t;
typedef io_object_t     io_service_t;
// Prototypes also necessary on iOS
kern_return_t IOServiceGetMatchingServices(
    mach_port_t     masterPort,
    CFDictionaryRef matching,
    io_iterator_t * existing );
CFMutableDictionaryRef IOServiceMatching(const char *name);
// Main starts here
int main(int argc, char **argv) {
    io_iterator_t deviceList;
    io_service_t  device;
    io_name_t     deviceName;
    io_string_t   devicePath;
    char         *ioPlaneName = “IOService”;
    int           dev = 0;
    kern_return_t kr;
    // Code does not check validity of plane (left as exercise)
    // Try IOUSB, IOPower, IOACPIPlane, IODeviceTree
    if (argv[1]) 
        ioPlaneName = argv[1];
    // Iterate over all services matching user provided class.
    // Note the call to IOServiceMatching, to create the dictionary
    kr = IOServiceGetMatchingServices(kIOMasterPortDefault,
                                      IOServiceMatching(”IOService”),
                                      &deviceList);
    // Would be nicer to check for kr != KERN_SUCCESS, but omitted for brevity
    if (kr){ 
        fprintf(stderr,”IOServiceGetMatchingServices: error\n”); 
        exit(1);
    }
    if (!deviceList) {  
        fprintf(stderr,”No devices matched\n”); 
        exit(2); 
    }
    while ( IOIteratorIsValid(deviceList) &&         
            (device = IOIteratorNext(deviceList))) {
        kr = IORegistryEntryGetName(device, deviceName);
        if (kr) {
            fprintf (stderr,”Error getting name for device\n”); 
            IOObjectRelease(device);
            continue;
        }
        kr = IORegistryEntryGetPath(device, ioPlaneName, devicePath);
        if (kr) { 
            // Device does not exist on this plane
            IOObjectRelease(device); 
            continue; 
        }
         // can listProperties here, increment device count, etc..
        dev++;
        printf(”%s\t%s\n”,deviceName, devicePath);
    }
    if (device) {
        fprintf (stderr,
                 "Iterator invalidated while getting devices. Did configuration change?\n");
        }
    return kr;
}