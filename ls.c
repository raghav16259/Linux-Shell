//
// Created by Raghav Sood on 19/01/18.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <memory.h>

static int myCompare (const void * a, const void * b);
void sort(const char *arr[], int n);

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
    int aflag=0;
    int oneflag=0;
    int first=0;
    char *diro;
    for(int i=0;i<k;i++)
    {
        if(arr[i]==NULL)
            break;
        if(first==0 && !strcmp(arr[i], "-a"))
        aflag=1;
        else if(first==0 && !strcmp(arr[i], "-1"))
        oneflag=1;
        else if(first==0 && !strcmp(arr[i], "-a1"))
        {
            aflag=1;
            oneflag=1;
        }
        else if(first==0 && !strcmp(arr[i], "-1a"))
        {
            aflag=1;
            oneflag=1;
        }
        else if(first==0)
        {
            //printf("%s\n",arr[i]);
            diro=arr[i];
            DIR *directory = opendir(diro);
            if (directory)
            {
                first=1;
            }
            if(first==0)
            {
                printf("ls: %s: No such file or directory\n",arr[i]);
            }

        }
        else
        {
            printf("ls: %s: No such file or directory\n",arr[i]);
        }

    }
    char a[1000][1000];
    int i=0;
    char *cwd;
    struct dirent *entry;
    if(arr[0]==NULL || diro==NULL) {
        cwd = getcwd(NULL, 0);
    }
    else {


        cwd = diro;
        if(first==1)
        printf("%s\n", cwd);
    }

    if (!cwd) {
        perror ("getcwd");
        exit (EXIT_FAILURE);
    }
    //printf ("%s\n", cwd);
    DIR *dir;
    dir = opendir (cwd);
    errno = 0;
    while ((entry = readdir (dir)) != NULL) {

        strcpy(a[i],entry->d_name);
        //if(a[i][0]!='.')
        //printf ("%s\n", a[i]);
        i++;
    }
    const char *b[i];
    for(int j=0;j<i;j++)
        b[j]=a[j];
    sort(b,i);

    for(int j=0;j<i;j++)
    {
        //if(b[j][0]!='.')
        if(aflag==1)
        printf("%s\n", b[j]);
        else if(b[j][0]!='.')
        {
            printf("%s\n", b[j]);
        }

    }

    if (errno && !entry)
        perror ("readdir");
    //closedir (dir);
    //free (cwd);
}

static int myCompare (const void * a, const void * b)
{
    return strcmp (*(const char **) a, *(const char **) b);
}

void sort(const char *arr[], int n)
{
    qsort (arr, n, sizeof (const char *), myCompare);
}