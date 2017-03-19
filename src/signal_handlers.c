#include "signal_handlers.h"

extern int child;

#include <stdio.h>

void signal_handler_2(int signo){
	
	if(signo == SIGINT){
		
		sigset_t sigmask;
		sigfillset(&sigmask);
		sigdelset(&sigmask, SIGUSR2);
		sigdelset(&sigmask, SIGUSR1);
		sigsuspend(&sigmask);
	}else
		if(signo == SIGUSR1){
			if(child)
				kill(child,SIGUSR1);
			_exit(0);
		}else
			if(signo == SIGUSR2){
					
				if(child)
					kill(child,SIGUSR2);
			}
}


void signal_handler(int signo){
	if(signo == SIGINT){
		char res;
		write(STDOUT_FILENO, "\nAre you sure you want to terminate(Y/N)? ",41);
		do{
			read(STDIN_FILENO, &res, 1);
			if(res == 'N' || res == 'n')
			{
				if(child){
					kill(child,SIGUSR2);
				}
				break;
			}else
				if(res == 'Y' || res == 'y')
				{
					kill(child,SIGUSR1);
					_exit(0);
				}
		}while(res != 'Y' && res != 'y' && res != 'N' && res != 'n');
	}
}
