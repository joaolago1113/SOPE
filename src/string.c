#include <stdbool.h>
#include <stddef.h>

//splits strings in buf separeted by spaces replacing them with '\0', 
//arr will contain narg positions and pointers to start of each split string
int split_strings (char ** arr, unsigned narg, char *buf)
{
    if (narg == 0 || arr==0 || buf ==0)
        return 1;

    bool next =true;
    unsigned j=0;
    for (unsigned i=0; buf[i]!=0; i++)
    {
        if (buf[i]==' ')
        {
            buf[i]=0;
            next=true;
        }
        else 
        {
            if (next)
            {
                arr[j]=buf+i;
                next=false;
                j++;
                if (j == narg-1)
                {
                    return 1;
                }
            }
        }
    }
    arr[j]=0;
    return 0;
}

//true if string equal, false otherwise
bool streq (const char* s1,const char* s2, unsigned n)
{
    unsigned i=0;
    for (; i < n; i++)
    {
        const char c1 = s1[i];
        const char c2 = s2[i];
        if(c1!=c2)
        {
            return 0;
        }
    }
    i--;
    if (s1[i] == 0 && s2[i]==0)
        return 0;

    return 1;
}

void str_copy(const char* src, char* dest)
{
    unsigned i;
    for (i=0; src[i]!=0; i++)
    {
            dest[i]=src[i];
    }
    dest[i]=src[i];
}

//str length witohut null terminator
size_t str_length (const char* str)
{
	const char* iter = str;
	for (;*iter != 0; iter++)
	{ }
	
	return (size_t)(iter - str);
	
}


