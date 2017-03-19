#include <string.h>
#include <signal.h>
#include "macros.h"
#include "search.h"
#include "signal_handlers.h"

int child = 0;

int main (int argc, char* argv[], char* envp[])
{	
	//"A child created via fork(2) inherits a copy of its parent's signal mask"
	sigset_t oldmask, newmask;
	sigprocmask(SIG_BLOCK, 0, &oldmask);
	newmask = oldmask;
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);
	sigprocmask(SIG_BLOCK, &newmask, 0);
	signal(SIGINT, signal_handler);
	signal(SIGUSR1, signal_handler_2);
	signal(SIGUSR2, signal_handler_2);

	short search_type = 0;

	short action_type = 0;

	if(!strcmp(argv[2], "-name")){
		search_type = NAME;
	}else
		if(!strcmp(argv[2], "-type")){
			search_type = TYPE;
		}else
			if(!strcmp(argv[2], "-perm")){
				search_type = PERM;
			}else
			{
				_exit(2);
			}
	

	if(!strcmp(argv[4], "-print")){
		action_type = PRINT;
	}else
		if(!strcmp(argv[4], "-delete")){
			action_type = DELETE;
		}else
			if(!strcmp(argv[4], "-exec")){
				action_type = EXEC;
			}else
			{
				_exit(3);
			}
	if( strlen(argv[3]) == 4 && search_type == PERM){
		argv[3] = argv[3]+1;
	}

	search(search_type, action_type, argv[3] , argv[1]);
	sigprocmask(SIG_SETMASK, &oldmask, 0);
    return 0;
}
