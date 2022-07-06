#include "headers.h"
#include "echo.h"
#include "pwd.h"
#include "change.h"
#include "dirdes.h"
#include "back.h"
#include "pinfo.h"
#include "prompt.h"
#include "linkedlist.h"
#include "hisdisplay.h"
#include "redirection.h"
#include "piping.h"
#include "ex.h"
#include "fg.h"
#include "bg.h"
#include "kjob.h"
#include "env.h"
#include "overkill.h"
void process(int i,node* headp,char *history[20],int* statusp,int* counthisp,char* arglist[10][12])
{
    succflag=1;
    int m=atoi(arglist[i][11]);
    // printf("%s",arglist[i][11]);
    if(strcmp(arglist[i][0],"pwd")==0)
    {
        pwd();
    }

    else if(strcmp(arglist[i][0],"echo")==0)
    {
        echo(arglist[i],m);
    }

    else if(strcmp(arglist[i][0],"cd")==0)
    {
        if(m<=2 && m>1)
        {
            change(arglist[i][1],m);
        }
        else
        {
            printf("%s","Large/Small Number Of Arguments Given \n");
        }
        
    }

    else if(strcmp(arglist[i][0],"ls")==0)
    {
        // printf("%d",m);
        dirdes(arglist[i],m);
    }

    else if(strcmp(arglist[i][0],"pinfo")==0)
    {
        pinfo(arglist[i],m,1);
    }
    
    // else if(strcmp(arglist[0],"pinfo")==0)
    // {
    //     nightwat(arglist,m);
    // }
    
    else if(strcmp(arglist[i][0],"history")==0)
    {
        hisdisplay(arglist[i],m,history,counthisp);
    }

    else if (strcmp(arglist[i][0],"quit")==0)
    {
        // printf("%s","Is this being recognized?");
        *statusp=0;
    }

    else if(strcmp(arglist[i][0],"overkill")==0)
    {
        // printf("%s","Is this being recognized?");
        overkill(headp);
    }

    else if (strcmp(arglist[i][0],"jobs")==0)
    {
        printList(*headp);
    }

    else if (strcmp(arglist[i][0],"fg")==0)
    {
        fg(arglist[i],headp);
    }

    else if (strcmp(arglist[i][0],"bg")==0)
    {
        bg(arglist[i],headp);
    }

    else if(strcmp(arglist[i][0],"kjob")==0)
    {
        kjob(arglist[i],headp);
    }

    else if(strcmp(arglist[i][0],"setenv")==0)
    {
        env(arglist[i]);
    }

    else if(strcmp(arglist[i][0],"unsetenv")==0)
    {
        unenv(arglist[i]);
    }

    else if(strcmp(arglist[i][0],"getenv")==0)
    {
        genv(arglist[i]);
    }
    
    else
    {
        ex(i,arglist,headp);
    }

}