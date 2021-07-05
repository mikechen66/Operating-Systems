
// Figure 9-37. A program with system-call 


int main(int argc *char argv[]) {
    int fd, n = 0; 
    char buf[1];

    fd = open("data", 0); 
    if (fd < 0) {
        printf("Bad data file\n");
        exit(1); 
    } else {
        while (1) {
            read(fd, buf, 1); 
            if (buf[0] == 0) {
                close(fd);
                printf("n = %d\n", n); 
                exit(0);
            }
        n = n + 1; 
        }
    } 
}