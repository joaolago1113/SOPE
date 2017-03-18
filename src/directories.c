#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#define _POSIX_SOURCE

#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <stdlib.h>

#include "syscalls.h"
#include "common_syscalls.h"

struct linux_dirent64 {
    uint64_t       d_ino;    /* 64-bit inode number */
    int64_t        d_off;    /* 64-bit offset to next structure */
    unsigned short d_reclen; /* Size of this dirent */
    unsigned char  d_type;   /* File type */
    char           d_name[]; /* Filename (null-terminated) */
} __attribute__ ((packed));

struct linux_dirent {
    unsigned long  d_ino;     /* Inode number */
    unsigned long  d_off;     /* Offset to next linux_dirent */
    unsigned short d_reclen;  /* Length of this linux_dirent */
    char           d_name[];  /* Filename (null-terminated) */
                        /* length is actually (d_reclen - 2 -
                        offsetof(struct linux_dirent, d_name)) */
    /*
    char           pad;       // Zero padding byte
    char           d_type;    // File type (only since Linux
                                // 2.6.4); offset is (d_reclen - 1)
    */
};


#define NUM_FILES 8
#define BUF_SIZE 256

//change process working dir to path
int change_dir(const char* path)
{
    int64_t sys_ret = SYSCALL_1(N_chdir, path);
    if (sys_ret<0)
    {
        WRITE_STDERR_CONST("Can't change working dir to: ");
        WRITE_STDERR(path);
        WRITE_STDERR_CONST("\n");
    }

    return 0;
}

// copy name and dir_path to buf : buf = dir_path/name
void copy_path (char* buf, char* dir_path, char* name)
{   
    unsigned i;
    for (i=0; dir_path[i]!=0; i++)
    {
            buf[i]=dir_path[i];
    }
    buf[i]=dir_path[i];

    buf[i]='/';
    str_copy(name,buf+i+1);
}

/*
//TODO : modificar para o trab1
int copy_folders(const char* dest_path, const char* src_path, int fd_src, int fd_dest)
{
    int64_t nbytes;
    do {
        char entries[BUF_SIZE*2];
        pid_t pid_arr[BUF_SIZE/4 ];
        SYSCALL_(217, fd_src, entries, sizeof(entries),0,0)
        
        if (sys_ret < 0)
        { 
            errno = -sys_ret;
            perror("SYSCALL: ");
            return -1;
        }
        else
            nbytes=sys_ret;
        
        unsigned pid_index=0;
        for (int64_t bpos=0; bpos < nbytes; )
        {
            const struct linux_dirent64* entry_ptr = (struct linux_dirent64*) (entries + bpos);
            const char d_type = entry_ptr->d_type;
            if (d_type == DT_REG)
            {
                SYSCALL_(57, 0, 0, 0,0,0)
                if (sys_ret == 0)
                {
                    int ret1=copy_file(dest_path, src_path, entry_ptr);
                    SYSCALL_(60, 0, 0,0,0,0)
                }
                else if (sys_ret > 0)
                {
                    pid_arr[pid_index]= sys_ret;
                }
                else
                    return -1;

                pid_index++;
            }
            bpos+=entry_ptr->d_reclen;

        }

        const unsigned nchildren = pid_index;
        for ( pid_index=0; pid_index < nchildren; ++pid_index)
        {
            siginfo_t sig;
            SYSCALL_( 247, P_PID, *((uint64_t *) &pid_arr[pid_index]), &sig, WEXITED, 0)
            if (sys_ret<0)
            {
                return -1;
            }
        }

    } while (nbytes != 0);

    return 0;
}
*/
