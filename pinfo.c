#include "pinfo.h"
#include "headers.h"
#include "piping.h"
char str[100];
char buf[2005];
char sep[100][100];
char exe[1005];
char exereal[1005];
char* temp[100];
char* ret;
char pp[100];
void pinfo(char* arglist[100],int m,int k)
{
    pid_t pid;
    if(m==1)
    {
        pid=getpid();
        sprintf(str,"/proc/%d/stat",pid);
        sprintf(exe,"/proc/%d/exe",pid);
    }
    else
    {
        sprintf(str,"/proc/%s/stat",arglist[1]);
        sprintf(exe,"/proc/%s/exe",arglist[1]);
    }

    int openfilnew=open(str,O_RDONLY);
    if(openfilnew==-1)
    {
        succflag=0;
        perror("Error:");
        return;
    }
    int ex=readlink(exe,exereal,1000);
    // printf("%d",ex);
    exereal[ex]='\0';
    // printf("%s",exe);
    if(ex==-1)
    {
        perror("Lnk Error:");
    }
    int sz=read(openfilnew, buf, 2000);
    if(sz==-1)
    {
        perror("Error:");
        return;
    }
    int i=0;
    char* tok=strtok(buf," \n");
    while(tok!=NULL)
    {
        if(strlen(tok)!=0)
        {
            strcpy(sep[i],tok);
            // printf("%d\n",strcmp(comlist[i],"pwd"));
            i++;
        }
        tok=strtok(NULL," \n");
    }
    // for(int j=0;j<i;j++)
    // {
    //     printf("%s ",sep[j]);
    // }
    if(k==1)
    {
        printf(" pid -- %s \n Process Status -- %s \n memory -- %s \n Executable Path-- %s \n",sep[0],sep[2],sep[22],exereal);
    }
}

char* getstatus(int proid)
{
    // printf("%d",proid);
    temp[0]="pinfo";
    sprintf(pp,"%d",proid);
    temp[1]=pp;
    pinfo(temp,2,0);
    ret=sep[2];
    // printf("%s",ret);
    return ret;
}