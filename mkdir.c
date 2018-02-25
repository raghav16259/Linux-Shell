//
// Created by Raghav Sood on 21/01/18.
//
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <memory.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *input=argv[0];
    char *arr[10];
    char *word;
    word = strtok(input, " ");
    arr[0]=word;
    int k=1;
    while ((word = strtok(NULL, " ")) != NULL)
    {
        arr[k]=word;
        k++;
    }
    int mflag=-1;
    int vflag=0;
    char *val;
    int first=-1;
    char *diro[10];
    int a=0;
    for(int i=0;i<k;i++)
    {
        if(arr[i]==NULL)
        {
            printf("usage: mkdir [-pv] [-m mode] directory ...\n");
            break;
        }
        if(mflag==1)
        {
            val=arr[i];
            mflag=0;
        }
        else if(first==-1 && !strcmp(arr[i], "-m"))
            mflag=1;
        else if(first==-1 && !strcmp(arr[i], "-v"))
            vflag=1;
        else if(first==-1 && !strcmp(arr[i], "-vm"))
        {
            vflag=1;
            mflag=1;
        }
        else
        {
            //printf("%s\n",arr[i]);
            //diro[0]=arr[i];
            DIR *directory = opendir(arr[i]);
            if (directory)
            {
                first=1;
            }
            else
            {
                diro[a]=arr[i];
                a++;
                first=0;
            }
            if(first==1)
            {
                printf("mkdir: %s: File exists\n",arr[i]);
            }
            if(first==1)
            first=0;

        }

    }
    for(int i=0;i<a;i++) {
        int ret=0;
        if(mflag!=-1) {
                umask(0);
                ret=mkdir(diro[i], strtoul(val,NULL,8));
                //if(!ret)
                //    perror("Invalid Mode");
                umask(022);
        }
        else
        mkdir(diro[i], 0777);
        if(vflag==1&&ret==0)
            printf("mkdir: created directory '%s'\n",diro[i]);
    }
}
