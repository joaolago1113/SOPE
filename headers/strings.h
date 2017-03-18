#ifndef _STRING__1
#define _STRING__1

#include <stdbool.h>
#include <stddef.h>

int split_strings (char ** arr, unsigned narg, char *buf);

bool streq (const char* s1,const char* s2, unsigned n);

void str_copy(const char* src, char* dest);

size_t str_length (const char* str);


#endif