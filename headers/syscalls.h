#ifndef __SYSCALL__1
#define __SYSCALL__1

#include <stdint.h>

#ifdef __GNUC__
#ifdef __amd64

#define N_write 1
#define N_rt_sigaction 13
#define N_access 21
#define N_fork 57
#define N_execve 59
#define N_chdir 80
#define N_waitid 247
#define N_exit 60


#define SYSCALL_0(sys_num) \
({ \
    int64_t sys_ret; \
    __asm __volatile ( \
    "movq %1, %%rax\n\t"\
    "syscall\n\t" \
    "movq %%rax, %0\n\t"\
    : "=g" (sys_ret)\
    : "g" (sys_num) \
    : "cc", "memory", "%rax", "%rcx", "%r11", "%rdi"\
		);\
    sys_ret; \
})

#define SYSCALL_1(sys_num, a1) \
({ \
    int64_t sys_ret; \
    __asm __volatile ( \
    "movq %1, %%rax\n\t"\
    "movq %2, %%rdi\n\t"\
    "syscall\n\t" \
    "movq %%rax, %0\n\t"\
    : "=g" (sys_ret)\
    : "g"(sys_num), "g" (a1) \
    : "cc", "memory", "%rax", "%rcx", "%r11"\
		);\
    sys_ret; \
})

#define SYSCALL_2(sys_num, a1,a2) \
({ \
    int64_t sys_ret; \
    __asm __volatile ( \
    "movq %1, %%rax\n\t"\
    "movq %2, %%rdi\n\t"\
    "movq %3, %%rsi\n\t"\
    "syscall\n\t" \
    "movq %%rax, %0\n\t"\
    : "=g" (sys_ret)\
    : "g"(sys_num), "g" (a1) , "g" (a2)\
    : "cc", "memory", "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11"\
		);\
    sys_ret; \
})

#define SYSCALL_3(sys_num, a1,a2,a3) \
({ \
    int64_t sys_ret; \
    __asm __volatile ( \
    "movq %1, %%rax\n\t"\
    "movq %2, %%rdi\n\t"\
    "movq %3, %%rsi\n\t"\
    "movq %4, %%rdx\n\t"\
    "syscall\n\t" \
    "movq %%rax, %0\n\t"\
    : "=g" (sys_ret)\
    : "g"(sys_num), "g" (a1) , "g" (a2), "g" (a3)\
    : "cc", "memory", "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11"\
		);\
    sys_ret; \
})


#define SYSCALL_4(sys_num, a1,a2,a3,a4) \
({ \
    int64_t sys_ret; \
    __asm __volatile ( \
    "movq %1, %%rax\n\t"\
    "movq %2, %%rdi\n\t"\
    "movq %3, %%rsi\n\t"\
    "movq %4, %%rdx\n\t"\
    "movq %5, %%r10\n\t"\
    "syscall\n\t" \
    "movq %%rax, %0\n\t"\
    : "=g" (sys_ret)\
    : "g"(sys_num), "g" (a1) , "g" (a2), "g" (a3), "g" (a4)\
    : "cc", "memory", "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "%r10"\
		);\
    sys_ret; \
})

#define SYSCALL_5(sys_num, a1,a2,a3,a4,a5) \
({ \
    int64_t sys_ret; \
    __asm __volatile ( \
    "movq %1, %%rax\n\t"\
    "movq %2, %%rdi\n\t"\
    "movq %3, %%rsi\n\t"\
    "movq %4, %%rdx\n\t"\
    "movq %5, %%r10\n\t"\
    "movq %6, %%r8\n\t"\
    "syscall\n\t" \
    "movq %%rax, %0\n\t"\
    : "=g" (sys_ret)\
    : "g"(sys_num), "g" (a1) , "g" (a2), "g" (a3), "g" (a4), "g" (a5)\
    : "cc", "memory", "%rax", "%rdi", "%rsi", "%rdx", "%rcx", "%r11", "%r10","%r8"\
		);\
    sys_ret; \
})



#endif //x64

#ifdef __i386
#endif //x86


#endif //gcc




#endif
