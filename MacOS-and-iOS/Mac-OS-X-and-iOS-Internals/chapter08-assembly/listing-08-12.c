// Listing 8-12: The bsd/kern/syscalls.master file

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>

0       AUE_NULL        ALL     { int nosys(void); }   { indirect syscall }
1       AUE_EXIT        ALL     { void exit(int rval) NO_SYSCALL_STUB; } 
2       AUE_FORK        ALL     { int fork(void) NO_SYSCALL_STUB; } 
3       AUE_NULL        ALL     { user_ssize_t read(int fd, user_addr_t cbuf, user_size
_t nbyte); } 
4       AUE_NULL        ALL     { user_ssize_t write(int fd, user_addr_t cbuf, user_size
_t nbyte); } 
5       AUE_OPEN_RWTC   ALL     { int open(user_addr_t path, int flags, int mode) NO
_SYSCALL_STUB; } 
// ...
// ... many more system calls omitted here 
// ... 
433     AUE_NULL        ALL     { int pid_suspend(int pid); }
434     AUE_NULL        ALL     { int pid_resume(int pid); }
#if CONFIG_EMBEDDED
435     AUE_NULL        ALL     { int pid_hibernate(int pid); }
436     AUE_NULL        ALL     { int pid_shutdown_sockets(int pid, int level); }
#else
435     AUE_NULL        ALL     { int nosys(void); } 
436     AUE_NULL        ALL     { int nosys(void); }
#endif
437     AUE_NULL        ALL     { int nosys(void); } { old shared_region_slide_np }
438     AUE_NULL        ALL     { int shared_region_map_and_slide_np(int fd, uint32_t 
count, const struct shared_file_mapping_np *mappings, uint32_t slide, uint64_t* 
slide_start, uint32_t slide_size) NO_SYSCALL_STUB; }
// Mountain Lion also contains 439 – kas_info