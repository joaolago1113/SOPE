#ifndef __COMMON_SYSCALL__
#define __COMMON_SYSCALL__

#include "syscall.h"
#include "string.h"

#ifdef __GNUC__
#ifdef __amd64


#define STDERR_NO 2
    // File number of stderr; 2.
#define STDIN_NO 0
    // File number of stdin; 0.
#define STDOUT_NO 1
    // File number of stdout; 1.


#define WRITE_STDOUT(str) ({ \
	SYSCALL_3 (N_write, STDOUT_NO, str, str_length(str)); \
})

#define WRITE_STDOUT_CONST(str) ({ \
	SYSCALL_3 (N_write, STDOUT_NO, str, sizeof(str) - 1); \
})

#define WRITE_STDERR(str) ({ \
	SYSCALL_3 (N_write, STDERR_NO, str, str_length(str)); \
})

#define WRITE_STDERR_CONST(str) ({ \
	SYSCALL_3 (N_write, STDERR_NO, str, sizeof(str) - 1); \
})



#endif //x64

#ifdef __i386
#endif //x86


#endif //gcc




#endif
