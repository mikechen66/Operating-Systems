// Listing 19-10: Sample I/O Kit driver init() function

bool sampleDriver::init(IOPhysicalAddress * paddr) {
    bool rc = super::init(); // MUST call superclass before doing anything
    if (!rc) return (rc); // return FALSE to caller if super failed 
    // Do own initialization
    return(false);
}