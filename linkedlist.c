#include "headers.h"
#include "linkedlist.h"
#include "pinfo.h"
#include "piping.h"
char* toprint[100];
char* deleteprocess(node* headp,pid_t pid)
{
    if(*headp==NULL)
    {
        return NULL;
    }

    node prev=NULL;
    node temp=*headp;
    char* tempo;
    tempo=(char *)malloc(100*sizeof(char));
    if (temp->ppid == pid) 
    { 
        *headp = temp->next;
        strcpy(tempo,temp->name);   
        free(temp); 
        numprocess--;   
        // siz--;           
        return tempo; 
    } 

    while(temp!=NULL && temp->ppid!=pid)
    {
        prev=temp;
        temp=temp->next;
    }

    if(temp!=NULL)
    {
        prev->next=temp->next;
        strcpy(tempo,temp->name); 
        free(temp);
        numprocess--;
        // siz--;
        return tempo;
    }

    else
    {
        return NULL;
    }
    
}

void addprocess(node* headp,pid_t pid,char* name)
{
    // printf("%s",name);
    node temp= (node)malloc(sizeof(struct Node));
    strcpy(temp->name,name);
    temp->ppid=pid;
    temp->next=*headp;
    *headp=temp;
    numprocess++;
    // siz++;
}

void printList(node noder) 
{ 
    // printf("%d",numprocess);
    int temp=numprocess;
    char str[20][500];
    while (noder != NULL) 
    {
        char stat[100];
        char p[10];
        strcpy(p,getstatus(noder->ppid));
        if(p==NULL)
        {
            succflag=0;
            return;
        }
        // printf("%s",p);
        if(strcmp(p,"R")==0)
        {
          strcpy(stat,"Running");
        }
        
        else if(strcmp(p,"S")==0)
        {
            strcpy(stat,"Running");
        }

        else if(strcmp(p,"T")==0)
        {
            strcpy(stat,"Stopped");
        }

        sprintf(str[temp-1],"[%d] %s %s [%d] ",temp,stat,noder->name,noder->ppid);
        noder = noder->next; 
        temp--;
    } 
    for(int i=0;i<numprocess;i++)
    {
        printf("%s\n",str[i]);
    }
} 

void deleteList(node* headp)
{
    // printList(*headp);
    while((*headp)!=NULL)
    {
       int killstat=kill((*headp)->ppid,SIGKILL);
       if(killstat==-1)
       {
           succflag=0;
           perror("Error:");
       }
        *headp=(*headp)->next;
    }
}