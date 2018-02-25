#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

void cd(char *str);

static const char *history[100];
static unsigned history_count = 0;

int main(int argc, char *argv[])
{
    int flag=1;
    int start=0;
    int clear=0;

    while(flag) {

        //printf("test2222\n");
        printf("Raghavs-MacBook-Pro: %s$ ",getcwd(NULL,0));
        /*FILE *fptr;
        FILE *stream;
       char ch[10];
        stream = fopen ("/Users/raghav/CLionProjects/OSAssign0/history", "r");
       while ( fgets ( ch, sizeof ch, stream ) != NULL )
        {

        }
        fclose (stream);
        char *word;
        word = strtok(ch, " ");
        int num=atoi(word);
        num++;
        char str1[10];
        sprintf(str1, "%d", num);
        strcat(str1," ");
        fptr = fopen("history", "a");

       int ret;*/
        char input[1024];
        fgets(input,1024,stdin);
        history[history_count++] = strdup(input );
        //char *temp1=input;
        //strcat(str1,temp1);
        //printf("%s",input);
        //fputs(str1,fptr);
        //fclose(fptr);

        int inputlen=strlen(input);
        //printf("%d\n",x);
        char *currdir;
        char *temp;
        int y;
        char input2[1024];
        char input3[1024];
        temp = strchr(input, ' ');
        if(temp!=NULL)
        {
            y=strlen(temp);
            temp++;
            strncpy(input3, temp, y-2);
            input3[y-2] = '\0';
            strncpy(input2, input, inputlen-y);
            input2[inputlen-y] = '\0';
            if(!strcmp(input2,"exit"))
                exit(0);
            else if(!strcmp(input2, "pwd"))
            {
                char *cwd;
                cwd = getcwd (NULL, 0);
                if(!strcmp(input3, "") || !strcmp(input3, "-P") || !strcmp(input3, "-L") || !strcmp(input3, "-L -P") || !strcmp(input3, "-P -L") || !strcmp(input3, "-LP") || !strcmp(input3, "-PL") )
                {
                    printf("%s\n",cwd);
                }
                else
                {
                    printf("pwd: %s: invalid option\n",input3);
                }
            }
            else if(!strcmp(input2, "cd"))
            {
                if(!strcmp(input3, "")||!strcmp(input3, "~")||!strcmp(input3, "~raghav")||!strcmp(input3, "~ raghav"))
                {
                    char *temp=getcwd (NULL, 0);
                    chdir("/Users/raghav");
                    currdir=temp;
                }
                else if(!strcmp(input3, "/"))
                {
                    char *temp=getcwd (NULL, 0);
                    chdir("/");
                    currdir=temp;
                }
                else if(!strcmp(input3, "-"))
                {
                    if(currdir!=NULL)
                    {
                        char *temp=getcwd (NULL, 0);
                        chdir(currdir);
                        printf("%s\n",currdir);
                        currdir=temp;
                    }
                    else
                    {
                        printf("cd: OLDPWD not set\n");
                    }
                }
                else {
                    DIR *directory = opendir(input3);
                    if (directory) {
                        char *temp=getcwd (NULL, 0);
                        chdir(input3);
                        currdir=temp;
                    }
                    else
                    {
                        printf("cd: %s: No such file or directory\n",input3);
                    }
                }
            }
            else if(!strcmp(input2, "ls"))
            {
                int cpid=fork();
                if(cpid==0)
                {
                    char *argv[2];
                    argv[0]=input3;
                    argv[1]=NULL;
                    execve("/Users/raghav/CLionProjects/OSAssign0/ls",argv,NULL);
                }
                else
                {
                    wait(NULL);
                }
            }
            else if(!strcmp(input2, "mkdir"))
            {
                int cpid=fork();
                if(cpid==0)
                {
                    char *argv[2];
                    argv[0]=input3;
                    argv[1]=NULL;
                    execve("/Users/raghav/CLionProjects/OSAssign0/mkdir",argv,NULL);
                }
                else
                {
                    wait(NULL);
                }
            }
            else if(!strcmp(input2, "rm"))
            {
                int cpid=fork();
                if(cpid==0)
                {
                    char *argv[2];
                    argv[0]=input3;
                    argv[1]=NULL;
                    execve("/Users/raghav/CLionProjects/OSAssign0/rm",argv,NULL);
                }
                else
                {
                    wait(NULL);
                }
            }
            else if(!strcmp(input2, "date"))
            {
                int cpid=fork();
                if(cpid==0)
                {
                    char *argv[2];
                    argv[0]=input3;
                    argv[1]=NULL;
                    execve("/Users/raghav/CLionProjects/OSAssign0/date",argv,NULL);
                }
                else
                {
                    wait(NULL);
                }
            }
            else if(!strcmp(input2, "cat"))
            {
                int cpid=fork();
                if(cpid==0)
                {
                    char *argv[2];
                    argv[0]=input3;
                    argv[1]=NULL;
                    execve("/Users/raghav/CLionProjects/OSAssign0/cat",argv,NULL);
                }
                else
                {
                    wait(NULL);
                }
            }
            else if(!strcmp(input2, "history"))
            {
                if(!strcmp(input3, "-c"))
                {
                    history_count=0;
                    clear=1;

                }
                else
                {
                    if(clear==0) {

                        FILE *stream;
                        char ch;
                        stream = fopen("/Users/raghav/CLionProjects/OSAssign0/history", "r");
                        ch = fgetc(stream);
                        {
                            while (ch != EOF) {

                                printf("%c", ch);
                                ch = fgetc(stream);
                            }
                            fclose(stream);
                        }
                        for (int i = 0; i < history_count; i++) {
                            printf("%d %s", i + 177, history[i]);
                        }
                    }
                    else
                    {
                        for (int i = 0; i < history_count; i++) {
                            printf("%d %s", i +1, history[i]);
                        }
                    }
                }
            }
            else if(!strcmp(input2, "echo"))
            {
                if(!strcmp(input3, ""))
                {
                    printf("Enter some text along with echo command\n");
                }
                else {
                    char *arr[10];
                    char *word;
                    word = strtok(input3, " ");
                    arr[0] = word;
                    int k = 1;
                    while ((word = strtok(NULL, " ")) != NULL) {
                        arr[k] = word;
                        k++;
                    }
                    int nflag=0;
                    int Eflag=0;
                    int first=0;
                    char *stringy[10];
                    int aa=0;
                    int count1=0;
                    int count2=0;
                    for(int i=0;i<k;i++)
                    {
                        if(first==0 && !strcmp(arr[i], "-E"))
                            Eflag=1;
                        else if(first==0 && !strcmp(arr[i], "-n"))
                            nflag=1;
                        else if(first==0 && !strcmp(arr[i], "-nE"))
                        {
                            nflag=1;
                            Eflag=1;
                        }
                        else if(first==0 && !strcmp(arr[i], "-En"))
                        {
                            Eflag=1;
                           nflag=1;
                        }
                        else
                        {
                            stringy[aa]=arr[i];
                            aa++;
                            first=1;
                        }
                    }
                    for(int i=0;i<aa;i++)
                    {
                        for(int j=0;j<strlen(stringy[i]);j++)
                        {
                            if(stringy[i][j]=='"')
                                count1++;
                            else if(stringy[i][j]=='\'')
                                count2++;
                        }
                    }
                    if(count1%2!=0 || count2%2!=0)
                    {
                        printf("Invalid quotes\n");
                        break;
                    }
                    for(int i=0;i<aa;i++) {
                        for (int j = 0; j < strlen(stringy[i]); j++) {
                            if (stringy[i][j] != '\'' && stringy[i][j] != '"')
                                printf("%c", stringy[i][j]);
                        }
                        printf(" ");
                    }
                    printf("\n");

                }

            }
            else
            {
                printf("%s: command not found\n",input2);
            }

        }
        else {
            strncpy(input2, input, inputlen - 1);
            input2[inputlen - 1] = '\0';
            if (!strcmp(input2, "exit"))
                exit(0);
            else if(!strcmp(input2, "pwd"))
            {
                char *cwd;
                cwd = getcwd (NULL, 0);
                printf("%s\n",cwd);
            }
            else if(!strcmp(input2, "cd")) {

                char *temp = getcwd(NULL, 0);
                //printf("%s",temp);
                chdir("/Users/raghav");
                //printf("test\n");
                //printf("%s\n",getcwd(NULL,0));
                currdir=temp;
            }
            else if(!strcmp(input2, "ls")) {
                int cpid=fork();
                if(cpid==0)
                {
                    execve("/Users/raghav/CLionProjects/OSAssign0/ls",NULL,NULL);
                }
                else
                {
                    wait(NULL);
                }
            }
            else if(!strcmp(input2, "mkdir")) {
                printf("usage: mkdir [-pv] [-m mode] directory ...\n");
            }
            else if(!strcmp(input2, "rm")) {
                printf("usage: rm [-f | -i] [-dPRrvW] file ... unlink file\n");
            }
            else if(!strcmp(input2, "date"))
            {
                int cpid=fork();
                if(cpid==0)
                {
                    execve("/Users/raghav/CLionProjects/OSAssign0/date",NULL,NULL);
                }
                else
                {
                    wait(NULL);
                }
            }
            else if(!strcmp(input2, "cat"))
            {
                char in[1024];
                fgets(in,1024,stdin);
                printf("%s",in);
            }
            else if(!strcmp(input2, "history"))
            {
                if(clear==0) {

                    FILE *stream;
                    char ch;
                    stream = fopen("/Users/raghav/CLionProjects/OSAssign0/history", "r");
                    ch = fgetc(stream);
                    {
                        while (ch != EOF) {

                            printf("%c", ch);
                            ch = fgetc(stream);
                        }
                        fclose(stream);
                    }
                    for (int i = 0; i < history_count; i++) {
                        printf("%d %s", i + 177, history[i]);
                    }
                }
                else
                {
                    for (int i = 0; i < history_count; i++) {
                        printf("%d %s", i +1, history[i]);
                    }
                }
            }
            else if(!strcmp(input2, "echo"))
            {
                printf("Enter some text along with echo command\n");
            }
            else
            {
                printf("%s: command not found\n",input2);
            }
            //printf("pls\n");
        }

        //CD COMMAND

        // if(strcmp(first,"cd")==0)
        //{
        //    cd(input);
        //}
    }
    return 0;
}
void cd(char *str)
{
    printf("%s",str);
}
