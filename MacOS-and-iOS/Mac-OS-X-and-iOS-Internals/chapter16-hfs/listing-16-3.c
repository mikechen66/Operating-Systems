// Listing 16-3: _decmp_get_func, used to obtain decompressor functions

_decmp_get_func(uint32_t type, int offset) {
    /*
    this function should be called while holding a shared lock to decompressorsLock,
    and will return with the lock held
    */
        
    if (type >= CMP_MAX) // only up to CMP_MAX decompressors
        return NULL;

    if (decompressors[type] != NULL) {
       // already have a registered decompressor at this offset, return its function
       return _func_from_offset(type, offset);
    }
        
    // does IOKit know about a kext that is supposed to provide this type?
    char providesName[80];
    snprintf(providesName, sizeof(providesName),
        "com.apple.AppleFSCompression.providesType%u", type);

    // I/O Kit and its "Catalogue" are both discussed in detail in Chapter 19
    if (IOCatalogueMatchingDriversPresent(providesName)) {
        // there is a kext that says it will register for this type, so let's wait for it
        char resourceName[80];
        uint64_t delay = 10000000ULL; // 10 milliseconds.
        snprintf(resourceName, sizeof(resourceName),  
                 "com.apple.AppleFSCompression.Type%u", type);
        printf("waiting for %s\n", resourceName);
        while(decompressors[type] == NULL) {
            lck_rw_done(decompressorsLock);
            if (IOServiceWaitForMatchingResource(resourceName, delay)) {
                break;
            }
            if (!IOCatalogueMatchingDriversPresent(providesName)) {
                printf("the kext with %s is no longer present\n", providesName);
                break;
            }
            printf("still waiting for %s\n", resourceName);
            delay *= 2;
            lck_rw_lock_shared(decompressorsLock);
        }
        // IOKit says the kext is loaded, so it should be registered too!
        if (decompressors[type] == NULL) {
            ErrorLog("we found %s, but the type still isn't registered\n", providesName);
            return NULL;
        }
        // it's now registered, so let's return the function
        return _func_from_offset(type, offset);
    }
        // the compressor hasn't registered, so it never will unless someone
        // manually kextloads it
        ErrorLog("tried to access a compressed file of unregistered type %d\n", type);
        return NULL;
}