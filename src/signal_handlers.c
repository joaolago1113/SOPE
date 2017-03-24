#include "signal_handlers.h"


#include <stdio.h>

void signal_handler(int signo){
	if(signo == SIGINT){
		
		char res;
		write(STDOUT_FILENO, "\nAre you sure you want to terminate(Y/N)? ",41);
		kill(0, SIGTSTP);	
		do{
			read(STDIN_FILENO, &res, 1);
			if(res == 'N' || res == 'n')
			{
				kill(0, SIGCONT);		
				break;
			}else
				if(res == 'Y' || res == 'y')
				{					
					kill(0, SIGTERM);		
				}
		}while(res != 'Y' && res != 'y' && res != 'N' && res != 'n');
	}

}
