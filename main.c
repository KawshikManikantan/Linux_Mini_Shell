#include "prompt.h"
#include "proc.h"
#include "headers.h"
#include "linkedlist.h"
#include "updatehistory.h"
#include "change.h"
#include "piping.h"
#include "overkill.h"
size_t BUFFER_SIZE=10000;
char temporary[10000];
char historystore[10000];
char hisstr[10005];
char addr[2005];
char* buffer;
char history[20][1000];
int counthis=0;
int status=1;
int numprocess=0;
int shellid=0;
char* tilda;
char* prev;
int succflag=1;
int input=0;
int output=0;
node head;
void childhandler(int sig)
{
    int status;
    pid_t pid=waitpid(-1, &status, WNOHANG|WUNTRACED);
    while(pid>0)
    {
        char* name=deleteprocess(&head,pid);
        if(name==NULL)
        {
            return;
        }

        if ( WIFEXITED(status) ) 
        {
            fprintf(stderr,"\n %s with pid %d %s\n",name,pid,"exited normally");
            prompt();
            fflush(stdout);
        }

        else if( WIFSIGNALED(status)==1)
        {
            fprintf(stderr,"\n %s with pid %d %s\n",name,pid,"exited abruptly");
            prompt();
            fflush(stdout);
        }

        else if(WIFSTOPPED(status)==1)
        {
            fprintf(stderr,"\n %s with pid %d %s \n",name,pid,"was stopped");
            addprocess(&head,pid,name);
            prompt();
            fflush(stdout);
        }   
        pid=waitpid(-1, &status, WNOHANG|WUNTRACED);      
    }
}
int main()
{
    shellid=getpid();
    errno=0;
    tilda = (char *)malloc(1005* sizeof(char));
    prev= (char *)malloc(1005* sizeof(char));
    getcwd(tilda,1000);
    if(tilda==NULL)
    {
        perror("Error:");
    }
    // printf("%s",tilda);
    strcpy(prev,tilda);
    signal(SIGINT,ctrlchandler);
    signal(SIGTSTP,ctrlzhandler);
    signal(SIGCHLD, childhandler);
    head=NULL;
    buffer = (char *)malloc(BUFFER_SIZE* sizeof(char));
    long long int filnew=open("H.txt",O_RDONLY);
    getcwd(addr,1000);
    if(filnew!=-1)
    {
        read(filnew, hisstr, 10000);
        char *tok=strtok(hisstr,"\n");
        while(tok!=NULL)
        {
            if(strlen(tok)!=0)
            {
                strcpy(history[counthis],tok);
                counthis++;
            }
            tok=strtok(NULL,"\n");
        }
        close(filnew);
        // for(int i=0;i<counthis;i++)
        // {
        //     printf("%s",history[i]);
        // }
    }
    while (status)
    {
        prompt(0);
        int sz=getline(&buffer,&BUFFER_SIZE,stdin);
        succflag=1;
        if(sz==-1)
        {
            status=0;
            printf("%c",'\n');
            continue;
        }
        buffer[sz-1]='\0';
        strcpy(temporary,buffer);
        strcpy(historystore,"");
        char *tok=strtok(temporary," \n");
        while(tok!=NULL)
        {
            if(strlen(tok)!=0)
            {
                strcat(historystore,tok);
                strcat(historystore," ");
            }
            tok=strtok(NULL," \n");
        }

        // printf("String: %s %ld\n",historystore,strlen(historystore));
        if(strlen(historystore)!=0)
        {
            strcpy(history[(counthis)%20],historystore);
            counthis=(counthis)+1;
            proc(buffer,&head,history,&status,&counthis); 
        }  
    }

    if(status==0)
    {
        updatehistory(history,counthis,addr);
        overkill(&head);
    }
}


