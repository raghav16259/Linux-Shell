#include <stdio.h>
#include <memory.h>
#include <dirent.h>
#include <zconf.h>

//
// Created by Raghav Sood on 21/01/18.
//
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
    int eflag=0;
    int nflag=0;
    int first=-1;
    char *diro[10];
    int a=0;
    for(int i=0;i<k;i++)
    {
        if (arr[i] == NULL) {
            char in[1024];
            fgets(in,1024,stdin);
            printf("%s",in);
            break;
        }
        if(first==-1 && !strcmp(arr[i], "-e"))
            eflag=1;
        else if(first==-1 && !strcmp(arr[i], "-n"))
            nflag=1;
        else if(first==-1 && !strcmp(arr[i], "-en"))
        {
            eflag=1;
            nflag=1;
        }
        else if(first==-1 && !strcmp(arr[i], "-ne"))
        {
            nflag=1;
            eflag=1;
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
                printf("cat: %s: is a directory\n",arr[i]);
            }
            else {
                if (access(arr[i], F_OK) != -1) {
                    diro[a] = arr[i];
                    a++;
                    first = 0;
                } else {
                    printf("cat: %s: No such file or directory\n", arr[i]);
                }
            }

        }
    }
    for(int j=0;j<a;j++)
    {
        FILE *stream;
        char ch;
        stream = fopen (diro[j], "r");
        ch = fgetc(stream);
        if(eflag==0 && nflag==0)
        {
            while (ch != EOF)
            {

                printf ("%c", ch);
                ch = fgetc(stream);
            }
            fclose(stream);
        }
        else if(eflag==0 && nflag==1)
        {
            int i=1;
            if(ch!=EOF)
                printf("    %d ",i);
            while (ch != EOF)
            {

                printf ("%c", ch);
                if(ch=='\n')
                {
                    i++;
                    printf("    %d ", i);
                }
                ch = fgetc(stream);
            }
            fclose(stream);
        }
        else if(eflag==1 && nflag==0)
        {
            while (ch != EOF)
            {
                if(ch=='\n')
                {
                    printf("$");
                }
                printf ("%c", ch);

                ch = fgetc(stream);
            }
            fclose(stream);
        }
        else
        {
            int i=1;
            if(ch!=EOF)
                printf("    %d ",i);
            while (ch != EOF)
            {
                if(ch=='\n')
                {
                    printf("$");
                }

                printf ("%c", ch);
                if(ch=='\n')
                {
                    i++;
                    printf("    %d ", i);
                }
                ch = fgetc(stream);
            }
            fclose(stream);
        }

    }

}