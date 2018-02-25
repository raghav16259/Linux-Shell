//
// Created by Raghav Sood on 21/01/18.
//

#include <stdio.h>
#include <memory.h>
#include <dirent.h>
#include <zconf.h>

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
    int vflag=0;
    int iflag=0;
    int first=-1;
    char *diro[10];
    int a=0;
    for(int i=0;i<k;i++)
    {
        if (arr[i] == NULL) {
            printf("usage: rm [-f | -i] [-dPRrvW] file ... unlink file\n");
            break;
        }
        if(first==-1 && !strcmp(arr[i], "-v"))
            vflag=1;
        else if(first==-1 && !strcmp(arr[i], "-i"))
            iflag=1;
        else if(first==-1 && !strcmp(arr[i], "-vi"))
        {
            vflag=1;
            iflag=1;
        }
        else if(first==-1 && !strcmp(arr[i], "-iv"))
        {
            vflag=1;
            iflag=1;
        }
        else
        {
            //printf("%s\n",arr[i]);
            //diro=arr[i];
            int dir=0;
            DIR *directory = opendir(arr[i]);
            if (directory)
            {
                dir=1;
            }
            if(dir==1)
            {
                printf("rm: %s: is a directory\n",arr[i]);
            }
            else {
                if (access(arr[i], F_OK) != -1) {
                    diro[a] = arr[i];
                    a++;
                    first = 0;
                } else {
                    printf("rm: %s: No such file or directory\n", arr[i]);
                }
            }

        }
    }
    for(int i=0;i<a;i++) {
        if(iflag==1) {
            char ch;
            printf("remove %s ? \n",diro[i]);
            scanf(" %c", &ch);
            if(ch=='y') {
                remove(diro[i]);
                if(vflag==1)
                    printf("%s\n",diro[i]);
            }
        }
        else {
            remove(diro[i]);
            if (vflag == 1)
                printf("%s\n", diro[i]);
        }
    }
}
