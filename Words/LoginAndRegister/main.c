#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX 100

typedef struct {
	char UsersName[MAX];
	char Password[MAX];
	int score;
	int daysStudied;
} User;
User users[MAX];

int ReadUsersInf(char* filename,User users[]);
int Login();
int RegisterUser();
int WordBook();

int main()
{
	SetConsoleOutputCP(65001);
	int choice;
	do {
		printf("\n注册或登录:\n");
		printf("1. 登录\n");
		printf("2. 注册\n");
		printf("0. 退出\n");
		printf("请选择：");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				Login();
			break;
			case 2:
				RegisterUser();
			break;
			case 0:
				printf("退出.\n");
			break;
			default:
				printf("错误的输入！\n");
		}
	} while (choice != 0);
	return 0;
}
int Login()
{
	char filename[MAX]="D:/ClionProject/Words/TXT/users.txt";
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
			printf("登陆成功！\n");
			return i; // 返回登录的用户索引
		}
	}
	printf("用户名或密码错误!\n");
	return -1;
}

int RegisterUser()
{
	char filename[MAX]="D:/ClionProject/Words/TXT/users.txt";
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
	}// 检查用户名是否已经存在
	// 注册新用户
	strcpy(users[userCount].UsersName, username);
	strcpy(users[userCount].Password, password);
	users[userCount].score = 0;
	users[userCount].daysStudied = 0;
	// 将新用户信息写入文件
	FILE *fp = fopen("D:/ClionProject/Words/TXT/users.txt", "a"); // 打开文件以追加模式写入
	if (!fp) {
		printf("Error opening file for writing.\n");
		return -1;
	}
	// 写入用户数据到文件
	fprintf(fp, "%s %s %d %d\n", username, password, users[userCount].score, users[userCount].daysStudied);
	fclose(fp);
	printf("注册成功.\n");
	return userCount - 1; // 返回新注册用户的索引
}
int ReadUsersInf(char* fname,User Inf[])
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
		fscanf(fp,"%s%s%d%d",Inf[i].UsersName,Inf[i].Password,&Inf[i].score,&Inf[i].daysStudied);//注意格式
		i++;
	}
	fclose(fp);
	return i-1; //因为文件写入时输入格式里的换行会写入文件，最后一条记录后面会有一个空行
}
