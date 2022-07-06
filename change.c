#include "headers.h"
#include "change.h"
#include "piping.h"
struct passwd* pw ;
extern int errno;
int chang;
char temp[1005];
void change(char* add)
{
    getcwd(temp,1000);                  
    if(strcmp(add,"-")==0)
    {
        errno=0; 
        printf("%s\n",prev);
        chang=chdir(prev);
        if(chang==-1)
        {
            perror("Error:");
            succflag=0;
        }
        else
        {
            if(temp==NULL)
            {
                perror("Error:");
            }

            else
            {
                strcpy(prev,temp);
            }    
        }            
    }
    
    else if(strcmp(add,"~")==0)
    {
        // errno=0;
        // pw = getpwuid(getuid());
        // if(pw==NULL)
        // {
        //     perror("Error:");
        //     return;
        // }
        // 
        // printf("%s",tilda);
        errno=0;
        chang=chdir(tilda);
        if(chang==-1)
        {
            perror("Error:");
            succflag=0;
        }
        else
        {
            if(temp==NULL)
            {
                perror("Error:");
            }

            else
            {
                strcpy(prev,temp);
            }
        }
        
    }
    else
    {
        errno=0;
        chang=chdir(add);
        if(chang==-1)
        {
            perror("Error:");
            succflag=0;
        }
        else
        {
            if(temp==NULL)
            {
                perror("Error:");
            }

            else
            {
                strcpy(prev,temp);
            }
        }
        
    }
}