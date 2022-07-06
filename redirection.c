#include "headers.h"
#include "redirection.h"
#include "piping.h"
int redirectioninit(int input,int inputred,char inputstr[1000])
{
    int pipeinput,pipeoutput;
    if(inputred==0)
    {
        pipeinput=dup(input);
    }
    else
    {
        int inputfile=open(inputstr,O_RDONLY);
        if(inputfile==-1)
        {
            succflag=0;
            perror("Error:");
            return -1;
        }
        else
        {
            pipeinput=inputfile;
            // close(inputfile);
        }
    } 
    return pipeinput;
}

int redirectionchange(int output,int outputred,char outputstr[1000])
{
    int pipeoutput;
    if(outputred!=0)
    {
        int outputfile;
        if(outputred==1)
        {
            outputfile=open(outputstr,O_CREAT|O_TRUNC|O_WRONLY,0644);
        }

        else if(outputred==2)
        {
            outputfile=open(outputstr,O_CREAT|O_WRONLY|O_APPEND,0644);
        }
        
        if(outputfile==-1)
        {
            succflag=0;
            perror("Error: Could not open outputfile ");
            return -1;
        }
        else
        {
            pipeoutput=outputfile;
            // close(outputfile);
        }
    }
    else
    {
        pipeoutput=dup(output);
    }    
    return pipeoutput;
}