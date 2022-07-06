#include "back.h"
#include "headers.h"
#include "prompt.h"
#include "linkedlist.h"
#include "main.h"
#include "redirection.h"
#include "piping.h"
char* name;
node* gheadp;
char str[100];
struct utsname buf;
char wordir[105];
char tempstring[1000];

void back(char* arglist[12],node* headp,int inputred,char* inputstr,int outputred,char* outputstr)
{
    pid_t wpid;
    gheadp=headp;
    // printf("%s %s \n",arglist[0],arglist[11]);
    int w=atoi(arglist[11]);
    arglist[atoi(arglist[11])]=NULL;
    arglist[11]=NULL;
    // printf("%s","Back");
    // printf("%s %s\n",outputstr,inputstr);
    int forkret=fork();
    if(forkret==-1)
    {
        perror("Error: Fork Failed");
        succflag=0;
        return;
    }
    if (forkret==0)
    {
        printf("%d \n",getpid());
        setpgid(0,0);
        input=dup(0);
        output=dup(1);
        // printf("%s %s\n",outputstr,inputstr);
        int pipeinput=redirectioninit(input,inputred,inputstr);
        dup2(pipeinput,0);
        close(pipeinput);
        close(input);
        int pipeoutput=redirectionchange(output,outputred,outputstr);
        dup2(pipeoutput,1);
        close(pipeoutput);
        close(output);
        int err=execvp(arglist[0], arglist);
        if(err==-1)
        {
            perror("Error:");
            _exit(1);
        }
    }
    else
    {
        setpgid(forkret,forkret);
        strcpy(tempstring,"");
        for(int i=0;i<w;i++)
        {
            strcat(tempstring,arglist[i]);
            strcat(tempstring," ");
        }
        // printf("%s",tempstring);
        addprocess(headp,forkret,tempstring); 
        // printList(*headp);
        return;
    }
}
