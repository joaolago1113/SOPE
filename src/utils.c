#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200809L


#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "syscall.h"
#include "common_syscalls.h"
#include "string.h"


#define BUF_SIZE 512


//finds PATH variable in envp[][] and returns pointer to first byte after '='
const char * find_PATH(const char** envp)
{
    for (unsigned i=0; ; i++)
    {
        if(streq("PATH",envp[i],4))
        {
            return envp[i]+5; //after =
        }
    }

    return 0;
}

// fork process, child executes program from arguments and parent waits for child to exit
int try_exec(char* path, char** argv, char** envp)
{
    int64_t sys_ret;

    sys_ret = SYSCALL_2(N_access,path, R_OK | X_OK);
    if(sys_ret < 0) //error
    {
        sys_ret = -sys_ret; //errno
        switch (sys_ret)
        {
            case EACCES:
                WRITE_STDERR_CONST(path);
                WRITE_STDERR_CONST(": No access priviledge.\n");
                break;
        }
        return 1;
    }
    else
    {
        sys_ret= SYSCALL_0(N_fork);
        if (sys_ret == 0) //child
        {
            sys_ret = SYSCALL_3(N_execve, path, argv, envp);
            return -1;
        }
        else if (sys_ret > 0) //parent
        {
            siginfo_t sig;
            sys_ret = SYSCALL_4( N_waitid, P_PID, sys_ret, &sig, WEXITED);
            if (sys_ret < 0)
            {
                return -1;
            }
        }
        else
            return -1;
    }

    return 0;
}


int exec_prog(char** argv, char ** envp)
{
    if(argv[0]==0 || argv[0][0]==0)
    {
        return 1;
    }

    const char *path_env = find_PATH(envp);

    // if(path_env == 0 || path_env[0]==0)
    // {
    //     print_error("PATH environment variable empty\n");
    //     return 2;
    // }
    char full_path[BUF_SIZE];

    unsigned i=0;
    unsigned envi=0;
    for (char c = path_env[envi] ; i < BUF_SIZE - BUF_SIZE/10 && c !=0; i++, envi++, c = path_env[envi])
    {    
        if( c != ':' )
        {
            full_path[i]=c;
        }
        else
        {
            full_path[i]='/';
            str_copy(argv[0], full_path+i+1);
            int ret=try_exec(full_path, argv, envp);
            if(ret < 0)
                return -1;
            else if (ret ==0)
                return 0;
            i=-1;
            
        }
    }

    full_path[i]='/';
    str_copy(argv[0], full_path+i+1);
    int ret=try_exec(full_path, argv, envp);
    if(ret < 0)
        return -1;
    else if (ret ==0)
        return 0;

    //tries for ./
    str_copy(argv[0], full_path);
    ret=try_exec(full_path, argv, envp);
    if(ret < 0)
        return -1;
    else if (ret ==0)
        return 0;

    WRITE_STDOUT(argv[0]);
    WRITE_STDOUT_CONST(": command not found\n");

    return 0;
}



