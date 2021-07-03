// Listing 5-4: Enabling or disabling kdebug_enable from user mode via sysctl

int set_kdebug_enable(int value)
{
    int rc;
    int mib[4];
    
    mib[0] = CTL_KERN; 
    mib[1] = KERN_KDEBUG; 
    mib[2] = KERN_KDENABLE; 
    mib[3] = value; 
    if ((rc = sysctl(mib, 4, NULL, &oldlen, NULL, 0) < 0) {perror(”sysctl”);}
    return (rc);
}