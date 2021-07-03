// Listing 17-15: Sample code to bind a new utun interface

int tun(unsigned int num) {
    struct sockaddr_ctl sc;
    struct ctl_info ctlInfo;
    int s;                     // returned socket descriptor
    memset(&ctlInfo, 0, sizeof(ctlInfo));
    strncpy(ctlInfo.ctl_name, UTUN_CONTROL_NAME, sizeof(ctlInfo.ctl_name));
    s = socket(PF_SYSTEM, SOCK_DGRAM, SYSPROTO_CONTROL);
    if (s < 0) { 
        perror("socket"); 
        return -1; 
    }
    if (ioctl(s, CTLIOCGINFO, &ctlInfo) == -1) {
        perror("CTLIOCGINFO");
        close(s);
        return -1;
    }
    sc.sc_family  = PF_SYSTEM;
    sc.ss_sysaddr = AF_SYS_CONTROL;
    sc.sc_id = ctlInfo.ctl_id;
    sc.sc_len = sizeof(sc);
  
    sc.sc_unit = num;
    if (connect(s, (struct sockaddr *)&sc, sizeof(sc)) == -1) {
        perror("connect");
        close(s);
        return -1;
    }
    return s;
}