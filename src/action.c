#include "action.h"

extern char** argv_2;

#include <stdio.h>

void action(Action action_type, char* name_file, char* path){
	char dir_path[350];
	strcpy(dir_path,path);
	strcat(dir_path,"/");
	strcat(dir_path, name_file);
	switch(action_type){
		case PRINT:
			;
			char * dir_path_aux = dir_path;
			while((dir_path_aux[0] == '/') && (dir_path_aux[1] == '/'))
			{
				dir_path_aux++;
			}
			write(STDOUT_FILENO, dir_path_aux, strlen(dir_path_aux));
			write(STDOUT_FILENO, "\n", 1);
			break;
		case DELETE:
			if(access(dir_path, W_OK)!=-1){				
				struct stat s;
				stat(dir_path,&s);
				if(s.st_mode & S_IFDIR){
					if(rmdir(dir_path) ==-1){
						char* msg = strerror(errno);
						write(STDOUT_FILENO, "Cannot delete: ", 15);
						write(STDOUT_FILENO, name_file, strlen(name_file));
						write(STDOUT_FILENO, ", ", 2);
						write(STDOUT_FILENO, msg, strlen(msg));
						write(STDOUT_FILENO, "\n", 1);
					}
				}else
					if(unlink(dir_path) == -1){
						char* msg = strerror(errno);
						write(STDOUT_FILENO, "Cannot delete: ", 15);
						write(STDOUT_FILENO, name_file, strlen(name_file));
						write(STDOUT_FILENO, ", ", 2);
						write(STDOUT_FILENO, msg, strlen(msg));
						write(STDOUT_FILENO, "\n", 1);
					}
			}
			else{
				write(STDOUT_FILENO, "No permission to delete file: ", 30);
				write(STDOUT_FILENO, name_file, strlen(name_file));
				write(STDOUT_FILENO, "\n", 1);
			}
			break;
		case EXEC:
			;
			int chlp;
			if(!(chlp = fork())){
				
				int i;
				for(i=0; (strcmp(argv_2[i],";") && (argv_2[i]!=0)); i++){
					
				}
				char * argv_aux[i+2];

				argv_aux[0] = argv_2[0];
				for(; i-1 ; i--){
					argv_aux[i] = argv_2[i];
				}
				argv_aux[i-1] = name_file;
				argv_aux[i] = 0;
				
				execvp(argv_2[0],argv_aux);
				_exit(9);
			}else{
				int staloc;
				waitpid(chlp, &staloc, 0);}
			break;
	}
}


