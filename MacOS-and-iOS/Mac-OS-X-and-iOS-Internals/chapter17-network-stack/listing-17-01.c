// Listing 17-1: A simple program to spoof packets

#include <sys/socket.h>
#include <net/if.h>
#include <net/ndrv.h>

void main(int argc, char **argv) { 
    int s; 
    int rc; 
    struct sockaddr_ndrv sndrv; 
    u_int8_t packet[1500];
    if (geteuid() != 0) { 
        fprintf (stderr, "You are wasting my time, little man. Come back as root\n");
        exit(1);
    }
    s = socket(PF_NDRV, SOCK_RAW, 0);                // Open socket 
    if (s < 0) { 
        perror ("socket"); 
        exit (1);
    }       // Just in case..
    //Bind to interface, say “en0”, or “en1”
    strlcpy((char*)ndrv.snd_name, “en0”, sizeof(sndrv.snd_name)); 
    ndrv.snd_family = AF_NDRV; 
    ndrv.snd_len = sizeof(sndrv); 
    rc = bind(s, (struct sockaddr*)&sndrv, sizeof(sndrv)); 

    if (rc < 0) { 
        perror("bind"); 
        exit(2);
    } // Could fail if interface doesn't exist
    // Craft packet!
    memset(&packet, 0, sizeof(packet)); 
    // Destination MAC goes in packet[0] through packet[5]
    packet[0] = 0xFF; /* ... */;  packet[5] = 0xFF; 
    // Source MAC address goes in packet[6] through packet[11]
    packet[7] = 0xFF; /* ... */;  packet[11] = 0xFF; 
    // Ethertype is next two
    packet[12] = ...; packet[13] = ...; 
    // And data (Layer III and up) follows
    strcpy((char*) &packet[14], "You can put whatever you want here.. \0");
    rc = sendto(fd, &packet, 1500, 0, (struct sockaddr*)&sndrv, sizeof(sndrv));
}


/* 
Output 17-1: Setting up and tearing down an RFC2893 tunnel using ifconfig gif:
root@Minion (/)# ifconfig gif0 tunnel <localv4> <remotev4>
root@Minion (/)# ifconfig gif0 inet6 <localv6> <remotev6> prefixlen 128 up
 */