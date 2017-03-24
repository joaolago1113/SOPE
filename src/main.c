#include <string.h>
#include <signal.h>
#include "macros.h"
#include "search.h"
#include "signal_handlers.h"

int child_counter;

char** argv_2;

struct sigaction oldsigaction;

int main (int argc, char* argv[], char* envp[])
{	
	//"A child created via fork(2) inherits a copy of its parent's signal mask"

	sigaction(SIGTSTP, 0,&oldsigaction);
	struct sigaction newsigaction;

	newsigaction = oldsigaction;
	newsigaction.sa_handler = &signal_handler;

	sigaction(SIGTSTP, &newsigaction,0);
	signal(SIGINT, signal_handler);

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

	int i;
	argv_2 = &argv[5];
	child_counter = 0;
	search(search_type, action_type, argv[3] , argv[1]);
	for(i = 0; i < child_counter; i++){
		wait(0);
	}
    return 0;
}
