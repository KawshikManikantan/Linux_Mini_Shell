#include "headers.h"
#include "forward.h"
#include "piping.h"
#include "redirection.h"
#include "linkedlist.h"

void forward(char* arglist[10][12],int n,int inputred,char inputstr[1000],int outputred,char outputstr[1000],node* headp,char history[20][1000],int* statusp,int* counthisp)
{
    input=dup(0);
    output=dup(1);
    if(input==-1 || output==-1)
    {
        succflag=0;
        perror("Error:");
        return;
    }
    int pipearr[2];
    int pipeinput,pipeoutput;
    // printf("%s %s",inputstr,outputstr);
    pipeinput=redirectioninit(input,inputred,inputstr);
    if(pipeinput==-1)
    {
        succflag=0;
        return;
    }
    int forkret;
    for(int i=0;i<n;i++)
    {
        int err=dup2(pipeinput,0);
        if(err==-1)
        {
            succflag=0;
            return;
        }
        close(pipeinput);
        arglist[i][atoi(arglist[i][11])]=NULL;
        
        if(i==n-1)
        {
            pipeoutput=redirectionchange(output,outputred,outputstr);
            if(pipeoutput==-1)
            {
                break;
            }
        }

        else
        {
            int er=pipe(pipearr);
            if(er==-1)
            {
                perror("Pipe Creation Error");
                break;
            }
            pipeinput=pipearr[0];
            pipeoutput=pipearr[1];
        }
        
        err=dup2(pipeoutput,1);
        if(err==-1)
        {
            succflag=0;
            return;
        }
        close(pipeoutput);
        process(i,headp,history,statusp,counthisp,arglist);
        close(pipearr[1]);
    }
    dup2(input,0);
    dup2(output,1);
    close(input);
    close(output);
}

