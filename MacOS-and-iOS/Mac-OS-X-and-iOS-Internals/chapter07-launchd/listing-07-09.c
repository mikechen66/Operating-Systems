// Listing 7-9: A generic launchd wrapper

#include <stdio.h>
#include <sys/socket.h>
#include <launch.h> // LaunchD related stuff
#include <stdlib.h> // for exit, and the like
#include <unistd.h> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h> // for getaddrinfo
#include <fcntl.h>

#define JOBKEY_LISTENERS "Listeners"
#define MAXSIZE 1024
#define CMD_MAX 80

int main (int argc, char **argv) {
    launch_data_t checkinReq, checkinResp;
    launch_data_t  mySocketsDict;
    launch_data_t  myListeners;
     
    int fdNum;
    int fd;
    struct sockaddr sa;
    unsigned int len = sizeof(struct sockaddr);
    int fdSession ;

    /* First, we must check-in with launchD.  */
    checkinReq = launch_data_new_string(LAUNCH_KEY_CHECKIN);
    checkinResp = launch_msg(checkinReq);
    if (!checkinResp) {
        // Failed to checkin with launchd - this can only be because we are run outside
        // its context. Print a message and exit
        fprintf (stderr,"This command can only be run under launchd\n");
        exit(2);
    }

    mySocketsDict = launch_data_dict_lookup(checkinResp, LAUNCH_JOBKEY_SOCKETS);

    if (!mySocketsDict) { 
        fprintf (stderr, "Can't find <Sockets> Key in plist\n"); 
        exit(1); 
    }

    myListeners = launch_data_dict_lookup(mySocketsDict, JOBKEY_LISTENERS);

    if (!myListeners) {
        fprintf (stderr, "Can't find <Listeners> Key inside <Sockets> in plist\n");
        exit(1);
        fdNum = launch_data_array_get_count(myListeners);    
        if (fdNum != 1) {
            fprintf (stderr,"Number of File Descriptors is %d - should be 1\n", fdNum);
            exit(1);
        }
    }

    // Get file descriptor (socket) from launchd
    fd = launch_data_get_fd(launch_data_array_get_index(myListeners,0));
    fdSession = accept(fd, &sa, &len);
    launch_data_free(checkinResp); // be nice..

    // Print to stderr (/var/log/system.log) before redirecting..
    fprintf (stderr, "Execing %s\n", argv[1]);
     
    dup2(fdSession,0);     // redirect stdin
    dup2(fdSession,1);     // redirect stdout
    dup2(fdSession,2);     // redirect stderr
    dup2(fdSession,255);   // Shells also like FD 255.

    // Quick and dirty example – assumes at least two arguments for the wrapper,
    // the first being the path to the program to execute, and the second (and later)
    // being the argument to the launchd program
    execl(argv[1], argv[1], argv[2], NULL);

    // If we're here, the execl failed.
    close(fdSession);

    return (42);
}



/*
Output 7-1: Using launchctl(1) to start a LaunchDaemon
root@Minion (∼)# launchctl
launchd% load /System/Library/LaunchDaemons/com.technologeeks.wrapper.plist
launchd% start com.technologeeks.wrapper
launchd% exit
 */

/*
Output 7-2: Demonstrating a launchd-wrapped root shell
root@Minion (∼)# telnet localhost 1024 # or whereever you set your SockServiceName
Trying 127.0.0.1...
Connected to localhost.
Escape character is ‘ˆ]'.
zsh# id;
uid=0(root) gid=0(wheel) groups=0(wheel),401(com.apple.access_screensharing),
402(com.apple.sharepoint.group.1),1(daemon),
2(kmem),3(sys),4(tty),5(operator),8(procview),9(procmod),12(everyone),
20(staff),29(certusers), 
33(_appstore),61(localaccounts)80(admin),98(_lpadmin),100(_lpoperator),
204(_developer)
zsh: command not found: ˆM
zsh# whoami;
root
zsh: command not found: ˆM
 */
