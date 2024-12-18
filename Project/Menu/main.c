#include <stdio.h>
#include "LoginRegister.h"
#include "struct.h"
#include <windows.h>
#include "WordBookManagement.h"
#include "MemorizeWords.h"

User users[100];
User Logined[1];
Word wordbook[10000];
Word wrongwords[10000];
Time LoginTime[100];
Time CurrentTime[100];
int TotalWords=0;
int success=0;
int Bianhao=0;

int main() {
    SetConsoleOutputCP(65001);
    int choice=0,choice2=0,choice3=0,button = 0;
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
                if (success==1) {
                    choice=0;
                }
                break;
                case 2:
                    RegisterUser();
                break;
                case 0:
                    printf("退出成功\n");
                choice=0;
                break;
                default:
                    printf("错误的输入！\n");
            }
        } while (choice != 0);
    if (success == 1)
    {
        do {
            printf("\n欢迎来到总菜单，请选择你今天想要干什么:\n");
            printf("1. 查看你的信息\n");
            printf("2. 进入单词本菜单\n");
            printf("3. 进入学习模式\n");
            printf("0. 退出登录并打卡\n");
            printf("请选择：");
            scanf("%d", &button);
            switch (button) {
                case 1:
                    printf("你的用户名为:%s\n你的密码为:%s\n你先前的总得分为%d\n你的打卡天数为:%d",
                        Logined[0].UsersName,Logined[0].Password,Logined[0].score,Logined[0].daysStudied);
                break;
                case 2:
                    button=2;
                break;
                case 3:
                    button=3;
                break;
                case 0:
                    DayPlusOne();
                    printf("退出成功,已为您打卡(一天只能打卡一次哦)\n");
                success=0;
                break;
                default:
                    printf("错误的输入！\n");
            }
            if (button==2)
            {
                do{
                    printf("\n欢迎来到单词本菜单：\n");
                    printf("1. 添加单词\n");
                    printf("2. 删除单词\n");
                    printf("3. 修改单词\n");
                    printf("4. 补充释义\n");
                    printf("5. 查看单词本\n");
                    printf("0. 退出单词本\n");
                    printf("请输入你的选项:");
                    scanf("%d", &choice2);
                    switch (choice2)
                    {
                        case 1:
                            AddWord();
                        break;
                        case 2:
                            DeleteWord();
                        break;
                        case 3:
                            ModifyWord();
                        break;
                        case 4:
                            AddMeaning();
                        break;
                        case 5:
                            ViewWords();
                        break;
                        case 0:
                            printf("退出成功\n");
                        break;
                        default:
                            printf("输入错误！\n");
                    }
                } while (choice2 != 0);
            }
                if (button==3) {
                    do
                    {
                        printf("\n欢迎来到学习页面,请选择你的学习方式:\n");
                        printf("1. 查看单词本\n");
                        printf("2. 开始学习\n");
                        printf("3. 查看成绩\n");
                        printf("4. 查看错题本\n");
                        printf("5. 复习错题\n");
                        printf("0. 返回\n");
                        printf("请输入你的选项: ");
                        scanf("%d", &choice3);
                        switch (choice3)
                        {
                            case 1:
                                ViewWords();
                            break;
                            case 2:
                                StartLearning();
                            break;
                            case 3:
                                ScoreManagement();
                            break;
                            case 4:
                                ViewWrongWords();
                            break;
                            case 5:
                                ReLearnWrongWords();
                            break;
                            case 0:
                                printf("返回成功\n");
                            break;
                            default:
                                printf("无效选项！\n");
                        }
                    }while (choice3 != 0);
                }
        } while (success != 0);
    }

}