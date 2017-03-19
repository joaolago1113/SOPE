#include "action.h"

void action(Action action_type, char* name_file, char* path){
	char dir_path[350];
	strcpy(dir_path,path);
	strcat(dir_path,"/");
	strcat(dir_path, name_file);
	switch(action_type){
		case PRINT:
			write(STDOUT_FILENO, dir_path, strlen(dir_path));
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
			
			break;
	}
}


