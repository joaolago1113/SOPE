#ifndef _ACTION
#define _ACTION

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include "macros.h"

void action(Action action_type, char* name_file, char* dir_path);

#endif
