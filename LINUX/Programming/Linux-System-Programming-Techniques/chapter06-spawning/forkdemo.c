#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
   pid_t pid;
   printf("My PID is %d\n", getpid());
   /* fork, save the PID, and check for errors */
   if ( (pid = fork()) == -1 )
   {
      perror("Can't fork");
      return 1;
   }
   if (pid == 0)
   {
      /* if pid is 0 we are in the child process */
      printf("Hello from the child process!\n");
      sleep(120);
   }
   else if(pid > 0)
   {
      /* if pid is greater than 0 we are in 
       * the parent */
      printf("Hello from the parent process! "
         "My child has PID %d\n", pid);
      sleep(120);
   }
   else
   {
      fprintf(stderr, "Something went wrong "
         "forking\n");
      return 1;
   }
   return 0;
}
