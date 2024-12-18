#include "LoginRegister.h"
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include <time.h>
int ReadTime(char* fname,Time time[]);
int ReadUsersInf(char* filename,User users[]);
int Login();
int RegisterUser();
void DayPlusOne();


extern Time LoginTime[1];
extern Time CurrentTime[100000];
extern User users[MAX];
extern User Logined[1];
extern int success;
extern int Bianhao;

char TimeLocation[100];
int Login()
{
    char filename[MAX]="D:/ClionProject/Project/Users/users.txt";
    int UserCount=ReadUsersInf(filename, users);
    char username[MAX], password[MAX];
    printf("请输入你的用户名: ");
    scanf("%s", username);
    printf("请输入你的密码: ");
    scanf("%s", password);
    for (int i = 0; i < UserCount; i++)
    {
        if (strcmp(users[i].UsersName, username) == 0 && strcmp(users[i].Password, password) == 0)
        {
            printf("登陆成功,您的信息已录入！\n");
            success = 1;
            Bianhao=i;
            strcpy(Logined[0].UsersName,users[i].UsersName);
            strcpy(Logined[0].Password,users[i].Password);
            Logined[0].score=users[i].score;
            Logined[0].daysStudied=users[i].daysStudied;
            time_t rawtime;
            struct tm * timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            LoginTime[0].year = timeinfo->tm_year + 1900;
            LoginTime[0].month = timeinfo->tm_mon + 1;
            LoginTime[0].day = timeinfo->tm_mday;
            char str1[]="D:/ClionProject/Project/LoginingTimeList/";
            char str2[]=".txt";
            char temp0[100];
            char temp1[100];
            strcpy(temp1,Logined[0].UsersName);
            strcat(temp1,str2);
            strcpy(temp0,temp1);
            strcpy(TimeLocation, strcat(str1,temp0));
            FILE *fp = fopen(TimeLocation, "a");
            fprintf(fp, "%d %d %d\n", LoginTime[0].year,LoginTime[0].month,LoginTime[0].day);
            fclose(fp);
            return i;
        }
    }
    printf("用户名或密码错误!\n");
    return -1;
}

int RegisterUser()
{
    char filename[MAX]="D:/ClionProject/Project/Users/users.txt";
    int userCount=ReadUsersInf(filename, users);
    char username[MAX], password[MAX];
    printf("请输入你的用户名: ");
    scanf("%s", username);
    printf("请输入你的密码: ");
    scanf("%s", password);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].UsersName, username)==0)
        {
            printf("该用户名已存在！\n");
            return -1;
        }
    }
    strcpy(users[userCount].UsersName, username);
    strcpy(users[userCount].Password, password);
    users[userCount].score = 0;
    users[userCount].daysStudied = 0;
    FILE *fp = fopen("D:/ClionProject/Project/Users/users.txt", "a");
    if (!fp) {
        printf("Error opening file for writing.\n");
        return -1;
    }
    fprintf(fp, "%s %s %d %d\n", username, password, users[userCount].score, users[userCount].daysStudied);
    fclose(fp);
    printf("注册成功,同时已为你创建错题本.\n");//录入信息
    char str1[]="D:/ClionProject/Project/WrongWordList/";
    char str2[]=".txt";
    char location[100];
    strcpy(location, strcat(str1, strcat(username,str2)));
    FILE *fp1 = fopen(location, "w");
    if (!fp1) {
        return -1;
    }
    char str3[]="D:/ClionProject/Project/LoginingTimeList/";
    char location1[100];
    strcpy(location1, strcat(str3, username));
    FILE *fp2 = fopen(location1, "w");
    if (!fp2) {
        printf("已为你创建登录系统时间表\n");
        return -1;
    }
    return userCount - 1;
}

int ReadUsersInf(char* fname,User Information[])
{
    FILE *fp;
    int i=0;
    fp=fopen(fname,"r");
    if(!fp)
    {
        printf("There is no files to read\n");
        return 0;
    }
    while(!feof(fp))//文件位置指针未到结束标志
    {
        fscanf(fp,"%s %s %d %d",Information[i].UsersName,Information[i].Password,&Information[i].score,&Information[i].daysStudied);//注意格式
        i++;
    }
    fclose(fp);
    return i-1; //因为文件写入时输入格式里的换行会写入文件，最后一条记录后面会有一个空行
}

int ReadTime(char* fname,Time time[])
{
    FILE *fp;
    int i=0;
    fp=fopen(fname,"r");
    if(!fp)
    {
        printf("There is no files to read\n");
        return 0;
    }
    while(!feof(fp))//文件位置指针未到结束标志
    {
        fscanf(fp,"%d %d %d",&time[i].year,&time[i].month,&time[i].day);//注意格式
        i++;
    }
    fclose(fp);
    return i-2; //因为文件写入时输入格式里的换行会写入文件，最后一条记录后面会有一个空行
}

void DayPlusOne()
{
    char filename[MAX]="D:/ClionProject/Project/Users/users.txt";
    int UserCount=ReadUsersInf(filename, users);
    int TimeCount=ReadTime(TimeLocation, CurrentTime);
    for (int i = 0; i < UserCount; i++)
    {
        if (!strcmp(users[i].UsersName, Logined[0].UsersName))
        {
                if (CurrentTime[TimeCount].year !=CurrentTime[TimeCount-1].year || CurrentTime[TimeCount].month
                    !=CurrentTime[TimeCount-1].month || CurrentTime[TimeCount].day !=CurrentTime[TimeCount-1].day)
                {
                    users[i].daysStudied+=1;
                }
        }
    }
    FILE *fp = fopen("D:/ClionProject/Project/Users/users.txt", "w"); // 打开文件以追加模式写入
    for (int i = 0; i < UserCount; i++)
        {
        fprintf(fp,"%s %s %d %d \n",users[i].UsersName,users[i].Password,users[i].score,users[i].daysStudied);
    }
}