// Listing 13-4: posix_spawn

int posix_spawn(pid_t *restrict pid,        // OUT pointer to spawned process pid 
                const char *restrict path,                 // absolute or relative path to the image  
                const posix_spawn_file_actions_t *file_act,// set up by posix_spawn_file_actions_init()
                const posix_spawnattr_t *restrict attrp,   // set up by posix_spawnattr_init()
                char *const argv[restrict],                // argv[0], or full argv[] command-line
                char *const envp[restrict]);               // environment pointer (same as in exec*e)