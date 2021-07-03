Listing 19-14: Initialization of BSD character devices in IOSerialBSDClient (IOSerialFamily-59)

// Provide a BSD layer compatible cdevsw structure, by populating all the
// system call handlers expected by BSD with those of the I/O Kit class
struct cdevsw IOSerialBSDClient::devsw =
{
    /* d_open     */ IOSerialBSDClient::iossopen,
    /* d_close    */ IOSerialBSDClient::iossclose,
    /* d_read     */ IOSerialBSDClient::iossread,
    /* d_write    */ IOSerialBSDClient::iosswrite,
    /* d_ioctl    */ IOSerialBSDClient::iossioctl,
    /* d_stop     */ IOSerialBSDClient::iossstop,
    /* d_reset    */ (reset_fcn_t *) &nulldev,
    /* d_ttys     */ NULL,
    /* d_select   */ IOSerialBSDClient::iossselect,
    /* d_mmap     */ eno_mmap,
    /* d_strategy */ eno_strat,
    /* d_getc     */ eno_getc,
    /* d_putc     */ eno_putc,
    /* d_type     */ D_TTY
};
// Constructor adds a devsw for TTYs
IOSerialBSDClientGlobals::IOSerialBSDClientGlobals()
{
     // ...
     // Initialization of various globals
     // ...
    fMajor = (unsigned int) -1;             // request dynamic major
    fNames = OSDictionary::withCapacity(4); 
    fLastMinor = 4;                         // four minor devices
    fClients = (IOSerialBSDClient **)
                IOMalloc(fLastMinor * sizeof(fClients[0]));
    if (fClients && fNames) {
        bzero(fClients, fLastMinor * sizeof(fClients[0]));  // memset to zero
        fMajor = cdevsw_add(-1, &IOSerialBSDClient::devsw); // assign major
        cdevsw_setkqueueok(fMajor, &IOSerialBSDClient::devsw, 0); // enable
    }
    if (!isValid())
        IOLog("IOSerialBSDClient didn't initialize");
}

// Destructor removes the devsw added
IOSerialBSDClientGlobals::∼IOSerialBSDClientGlobals() {
    // removal of all globals
if (fMajor != (unsigned int) -1)
        cdevsw_remove(fMajor, &IOSerialBSDClient::devsw);
 ...
}

bool IOSerialBSDClient::createDevNodes() {
    // ...
    // Create the device nodes
    //
    calloutNode = devfs_make_node(fBaseDev | TTY_CALLOUT_INDEX,
        DEVFS_CHAR, UID_ROOT, GID_WHEEL, 0666,
        (char *) calloutName->getCStringNoCopy() + 
                 (uint32_t)sizeof(TTY_DEVFS_PREFIX) - 1);
    dialinNode = devfs_make_node(fBaseDev | TTY_DIALIN_INDEX,
        DEVFS_CHAR, UID_ROOT, GID_WHEEL, 0666,
        (char *) dialinName->getCStringNoCopy() + 
                 (uint32_t)sizeof(TTY_DEVFS_PREFIX) - 1);
    if (!calloutNode || !dialinNode)
        break;
}