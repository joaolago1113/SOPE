#include "search.h"

extern int child;

char cwd[350];

char * getDir(char *str){
	
	getcwd(cwd, sizeof(cwd));
	if(str[1] == '.'){
		int i;
		for(i = strlen(cwd)-1; cwd[i]!='/'; i--);
		cwd[i] = '\0';
	}
	
	return cwd;
}

void search(Search search_type, Action action_type , char* name_type_mode, char* dir_path)
{

	
	struct dirent *dentry;
	DIR *dir;
	struct stat stat_entry;

	char dir_path_alt_mem[350];
	char *dir_path_alt = dir_path_alt_mem;
	strcpy(dir_path_alt, dir_path);
	
	if((dir_path_alt[0] == '.') && (dir_path_alt[1] == '.') && ((dir_path_alt[2] == '\0')||(dir_path_alt[2] == '/'))){
		dir_path_alt+=2;
		char *final;
		final = getDir("..");
		strcat(final, dir_path_alt);
		dir_path_alt = final;
	}else
		if((dir_path_alt[0] == '.') && ((dir_path_alt[1] == '\0')||(dir_path_alt[1] == '/'))) {
			if(strlen(dir_path_alt)>1)
				dir_path_alt++;
			char *final;
			
			final = getDir(".");
			if(strlen(dir_path_alt)>1)
				strcat(final, dir_path_alt);
			dir_path_alt = final;
		}

	if ((dir = opendir(dir_path_alt)) == NULL){
		perror(dir_path_alt);
		_exit(2);
	}
	

	while((dentry = readdir(dir)) != NULL){
		if(!strcmp(dentry->d_name,"..") || !strcmp(dentry->d_name,".")){
			continue;
		}
		char filepath[350];
		strcpy(filepath,dir_path_alt);
		strcat(filepath,"/");
		strcat(filepath,dentry->d_name);
		lstat(filepath, &stat_entry);
		switch(search_type){
			case NAME:
				if(!strcmp(dentry->d_name,name_type_mode)){
					action(action_type, dentry->d_name, dir_path);
				}
				break;
			case TYPE:
				switch((char)name_type_mode[0]){
					case 'f':
						if(S_ISREG(stat_entry.st_mode)){
							action(action_type, dentry->d_name, dir_path);
						}
						break;
					case 'd':
						if(S_ISDIR(stat_entry.st_mode)){
							action(action_type, dentry->d_name, dir_path);
						}
						break;					
					case 'l':
						if(S_ISLNK(stat_entry.st_mode)){
							action(action_type, dentry->d_name, dir_path);
						}
						break;
				}
				break;
			case PERM:
				;
				char mode_permissions_[5];
				char *mode_permissions;
				sprintf(mode_permissions_, "%o" ,(stat_entry.st_mode));
				mode_permissions = (mode_permissions_+(strlen(mode_permissions_)-3));
				if(!strcmp(mode_permissions, name_type_mode)){
					action(action_type, dentry->d_name, dir_path);
				}
				break;
		}
		if(S_ISDIR(stat_entry.st_mode)){
			char pathname[350];
			strcpy(pathname, dir_path);
			strcat(pathname,"/");
			strcat(pathname, dentry->d_name);

			if((action_type == DELETE) && (access(pathname, F_OK)==-1)){
				//itwasdeleted
				continue;
			}
			if((child = fork())){
				//1)recursividade 2)escrita sync.
				int status;
				wait(&status);
				int exit_status = WEXITSTATUS(status);
				if(exit_status!=0){
					write(STDOUT_FILENO, "Search in ", 10);
					write(STDOUT_FILENO, pathname, strlen(pathname));
					write(STDOUT_FILENO, " exited with status: ", 21);
					char exst[10];
					sprintf(exst, "%d", exit_status);
					write(STDOUT_FILENO, exst, strlen(exst));
					write(STDOUT_FILENO, "\n", 1);
				}
			}else
			{
				signal(SIGINT, signal_handler_2);
				search(search_type, action_type, name_type_mode, pathname);
				_exit(0);
			}
		}
	}
	//free(dir_path_alt);
}
