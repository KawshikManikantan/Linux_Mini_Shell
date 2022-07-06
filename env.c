#include "headers.h"
#include "env.h"
#include "piping.h"
char str[1000];
char* name;
void env(char* arglist[12])
{
    int w=atoi(arglist[11]);
    if(w==1 && w>3)
    {
        printf("%s","Wrong input given...");
        succflag=0;
        return ;
    }
    else
    {
        if(w==2)
        {
            strcpy(str,"");
        }   
        else
        {
            strcpy(str,arglist[2]);
        }
        int err=setenv(arglist[1],str,1);
        if(err==-1)
        {
            succflag=0;
            perror("Error:");
        }
    }
}

void unenv(char* arglist[12])
{
    int w=atoi(arglist[11]);
    if(w==1 && w>=3)
    {
        printf("%s","Wrong input given...");
        return ;
    }
    else
    {
        int err=unsetenv(arglist[1]);
        if(err==-1)
        {
            succflag=0;
            perror("Error:");
        }
    }
}

void genv(char* arglist[12])
{
    printf("%s",getenv(arglist[1]));
}

