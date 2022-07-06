#include "headers.h"
#include "fg.h"
#include "linkedlist.h"
#include "piping.h"
char str1[1010];
void bg(char* arglist[12],node* headp)
{
    node noder=*headp;

    if(atoi(arglist[11])!=2)
    {
        printf("%s","Wrong args\n");
        succflag=0;
        return;
    }

    int num=atoi(arglist[1]);
    
    if(num>numprocess || num<=0)
    {
        printf("%s","Not available- Too large/small\n");
        succflag=0;
        return;
    }

    for(int i=1;i<numprocess-num+1;i++)
    {
        noder=noder->next;
    }

    pid_t processid=noder->ppid;
    int statkill=kill(processid,SIGCONT);

    if(statkill==-1)
    {
        succflag=0;
        perror("Error:");
    }
}