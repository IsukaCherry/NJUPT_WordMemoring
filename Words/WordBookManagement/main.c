#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX 1000
typedef struct {
    char word[100];
    char partOfSpeech[100];
    char meaning[1000];
} Word;

// 全局变量：单词库
Word wordbook[10000];

int ReadWordBook(char* fname,Word word[]);
void AddWord();
void DeleteWord();
void ModifyWord();
void AddMeaning();
void ViewWords();

int main()
{
    SetConsoleOutputCP(65001);
    int choice;
    do
    {
        printf("\n欢迎来到单词本菜单：\n");
        printf("1. 添加单词\n");
        printf("2. 删除单词\n");
        printf("3. 修改单词\n");
        printf("4. 补充释义\n");
        printf("5. 查看单词本\n");
        printf("0. 退出单词本\n");
        printf("请输入你的选项:");
        scanf("%d", &choice);
        switch (choice)
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
    } while (choice != 0);
        return 0;
}

int ReadWordBook(char* fname,Word wordbook[])
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
        fscanf(fp,"%s %s %s",wordbook[i].word,wordbook[i].partOfSpeech,wordbook[i].meaning);//注意格式
        i++;
    }
    fclose(fp);
    return i-1; //因为文件写入时输入格式里的换行会写入文件，最后一条记录后面会有一个空行
}

void AddWord()
{
    char filename[MAX]="D:/ClionProject/Words/TXT/wordbook.txt";
    char word[MAX], partOfSpeech[MAX],meaning[MAX];
    int Number;
    int WordCount=ReadWordBook(filename, wordbook);
    printf("请输入你想添加的单词数:");
    scanf("%d",&Number);
    for (int i = WordCount; i < WordCount+Number; i++)
    {
        printf("请输入单词的英文:");
        scanf("%s",word);

        printf("请输入词性:");
        scanf("%s", partOfSpeech);

        printf("请输入解释");
        scanf(" %[^\n]", meaning);  // 允许输入包含空格的字符串
        strcpy(wordbook[WordCount].word, word);
        strcpy(wordbook[WordCount].partOfSpeech, partOfSpeech);
        strcpy(wordbook[WordCount].meaning,meaning );
        FILE *fp = fopen("D:/ClionProject/Words/TXT/wordbook.txt", "a"); // 打开文件以追加模式写入
        if (!fp)
        {
            printf("Error opening file for writing.\n");
        }
        // 写入用户数据到文件
        fprintf(fp, "%s %s %s\n", word, partOfSpeech, meaning);
        fclose(fp);
        printf("Add successfully.\n");
    }
}

void DeleteWord()
{
    char filename[MAX]="D:/ClionProject/Words/TXT/wordbook.txt";
    char Delete[MAX];
    int WordCount=ReadWordBook(filename, wordbook);
    printf("请输入你想删除的单词");
    scanf("%s", Delete);
    for (int i = 0; i < WordCount; i++)
    {
        if (strcmp(wordbook[i].word, Delete)==0)
        {
            for (int j = i; j < WordCount - 1; j++)
            {
                strcpy(wordbook[j].word,wordbook[j + 1].word);
                strcpy(wordbook[j].partOfSpeech,wordbook[j + 1].partOfSpeech);
                strcpy(wordbook[j].meaning,wordbook[j + 1].meaning);
            }
            WordCount--;
            break;
        }
    }
    FILE *fp = fopen("D:/ClionProject/Words/TXT/wordbook.txt", "w");
    for (int i = 0; i < WordCount; i++) {
        fprintf(fp, "%s %s %s\n", wordbook[i].word, wordbook[i].partOfSpeech, wordbook[i].meaning);
    }
    fclose(fp);
}

void ModifyWord()
{
    char filename[MAX]="D:/ClionProject/Words/TXT/wordbook.txt";
    char Modify[MAX], Word[MAX],Character[MAX];
    int WordCount=ReadWordBook(filename, wordbook);
    printf("请输入你想修改的单词部分及修改后的内容");
    scanf("%s %s %s",Word, Character, Modify);
    for (int i = 0; i < WordCount; i++)
    {
        if (strcmp(wordbook[i].word, Word)==0)
        {
            if (strcmp(wordbook[i].partOfSpeech, Character)==0)
            {
                strcpy(wordbook[i].partOfSpeech, Modify);
                break;
            }
            else if (strcmp(wordbook[i].meaning, Character)==0)
            {
                strcpy(wordbook[i].meaning,Modify);
                break;
            }
            else
            {
                printf("Modify wrong\n");
                break;
            }
        }
        else
        {
            printf("No such word you want to modify\n");
            break;
        }
    }
    FILE *fp = fopen("D:/ClionProject/Words/TXT/wordbook.txt", "a"); // 打开文件以追加模式写入
    for (int i = 0; i < WordCount; i++) {
        fprintf(fp, "%s %s %s", wordbook[i].word, wordbook[i].partOfSpeech, wordbook[i].meaning);
    }
    fclose(fp);
}

void AddMeaning()
{
    char filename[MAX]="D:/ClionProject/Words/TXT/wordbook.txt";
    char Add[MAX], Word[MAX];
    int WordCount=ReadWordBook(filename, wordbook);
    printf("请输入你想补充的释义 ");
    scanf("%s %s",Word, Add);
    int len = strlen(Add);
    char temp[len + 2];
    temp[0] = ',';
    for (int i = 0; i < len; i++) {
        temp[i + 1] = Add[i];
    }
    temp[len + 1] = '\0';
    strcpy(Add, temp);//为补充的意义前添加空格
    for (int i = 0; i < WordCount; i++)
    {
        if (strcmp(wordbook[i].word, Word)==0)
        {
            strcpy(wordbook[i].meaning,strcat(wordbook[i].meaning, Add));
        }
        else
        {
            printf("没有这个单词\n");
            break;
        }
    }
    FILE *fp = fopen("D:/ClionProject/Words/TXT/wordbook.txt", "a"); // 打开文件以追加模式写入
    for (int i = 0; i < WordCount; i++) {
        fprintf(fp, "%s %s %s", wordbook[i].word,wordbook[i].partOfSpeech, wordbook[i].meaning);
    }
    fclose(fp);
}

void ViewWords()
{
    char filename[MAX]="D:/ClionProject/Words/TXT/wordbook.txt";
    int WordCount=ReadWordBook(filename, wordbook);
    printf("%d\n",WordCount);
    for(int i=0;i<=WordCount;i++)
        printf("%s %s %s\n",wordbook[i].word, wordbook[i].partOfSpeech, wordbook[i].meaning);
}