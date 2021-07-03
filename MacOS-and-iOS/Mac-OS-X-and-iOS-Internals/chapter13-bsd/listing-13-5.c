// Listing 13-5: posix_spawn_file_actions_t and posix_spawnattr_t manipulation

int posix_spawn_file_actions_init(posix_spawn_file_actions_t *file_actions);
int posix_spawn_file_actions_addopen
    (posix_spawn_file_actions_t *restrict file_actions, 
     int filedes, const char *restrict path, 
     int oflag, mode_t mode);
int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *file_actions, 
                                     int filedes, int newfiledes);
int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *file_actions, 
                                      int filedes);
int posix_spawn_file_actions_destroy (posix_spawn_file_actions_t *file_actions);
int posix_spawnattr_init(posix_spawnattr_t *attr);
int posix_spawnattr_getflags(const posix_spawnattr_t *restrict attr,
                             short *restrict flags);
int posix_spawnattr_getpgroup(const posix_spawnattr_t *restrict attr, 
                               pid_t *restrict pgroup);
int posix_spawnattr_getsigmask(const posix_spawnattr_t *restrict attr,
                               sigset_t *restrict sigmask);
int posix_spawnattr_setflags(posix_spawnattr_t *attr, short flags);
int posix_spawnattr_setpgroup(posix_spawnattr_t *attr, pid_t pgroup);
int posix_spawnattr_setsigmask(posix_spawnattr_t *restrict attr,
                               const sigset_t *restrict sigmask);
int posix_spawnattr_destroy(posix_spawnattr_t *attr);