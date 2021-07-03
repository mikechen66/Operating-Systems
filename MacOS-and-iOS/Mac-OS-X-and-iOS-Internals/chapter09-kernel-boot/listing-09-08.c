// Listing 9-8: Testing a panic image (OS X only)

size_t len = 0; 
int name[3] = { CTL_KERN, KERN_PANICINFO, KERN_PANICINFO_IMAGE + 2 }; 
sysctl(name, 3, NULL, (void *)&len, NULL, 0);