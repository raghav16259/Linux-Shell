//
// Created by Raghav Sood on 19/01/18.
//
#include <time.h>
#include <stdio.h>
#include <memory.h>

int main(int argc, char *argv[]) {
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
    int uflag=0;
    int Rflag=0;
    for(int i=0;i<k;i++)
    {
        if(arr[i]==NULL)
            break;
        if(!strcmp(arr[i], "-u"))
        {
            uflag=1;
        }
        else if(!strcmp(arr[i], "-R"))
        {
            Rflag=1;
        }
        else if(!strcmp(arr[i], "-uR"))
        {
            uflag=1;
            Rflag=1;
        }
        else if(!strcmp(arr[i], "-Ru"))
        {
            uflag=1;
            Rflag=1;
        }
    }
    time_t t = time(NULL);
    struct tm tm;
    if(uflag==0)
    tm = *localtime(&t);
    else
    tm = *gmtime(&t);
    char *wday;
    char *mon;
    char hour1[10];
    char min1[10];
    char sec1[10];
    //printf("%d\n",tm.tm_mon);
    switch (tm.tm_wday)
    {
        case 1:
            wday="Mon";
            break;
        case 2:
            wday="Tue";
            break;
        case 3:
            wday="Wed";
            break;
        case 4:
            wday="Thu";
            break;
        case 5:
            wday="Fri";
            break;
        case 6:
            wday="Sat";
            break;
        case 7:
            wday="Sun";
            break;
        default:
            break;
    }
    switch (tm.tm_mon)
    {
        case 0:
            mon="Jan";
            break;
        case 1:
            mon="Feb";
            break;
        case 2:
            mon="Mar";
            break;
        case 3:
            mon="Apr";
            break;
        case 4:
            mon="May";
            break;
        case 5:
            mon="Jun";
            break;
        case 6:
            mon="Jul";
            break;
        case 7:
            mon="Aug";
            break;
        case 8:
            mon="Sep";
            break;
        case 9:
            mon="Oct";
            break;
        case 10:
            mon="Nov";
            break;
        case 11:
            mon="Dec";
            break;
        default:
            break;
    }
    int a=tm.tm_hour;
    int b=tm.tm_min;
    int c=tm.tm_sec;
    sprintf(hour1,"%d",a);
    sprintf(min1,"%d",b);
    sprintf(sec1,"%d",c);
    char hour[3]="0";
    char min[3]="0";
    char sec[3]="0";
    if(a<10)
        strcat(hour,hour1);
    else {
        hour[0] = hour1[0];
        hour[1] = hour1[1];
        hour[2] = '\0';
    }
    if(b<10)
        strcat(min,min1);
    else {
        min[0] = min1[0];
        min[1] = min1[1];
        min[2] = '\0';
    }
    if(c<10)
        strcat(sec,sec1);
    else {
        sec[0] = sec1[0];
        sec[1] = sec1[1];
        sec[2] = '\0';
    }
    //printf("%s\n",hour1);
    if(Rflag==0)
    printf("%s %s %d %s:%s:%s %s %d\n",wday,mon,tm.tm_mday,hour,min,sec,tm.tm_zone,tm.tm_year+1900);
    else
    {
        time_t cur=time(NULL);
        struct tm *tm1;
        if(uflag==0)
               tm1 =localtime(&cur);
        else
            tm1 =gmtime(&cur);
       char str[100];
        strftime(str,100,"%z",tm1);
        if(uflag==0)
        printf("%s, %d %s %d %s:%s:%s %s\n", wday, tm.tm_mday, mon, tm.tm_year + 1900, hour, min, sec,str);
        else
            printf("%s, %d %s %d %s:%s:%s +0000\n", wday, tm.tm_mday, mon, tm.tm_year + 1900, hour, min, sec);
    }
    //printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return 0;
}