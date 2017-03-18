#include "common_syscalls.h"

int main (int argc, char* argv[], char* envp[])
{
    WRITE_STDOUT_CONST("Hello\n");
	if(argc < 3)
	{
		EXIT(1);
	}
    return 0;
}
