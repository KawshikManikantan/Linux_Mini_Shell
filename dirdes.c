#include "headers.h"
#include "dirdes.h"
#include "change.h"
#include "piping.h"
extern int errno;
DIR *dir;
struct dirent *file;
struct stat filedet;
struct passwd *password;
struct group *group;
extern int errno;
struct tm *timeinfo;
char timer[50];
char fulladdress[2000];
char filenamegen[100];
void lsimp(char* filename,char *name, int b)
{
    if (!((b == 0) && (filename[0] == '.')))
    {
        int err=stat(name, &filedet);
        if(err==-1)
        {
            succflag=0;
            perror("PError:");
        }
        else
        {
            printf(!(S_ISDIR(filedet.st_mode)) ? "-" : "d");
            printf(!(filedet.st_mode & S_IRUSR) ? "-" : "r");
            printf(!(filedet.st_mode & S_IWUSR) ? "-" : "w");
            printf(!(filedet.st_mode & S_IXUSR) ? "-" : "x");
            printf(!(filedet.st_mode & S_IRGRP) ? "-" : "r");
            printf(!(filedet.st_mode & S_IWGRP) ? "-" : "w");
            printf(!(filedet.st_mode & S_IXGRP) ? "-" : "x");
            printf(!(filedet.st_mode & S_IROTH) ? "-" : "r");
            printf(!(filedet.st_mode & S_IWOTH) ? "-" : "w");
            printf(!(filedet.st_mode & S_IXOTH) ? "" : "x");
            printf(" %ld", filedet.st_nlink);
            if ((password = getpwuid(filedet.st_uid)) != NULL)
                printf(" %-8.8s", password->pw_name);
            else
                printf(" %-8d", filedet.st_uid);
            if ((group = getgrgid(filedet.st_gid)) != NULL)
                printf(" %-8.8s", group->gr_name);
            else
                printf(" %-8d", filedet.st_gid);
            printf(" %ld", filedet.st_size);
            timeinfo = localtime(&(filedet.st_mtime));
            strftime(timer, 20, "%b %d %H:%M", timeinfo);
            printf(" %s", timer);
            printf(" %s\n", filename);
        }
    }
}
void dirdes(char* comlist[100], int j)
{
    int l = 0;
    int a = 0;
    // printf("%d\n",j);
    // if (j == 1)
    // {
    //     j++;
    //     strcpy(comlist[1], ".");
    // }
    // printf("%d\n",j);
    // printf("%s",comlist[j-1]);
    int flag = 0;

    for (int i = 1; i < j; i++)
    {
        if (comlist[i][0] == '-')
        {
            if (strcmp(comlist[i], "-la") == 0 || strcmp(comlist[i], "-al") == 0)
            {
                l = 1;
                a = 1;
            }
            else if (strcmp(comlist[i], "-l") == 0)
            {
                l = 1;
            }
            else if (strcmp(comlist[i], "-a") == 0)
            {
                a = 1;
            }
            else
            {
                printf("%s","Un-Recognised Format Specified \n");
                succflag=0;
                return;
            }
        }
    }
    // printf("%d %d",l,a);
    // printf("ONce: %s\n",comlist[2]);
    for(int i=1;i<j;i++)
    {
        // printf("%s \n",comlist[i]);
        if (strcmp(comlist[i], "~") == 0)
        {
            // errno=0;
            // password = getpwuid(getuid());
            // if(password==NULL)
            // {
            //     perror("Error:");
            //     continue;
            // }
            // printf("Twice %s \n",comlist[2]);
            // printf("%s",password->pw_dir);
            comlist[i]=strdup(tilda);  
            // printf("Twice %s \n",comlist[2]);
        }

        if(!(comlist[i][0] == '-'))
        {
            flag = 1;
            errno=0;
            // printf("%d Printing COmlist: %s\n",i,comlist[i]);
            dir = opendir(comlist[i]);

            if(dir==NULL)
            {
                succflag=0;
                perror("Error:");
                continue;
            }

            else
            {
                errno=0;
                printf("%s: \n", comlist[i]);

                file = readdir(dir);

                if(file==NULL && errno==-1)
                {
                    succflag=0;
                    perror("Error:");
                    continue;
                }
                // printf("%s \n","fil read success");
                if (l == 0)
                {
                    while (file != NULL)
                    {
                        if (a == 1)
                        {
                            printf("%s ", file->d_name);
                        }
                        else
                        {
                            if ((file->d_name)[0] != '.')
                            {
                                printf("%s ", file->d_name);
                            }
                        }
                        file = readdir(dir);
                    }
                    printf("%c", '\n');
                }
                else
                {
                    while (file != NULL)
                    {
                        strcpy(fulladdress,"");
                        strcat(fulladdress,comlist[i]);
                        strcat(fulladdress,"/");
                        strcat(fulladdress,file->d_name);
                        // printf("%s \n",fulladdress);
                        lsimp(file->d_name,fulladdress, a);
                        file = readdir(dir);
                    }
                }
                closedir(dir);
            }

        }
    }

    if(flag==0)
    {
        errno=0;
        dir = opendir(".");
        if(dir==NULL)
        {
            succflag=0;
            perror("Error:");
            return;
        }
        printf("%s: \n",".");
        errno=0;
        file = readdir(dir);
        if(file==0 && errno==-1)
        {
            succflag=0;
            perror("Error:");
            return;
        }
            // printf("%s \n","fil read success");
            if (l == 0)
            {
                while (file != NULL)
                {
                    if (a == 1)
                    {
                        printf("%s ", file->d_name);
                    }
                    else
                    {
                        if ((file->d_name)[0] != '.')
                        {
                            printf("%s ", file->d_name);
                        }
                    }
                    file = readdir(dir);
                }
                printf("%c", '\n');
            }
            else
            {
                while (file != NULL)
                {
                    lsimp(file->d_name,file->d_name, a);
                    file = readdir(dir);
                }
            }
            closedir(dir);
    }
}