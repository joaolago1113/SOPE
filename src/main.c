#include "common_syscalls.h"

int main (int argc, char* argv[], char* envp[])
{
    WRITE_STDOUT_CONST("Hello\n");

    return 0;
}
