#include "prompt.h"
#include "headers.h"
#include "piping.h"
#define _GNU_SOURCE
struct utsname buf;
char wordir[105];
void prompt(int sig) {
    int user=uname(&buf);
    char* name=getlogin();
    getcwd(wordir,100);
    if(user==-1)
    {
        perror("Error:");
    }
    else
    {
        // printf("%d",foreprocess);
        if(succflag==1)
        {
            printf("%s",":')");
        }
        else
        {
            printf("%s",":'(");
        }
        
        printf("<%s@%s:%s>",name,buf.nodename,wordir);
    }
}

void ctrlchandler(int sig)
{
    printf("%s","\n");
    prompt(sig);
    fflush(stdout);
}

void ctrlzhandler(int sig)
{
    printf("%s","\n");
    prompt(sig);
    fflush(stdout);
}