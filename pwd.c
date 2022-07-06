#include "pwd.h"
#include "headers.h"
#include "piping.h"
extern int errno;
char address[1005];
void pwd()
{
    errno=0;
    getcwd(address,100);
    if(address==NULL)
    {
        succflag=0;
        perror("Error:");
        return;
    }
    printf("%s\n",address);
}