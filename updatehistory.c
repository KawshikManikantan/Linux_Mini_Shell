#include "updatehistory.h"
#include "headers.h"
char strname[100000];
void updatehistory(char history[20][1000],int counthis,char addr[2005])
{
    strcat(addr,"/H.txt");
    int c=20;
    int start=counthis;;
    if(counthis<20)
    {
        c=counthis;
        start=0;
    }
    while(c>0)
    {
        strcat(strname,history[start%20]);
        strcat(strname,"\n");
        c--;
        start++;
    }
    // printf("%s",strname);
    int filnew=open(addr,O_WRONLY|O_TRUNC|O_CREAT,0777);
    if(filnew==-1)
    {
        perror("Error");
    }
    if(filnew!=-1)
    {
        int sz = write(filnew,strname,strlen(strname));
        close(filnew);
    }
}