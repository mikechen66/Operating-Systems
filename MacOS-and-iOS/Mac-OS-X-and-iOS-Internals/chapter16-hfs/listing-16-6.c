// Listing 16-6: The hfs_virtualmetafile() function

int hfs_virtualmetafile(struct cnode *cp) {
    const char * filename;
    if (cp->c_parentcnid != kHFSRootFolderID)
        return (0);
    filename = (const char *)cp->c_desc.cd_nameptr;
    if (filename == NULL)
        return (0);
    if ((strncmp(filename, ".journal", sizeof(".journal")) == 0) ||
            (strncmp(filename, ".journal_info_block", sizeof(".journal_info_block")) == 0) ||
            (strncmp(filename, ".quota.user", sizeof(".quota.user")) == 0) ||
            (strncmp(filename, ".quota.group", sizeof(".quota.group")) == 0) ||
            (strncmp(filename, ".hotfiles.btree", sizeof(".hotfiles.btree")) == 0))
        return (1);
        return (0);
    }