#include "headers.h"
#include "hisdisplay.h"
#include "piping.h"
void hisdisplay(char* comlist[100], int j,char history[20][1000],int* counthisp)
{
    // printf("%d\n",*counthisp);
    if(j>=3)
    {
        printf("%s","Wrong Arguments Given\n");
        succflag=0;
        return;
    }
    else
    {
        if(j==2)
        {
            int req=atoi(comlist[1]);
            if(req>10)
            {
                printf("%s","Too Large A Number --- Max 10\n");
                succflag=0;
                return;
            }
            else
            {
                if(req>*counthisp)
                {
                   printf("Too Large A Number --- Max %d\n",*counthisp+1);   
                   succflag=0;
                    return;
                }
                else
                {
                    int start;
                    int end;
                    // printf("%d",*counthisp);
                    start=*counthisp-1;
                    end=*counthisp-req-1;
                    while(start>end)
                    {
                        printf("%s \n",history[start%20]);
                        start--;
                    }
                }
            }
        }
        else
        {
           int num;
           int temp=*counthisp-1;
           if(*counthisp<10)
           {
               num=*counthisp;
           } 
           else
           {
               num=10;
           }
        //    printf("%d",*counthisp);
           while(num>0)
           {
               printf("%s \n",history[temp%20]);
               temp--;
               num--;
           }
        }
        
    }
    
}
