#include "headers.h"
#include "fg.h"
#include "linkedlist.h"
#include "piping.h"
char tempstring[1005];
void fg(char* arglist[12],node* headp)
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
    strcpy(tempstring,noder->name);
    
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    
    
    int kilstat=kill(processid,SIGCONT);
    if(kilstat==-1)
    {
        succflag=0;
        perror("Error:");
    }

    tcsetpgrp(0,processid);

    int status;
    waitpid(getpgid(processid), &status, WUNTRACED);
    
    tcsetpgrp(0,getpgrp());
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    deleteprocess(headp,processid);
    
    if(WIFSTOPPED(status))
    {
        succflag=0;
        printf("%d process was stopped\n",processid);
        addprocess(headp,processid,tempstring);
    }

}