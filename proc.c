#include "proc.h"
#include "headers.h"
#include "echo.h"
#include "pwd.h"
#include "change.h"
#include "dirdes.h"
#include "back.h"
#include "pinfo.h"
#include "prompt.h"
#include "forward.h"
#include "linkedlist.h"
#include "hisdisplay.h"
#include "redirection.h"
#include "piping.h"
char* buffer;
char* tok;
char *sepcom[10];
char *comlist[20];
int isbackground[100];
char *cds[20][10];
char *commands[20][10][12];
char temp[10000];
char num[5];
char inputstr[1000];
char outputstr[1000];
char test[1000];
int pipearr[20][2];
int pipeinput,pipeoutput;
int input,output;

int checkendswith(char* str)
{
    long int d=strlen(str);
    for(long i=d-1;i>=0;i--)
    {
        if(str[i]!=' ' && str[i]=='&')
        {
            return 1;
        }

        else if(str[i]!=' ' && str[i]!='&')
        {
            // printf("This was found %c",str[i]);
            return 0;
        }
        
    }
}

int namgen(int p,int pos,char c)
{
    while(pos<strlen(comlist[p]) && comlist[p][pos]==' ')
    {
        pos++;
    }
    int i;
    for(i=pos;i<strlen(comlist[p]);i++)
    {
        if(comlist[p][i]!=' ')
        {
            if(c=='<')
            {
                inputstr[i-pos]=comlist[p][i];
                inputstr[i-pos+1]='\0';
                comlist[p][i]=' ';
            }
            else
            {
                outputstr[i-pos]=comlist[p][i];
                outputstr[i-pos+1]='\0';
                comlist[p][i]=' ';
            }
        }
        else
        {
            break;
        }
    }
    return i;
}
int iocheck(int p,char c)
{
    int ret=0;
    int pos=-1;
    int fl=0;
    for(int i=0;i<strlen(comlist[p]);i++)
    {
        if(fl==1 && ( comlist[p][i]!=' ' && comlist[p][i]!=c) )
        {
            fl=0;
            i=namgen(p,pos,c);
            // printf("%d %s %s",i,inputstr,outputstr);
        }

        else if(comlist[p][i]==c)
        {
            if(fl==0)
            {
                ret=1;
            }

            else
            {
                ret++;
            }
            
            fl=1;
            pos=i+1;
            comlist[p][i]=' ';   
        }
        
    }
    // printf("%d\n",pos);
    if(pos==-1)
    {
        return 0;
    }
    else
    {
        return ret;
    }   
}

void proc(char* buffer,node* headp,char history[20][1000],int* statusp,int* counthisp)
{
    // printList(*headp);
    int i=0;
    tok=strtok(buffer,";\n");
    
    while(tok!=NULL)
    {
        if(strlen(tok)!=0)
        {
            sepcom[i]=tok;
            i++;
        }
        tok=strtok(NULL,";\n");
    }
    int k=0;
    for(int j=0;j<i;j++)
    {
        strcpy(temp,sepcom[j]);
        tok=strtok(sepcom[j],"&\n");
        while(tok!=NULL)
        {
            if(strlen(tok)!=0)
            {
                comlist[k]=tok;
                isbackground[k]=1;
                // printf("%d\n",strcmp(comlist[i],"pwd"));
                k++;
            }
            tok=strtok(NULL,"&\n");
        }

        if(checkendswith(temp)==0)
        {
            isbackground[k-1]=0;
        }
    }

    //  printf("%d",k);
    
    for(int j=0;j<k;j++)
    {
        int n=0;
        int inputred=iocheck(j,'<');
        int outputred=iocheck(j,'>');
        tok=strtok(comlist[j],"|\n");
        while(tok!=NULL)
        {
            if(strlen(tok)!=0)
            {
                cds[j][n]=tok;
                // printf("%d\n",strcmp(comlist[i],"pwd"));
                n++;
            }
            tok=strtok(NULL,"|\n");
        }

        // printf("Proc:%s %s\n",inputstr,outputstr);
        int m;

        for(int z=0;z<n;z++)
        {
            m=0;
            tok=strtok(cds[j][z]," \n");
            while(tok!=NULL)
            {
                if(strlen(tok)!=0)
                {
                    commands[j][z][m]=tok;
                    // printf("%d\n",strcmp(comlist[i],"pwd"));
                    m++;
                }
                tok=strtok(NULL," \n");
            }
            // if(m!=0)
            // {
                sprintf(num,"%d",m);
                commands[j][z][11]=strdup(num);
            // }
        }
        if(isbackground[j]==1)
        {
            // printf("%s\n",commands[j][0][11]);
            back(commands[j][0],headp,inputred,inputstr,outputred,outputstr);
            // printf("%s\n","RET");
        }
        else
        {
          if(inputred>2 || outputred>2)
          {
            succflag=0;
            printf("Wrong command given");
            return;
          }

        else
        {
            // printf("%s","Hello There");
            forward(commands[j],n,inputred,inputstr,outputred,outputstr,headp,history,statusp,counthisp);   
        }

        }
    }
}

