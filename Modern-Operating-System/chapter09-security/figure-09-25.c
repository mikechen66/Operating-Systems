
// Figure 9-25. Code that might lead to a command injection attack.

int main(int argc, char *argv[]) {
    char src[100], dst[100], cmd[205] = "cp ";         /* declare 3 strings */
    printf("Please enter name of source file: ");      /* ask for source file */
    gets(src);                                         /* get input from the keyboard */
    strcat(cmd, src);                                  /* concatenate src after cp */ 
    strcat(cmd, " ");                                  /*add a space to the end of cmd */
    printf("Please enter name of destination file: "); /* ask for output file name */
    gets(dst);                                         /* get input from the keyboard */
    strcat(cmd, dst);                                  /* complete the commands string */
    system(cmd);                                       /* execute the cp command */
}
