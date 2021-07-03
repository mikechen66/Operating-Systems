// Listing 16-1: Simple, but working code to list extended attributes

#include <sys/xattr.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE         4096

// Minimal version of xattr, but one that actually presents compressed attributes
// Can be extended to support reading and writing the attribute themselves
// (left as an exercise for the reader)
int  main (int argc, char **argv) {
    char *fileName = argv[1];
    int xattrsLen;
    char *xattrNames;
    char *attr;
    // We could call listxattr with NULL to get the name len, but – quick & dirty
    // I have yet to see a file with more than 4K of extended attribute names..
    xattrNames = malloc (BUFSIZE);
    memset (xattrNames, '\0', BUFSIZE); // or calloc..
    switch (listxattr(fileName, 
                      xattrNames, 
                      BUFSIZE, 
                      XATTR_SHOWCOMPRESSION | XATTR_NOFOLLOW)) {   
        case 0:
            fprintf(stderr, "File %s has no extended attributes\n", fileName); return (0);
        case -1:
            perror("listxattr"); return (1);
        default: // it worked. fall through
        ;
    }
    // Rely on attributes being NULL terminated..
    for (attr = xattrNames; attr[0]; attr += strlen(attr) + 1) {
        printf ("Attribute: %s\n", attr);
    }
    free(xattrNames); // Be nice. Clean up
    return (0);
}


/* 
Output 16-1: The com.apple.FinderInfo attribute changing along with color labels
morpheus@Ergo (/)$ jxattr  -p ∼/Desktop/test 
Attribute: com.apple.FinderInfo (32 bytes)
\x0\x0\x0\x0\x0\x0\x0\x0\x0\xc\x0\x0\x0...  # Red
Attribute: com.apple.FinderInfo (32 bytes)
\x0\x0\x0\x0\x0\x0\x0\x0\x0\xe\x0\x0\x0...  # Orange
Attribute: com.apple.FinderInfo (32 bytes)
\x0\x0\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0…    # Gray 
 */