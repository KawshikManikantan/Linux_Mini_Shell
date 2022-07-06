#include "echo.h"
#include "headers.h"

void echo(char* comlist[100],int j)
{
    for(int i=1;i<j;i++)
    {
        if(i!=j-1)
        {
            printf("%s ",comlist[i]);
        }
        else
        {
            printf("%s",comlist[i]);
        }
    }
    printf("%s","\n");
}