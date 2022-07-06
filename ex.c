#include "headers.h"
#include "ex.h"
#include "prompt.h"
#include "linkedlist.h"
#include "piping.h"
char tempstring[1000];
void ex(int i,char* arglist[10][12],node* headp)
{
    int w=atoi(arglist[i][11]);
    int forkret=fork();

    if(forkret==-1)
    {
       succflag=0;
       perror("Error:");
       return; 
    }
    
    else if(forkret==0)
    {
        setpgid(0,0);
        int err=execvp(arglist[i][0], arglist[i]);
        if(err==-1)
        {
            succflag=0;
            perror("ExecError:");
            _exit(1);
        }   
    }

    else
    {
        setpgid(forkret,forkret);
       
        signal(SIGTTIN,SIG_IGN);
        signal(SIGTTOU,SIG_IGN);
       
        int err=tcsetpgrp(input,forkret);
        
        if(err==-1)
        {
            succflag=-1;
            perror("TTSError:");
            return;
        } 

        int status;
        waitpid(forkret,&status,WUNTRACED);
        tcsetpgrp(input,getpgrp());
        
        if(err==-1)
        {
            succflag=-1;
            perror("TTError:");
            return;
        }
        
        signal(SIGTTIN,SIG_DFL);
        signal(SIGTTOU,SIG_DFL);
        strcpy(tempstring,"");
        
        for(int j=0;j<w;j++)
        {
            strcat(tempstring,arglist[i][j]);
            strcat(tempstring," ");
        }
        
        if(WIFEXITED(status))
        {
            // printf("%s","Hey");
            // printf("%d",WEXITSTATUS(status));
            if(WEXITSTATUS(status)!=EXIT_SUCCESS)
            {
                succflag=0;
                // printf("%d",succflag);
            }
        }
        
        else if(WIFSTOPPED(status))
        {
            succflag=0;
            printf("%d process was stopped\n",forkret);
            addprocess(headp,forkret,tempstring);
        }
    }
}