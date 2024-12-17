#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX 100
#define TotalWords 50

typedef struct {
    char word[100];
    char partOfSpeech[100];
    char meaning[1000];
} Word;


Word wrongwords[10000];
Word wordbook[10000];
char HelpWord[1000][100]={0};
int assitant=0;
int score=0;
int HighestMark=0;
// 功能声明
void ViewWords();
int ReadWordBook(char* fname,Word wordbook[]);
void StartLearning();
void FourQuestions();
void SpellWords();
void ViewWrongWords();
void ScoreManagement();
void ReLearnWrongWords();

int main()
{
    SetConsoleOutputCP(65001);
    int choice;
    do
    {
        printf("\n选择你的学习方式:\n");
        printf("1. 查看单词本\n");
        printf("2. 开始学习\n");
        printf("3. 查看成绩\n");
        printf("4. 查看错题本\n");
        printf("5. 复习错题\n");
        printf("0. 退出\n");
        printf("请输入你的选项: ");
        scanf("%d", &choice);
        switch (choice)
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
                printf("退出成功\n");
                break;
            default:
                printf("无效选项！\n");
        }
    }while (choice != 0);
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
        fscanf(fp,"%s %s %[^\n]",wordbook[i].word,wordbook[i].partOfSpeech,wordbook[i].meaning);//注意格式
        i++;
    }
    fclose(fp);
    return i-1; //因为文件写入时输入格式里的换行会写入文件，最后一条记录后面会有一个空行
}

void ViewWords()
{
    char booklist[MAX]="D:/ClionProject/Words/TXT/wordbook.txt";
    int WordCount=ReadWordBook(booklist, wordbook);
    for(int i=0;i<WordCount;i++)
        printf("%s %s %s \n",wordbook[i].word, wordbook[i].partOfSpeech, wordbook[i].meaning);
}//查看单词本

void ViewWrongWords()
{
    char booklist[MAX]="D:/ClionProject/Words/TXT/wrongwords.txt";
    int WordCount=ReadWordBook(booklist, wrongwords);
    for(int i=0;i<WordCount;i++)
        printf("%s %s %s \n",wrongwords[i].word, wrongwords[i].partOfSpeech, wrongwords[i].meaning);
}//查看错题本

void StartLearning()
{
    char booklist[MAX]="D:/ClionProject/Words/TXT/wordbook.txt";
    int WordCount=ReadWordBook(booklist, wordbook);
    int ways,mode;
    do
    {
        printf("选择你的学习方式：\n");
        printf("1.英文提示->输入中文\n");
        printf("2.中文提示->输入英文\n");
        printf("0.退出\n");
        printf("请输入你的选项: ");
        scanf("%d", &ways);
        switch(ways)
        {
            case 1:
                assitant=1;
                for(int i=0;i<=WordCount;i++)
                {
                    strcpy(HelpWord[i],wordbook[i].word);
                }
                ways=0;
            break;
            case 2:
                assitant=2;
                for(int i=0;i<=WordCount;i++)
                {
                    strcpy(HelpWord[i],wordbook[i].meaning);
                }
                ways=0;
            break;
            case 0:
                printf("退出选项\n");
                memset(HelpWord, 0, sizeof(HelpWord));
            return;
            default:
                printf("错误选项\n");
        }
        do
        {
            printf("请选择你的学习模式\n");
            printf("1.选择题\n");
            printf("2.填空题\n");
            printf("0.退出\n");
            printf("请输入你的选项: ");
            scanf("%d", &mode);
            switch(mode)
            {
                case 1:
                    FourQuestions();
                mode=0;
                break;
                case 2:
                    SpellWords();
                mode=0;
                break;
                case 0:
                    printf("返回上一步\n");
                break;
                default:
                    printf("Wrong\n");
            }
        }while (mode!=0);
    } while (ways!=0);
}//开始学习菜单,同时录入提示词

void FourQuestions()
{
    FILE *fp = fopen("D:/ClionProject/Words/TXT/wrongwords.txt", "a");//以追加模式打开错题本
    char wrongwordlist[MAX]="D:/ClionProject/Words/TXT/wordbook.txt";
    int count=ReadWordBook(wrongwordlist, wrongwords);
    int numbers=0;
    do
    {
        printf("请输入你今天想学的单词数");
        scanf("%d",&numbers);
        if(numbers<=0 || numbers>(TotalWords/4))
        {
            printf("输入无效，请再输一次！\n");
            continue;
        }
        if (numbers>0 && numbers<=10)
        {
            printf("Emmm，有点少，但我们还是开始吧\n");
            break;
        }
        if (numbers>10 && numbers<=(TotalWords/4))
        {
            printf("Wow，你太棒了，我们开始吧\n");
            break;
        }
    }while (!(numbers>0 && numbers<=(TotalWords/4)));
    HighestMark+=numbers*10;
    int generatedNumbers[TotalWords] = {0};  // 用于标记已经生成的数
    int RandNumbers[numbers][4];  // 存储每组的随机数
    int i, j, num;
    // 设置随机数种子
    srand(time(0));
    for (i = 0; i < numbers; i++) {
        for (j = 0; j < 4;) {
            // 生成 0 到 49 之间的随机数
            num = rand() % (TotalWords);
            // 检查该数是否已生成过
            if (generatedNumbers[num] == 0) {
                // 如果没有生成过，则将其存储
                RandNumbers[i][j] = num;
                generatedNumbers[num] = 1;  // 标记该数已经生成
                j++;  // 增加该组已生成数字的计数
            }
        }
    }
    for (i = 0; i < numbers; i++)
    {
        char Answer;
        int CorrectAnswer=rand() %4 ;
        if (assitant==1)
        {
            printf("本题的提示词为：%s\n",HelpWord[RandNumbers[i][CorrectAnswer]]);
            printf("A.%s\n",wordbook[RandNumbers[i][0]].meaning);
            printf("B.%s\n",wordbook[RandNumbers[i][1]].meaning);
            printf("C.%s\n",wordbook[RandNumbers[i][2]].meaning);
            printf("D.%s\n",wordbook[RandNumbers[i][3]].meaning);//显示选项
        }
        if (assitant==2)
        {
            printf("本题的提示词为：%s\n",HelpWord[RandNumbers[i][CorrectAnswer]]);
            printf("A.%s\n",wordbook[RandNumbers[i][0]].word);
            printf("B.%s\n",wordbook[RandNumbers[i][1]].word);
            printf("C.%s\n",wordbook[RandNumbers[i][2]].word);
            printf("D.%s\n",wordbook[RandNumbers[i][3]].word);//显示选项
        }
        printf("请输入正确选项\n");
        scanf(" %c",&Answer);
        int select=(int)Answer;
        if (select-65==CorrectAnswer || select-97==CorrectAnswer)
        {
            printf("输入正确，加十分！\n");
            score+=10;//计分+10
        }
        else
        {
            printf("错误!\n正确答案是%s\n",wordbook[RandNumbers[i][CorrectAnswer]].word);
            score-=10;//计分-10
            strcpy(wrongwords[count].word,wordbook[RandNumbers[i][CorrectAnswer]].word);
            strcpy(wrongwords[count].partOfSpeech,wordbook[RandNumbers[i][CorrectAnswer]].partOfSpeech);
            strcpy(wrongwords[count].meaning,wordbook[RandNumbers[i][CorrectAnswer]].meaning);
            fprintf(fp, "%s %s %s\n", wrongwords[count].word, wrongwords[count].partOfSpeech, wrongwords[count].meaning);
            //这边为登录错题本
        }
    }
    fclose(fp);
}//选择题

void SpellWords()
{
    FILE *fp = fopen("D:/ClionProject/Words/TXT/wrongwords.txt", "a");//以追加模式打开错题本
    char wrongwordlist[MAX]="D:/ClionProject/Words/TXT/wordbook.txt";
    int count=ReadWordBook(wrongwordlist, wrongwords);
    int numbers=0;
    do
    {
        printf("请输入你今天想学的单词数");
        scanf("%d",&numbers);
        if(numbers<=0 || numbers>TotalWords)
        {
            printf("输入无效，请再输一次！\n");
            continue;
        }
        if (numbers>0 && numbers<=10)
        {
            printf("Emmm，有点少，但我们还是开始吧\n");
            break;
        }
        if (numbers>10 && numbers<=TotalWords)
        {
            printf("Wow，你太棒了，我们开始吧\n");
            break;
        }
    }while (!(numbers>0 && numbers<=TotalWords));
    HighestMark+=numbers*10;
    int generatedNumbers[TotalWords] = {0};
    int RandNumbers[numbers];
    int i,num;
    srand(time(0));
    for (i = 0; i < numbers; i++)
    {
        num = rand() % (TotalWords);
        if (generatedNumbers[num] == 0) \
           {
                RandNumbers[i] = num;
                generatedNumbers[num] = 1;  // 标记该数已经生成
           }
    }
    for (i = 0; i < numbers; i++) {
        printf("%d\n",RandNumbers[i]);
    }
    for (i = 0; i < numbers; i++)
    {
        char Answer[MAX];
        if (assitant==1)
        {
            printf("本题的提示词为：%s\n",HelpWord[RandNumbers[i]]);
        }
        if (assitant==2)
        {
            printf("本题的提示词为：%s\n",HelpWord[RandNumbers[i]]);
        }
        printf("请输入正确的英文单词:");
        scanf("%s",&Answer);
        if (!strcmp(Answer,wordbook[RandNumbers[i]].word))
        {
            printf("输入正确，加十分！\n");
            score+=10;//计分+10
        }
        else
        {
            printf("错误!\n正确答案是%s\n",wordbook[RandNumbers[i]].word);
            score-=10;//计分-10
            strcpy(wrongwords[count].word,wordbook[RandNumbers[i]].word);
            strcpy(wrongwords[count].partOfSpeech,wordbook[RandNumbers[i]].partOfSpeech);
            strcpy(wrongwords[count].meaning,wordbook[RandNumbers[i]].meaning);
            fprintf(fp, "%s %s %s\n", wrongwords[count].word, wrongwords[count].partOfSpeech, wrongwords[count].meaning);
            //这边为登录错题本
        }
    }
    fclose(fp);
}//拼写题

void ReLearnWrongWords()
{
    char booklist[MAX]="D:/ClionProject/Words/TXT/wrongwords.txt";
    int WordCount=ReadWordBook(booklist, wrongwords);
    int list[WordCount],number=0;
    printf("你的错题有:\n");
    for(int i=0;i<WordCount;i++)
        printf("%d %s %s %s \n",i+1,wrongwords[i].word, wrongwords[i].partOfSpeech, wrongwords[i].meaning);
    printf("请问你要选择重背的错题数:");
    scanf("%d",&number);
    printf("请问你要选择重背的错题编号:");
    for(int i=0;i<number;i++)
    {
        int temp;
        scanf("%d",&temp);
        list[i]=temp-1;
    }
    printf("我将会把这些词的中英文都给你，请你复习后拼写一遍，这将有助于你掌握词汇:\n");
    for (int i=0;i<number;i++)
    {
        char Answer[MAX];
        printf("%s %s \n",wrongwords[list[i]].word, wrongwords[list[i]].meaning);
        printf("请输入对应的英文:");
        scanf("%s",&Answer);
        if (!strcmp(Answer,wrongwords[list[i]].word))
        {
            printf("你成功掌握了%s这个词！",wrongwords[list[i]].word);
            for (int j = 0; j <=WordCount; j++)
            {
                if (!strcmp(wrongwords[j].word, wrongwords[list[i]].word))
                {
                    for (int k = j; k < WordCount - 1; k++)
                    {
                        strcpy(wrongwords[k].word,wrongwords[k + 1].word);
                        strcpy(wrongwords[k].partOfSpeech,wrongwords[k + 1].partOfSpeech);
                        strcpy(wrongwords[k].meaning,wrongwords[k + 1].meaning);
                    }
                    WordCount--;
                    break;
                }
            }
        }
        else
        {
            printf("你仍然有错,再尝试学习一遍吧\n");
        }
    }
    FILE *fp = fopen("D:/ClionProject/Words/TXT/wrongwords.txt", "w");
    for (int i = 0; i < WordCount; i++) {
        fprintf(fp, "%s %s %s\n", wrongwords[i].word, wrongwords[i].partOfSpeech, wrongwords[i].meaning);
    }
    fclose(fp);
    printf("你的剩余的错题有:\n");
    for(int i=0;i<WordCount;i++)
        printf("%d %s %s %s \n",i+1,wrongwords[i].word, wrongwords[i].partOfSpeech, wrongwords[i].meaning);
}

void ScoreManagement()//成绩查看系统
{
    if (HighestMark==0)
    {
        printf("你今天还没有学习，请学习后再来吧\n");
        return;
    }
    printf("你的成绩是:%d\n",score);
    if (score<HighestMark)
    {
        printf("你没能完全掌握，是否要复习你的错题,以下是你的错题:\n");
        ViewWrongWords();
        printf("请问你需要复习你的错题吗?");

        ReLearnWrongWords();
    }
    else
    {
        printf("Wow,你已经全部掌握了今天的单词，继续努力吧");
    }
}