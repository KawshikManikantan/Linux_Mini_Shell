#include "headers.h"
#include "overkill.h"
#include "linkedlist.h"
#include "piping.h"
void overkill(node* headp)
{
    while((*headp)!=NULL)
    {
       int killstat=kill((*headp)->ppid,SIGKILL);
       if(killstat==-1)
       {
           succflag=0;
           perror("Error:");
       }
    }
}