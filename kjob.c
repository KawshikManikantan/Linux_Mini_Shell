#include "kjob.h"
#include "headers.h"
#include "linkedlist.h"
#include "piping.h"
void kjob(char* arglist[12],node* headp)
{
    node noder=*headp;
    if(atoi(arglist[11])!=3)
    {
        succflag=0;
        printf("%s","Wrong number of Arguments\n");
        return;
    }
    int num=atoi(arglist[1]);
    int sig=atoi(arglist[2]);
    if(num > numprocess || num<=0)
    {
        succflag=0;
        printf("%s","Not available- Too large/small\n");
        return;
    }

    for(int i=1;i<numprocess-num+1;i++)
    {
        noder=noder->next;
    }

    pid_t processid=noder->ppid;
    // printf("%d %d %d\n",num,sig,processid);
    int killstat=kill(processid,sig);
    if(killstat==-1)
    {
        succflag=0;
        return;
    }
}