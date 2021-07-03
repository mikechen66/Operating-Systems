// Listing 16-11: Walking the B-Tree in search of a file

#define PATH_SEPARATOR L'/'
//
// pseudo code only – this destroys the inputted PathName..
//
key *fileNameToCatalogKey (char *PathName) {
    key *returned = malloc (..);
    UInt32 parentCNID = kHFSPlusRootFolderID; // start at the root folder
    char *sep = strchr (PathName, PATH_SEPARATOR)
    while (sep) {
        *sep = 0;  // Replace ‘/’ with NULL, so pathname is now parent dir
        parentCNID = getFileCNID (parentCNID, PathName);
        PathName= ++sep; // PathName is now whatever follows the parent
        sep = strchr(PathName, PATH_SEPARATOR);
    }
    // if we are here, what's left of the pathname is a file/folder name
    // and parentCNID holds our containing folder
    returned.parentID = parentCNID;
    returned.nodeName.length = cpu_to_be16(strlen(PathName));
    copyAndFlipUnicode(&returned.nodeName.unicode, PathName);
}