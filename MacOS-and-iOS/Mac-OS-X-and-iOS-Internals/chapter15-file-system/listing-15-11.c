// Listing 15-11: An example fuse_main()

int main (int argc, char **argv) {
    struct fuse_operations  fuseOps;
    // handle any arguments..
    fuseOps.init =    // pointer to initializer
    fuseOps.destroy = // pointer to destructor
    fuseOps.statfs =  // pointer to statfs(2) handler
    fuseOps.open =    // pointer to file open(2) handler
    fuseOps.release = // pointer to file close(2) handler
    fuseOps.opendir =    // pointer to opendir(3) handler
    fuseOps.releasedir = // pointer to closedir(3) handler
    fuseOps.getattr =    // pointer to getattrlist(2) handler
    fuseOps.read =       // pointer to file read(2) handler
    fuseOps.readdir =    // pointer to readdir(3) handler
    fuseOps.readlink =   // pointer to readlink(2) handler
    // other handlers // ...
    return fuse_main(argc, new_argv, &fuseOps, NULL);
}