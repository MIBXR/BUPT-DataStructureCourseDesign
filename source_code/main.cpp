#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <direct.h>
#include<time.h>
#include <io.h>
#include"initX.h"
#include"inputX.h"
#include"outputX.h"
#include"updateX.h"
#include"routeX.h" 
#include"interruptX.h"
#include"logX.h"

//初始化 重要全局变量
int activePass = 0; //活跃乘客数
int global_hour = -1; //系统时间
int cityNum = 0;//城市数

PASS* passengers = NULL;
CITY citys[MAX_CITY] = { 0 };
char systemLogPath[64] = { 0 };
char interruptLogPath[64] = { 0 };
char otherLogPath[64] = { 0 };

//定时器超时处理函数，即系统内每小时执行一次
void func2()
{
    FILE* fp = NULL;
    int i,j;
    PASS* tmpPass = passengers;
    PASS* prePass = NULL;
    fp = fopen(systemLogPath, "a+");
    int* date = (int*)malloc(sizeof(int) * 3);
    timeChange(date, global_hour);
    if (fp)
    {
        fprintf(fp, "1小时过去了，当前时间是%d月%d日%d点.\n", date[0], date[1], date[2]);
        fclose(fp);
    }
    printf("1小时过去了，当前时间是%d月%d日%d点.\n", date[0], date[1], date[2]);
    updateTimetable();//更新交通时间表
    //outputCitys();
    if (passengers == NULL)
    {
        fp = fopen(systemLogPath, "a+");
        if (fp)
        {
            fprintf(fp, "当前无旅客使用本系统\n");
            fclose(fp);
        }
        printf("当前无旅客使用本系统\n");
    }
    else
    {
        while(tmpPass)
        {
            tmpPass = updatePassStage(prePass, tmpPass);//更新旅客状态并输出
            //printf("findroute %d \n", i);
            //findRoute(tmpPass);
            //outputRoute(tmpPass);
            if (tmpPass != NULL)
            {
                prePass = tmpPass;
                tmpPass = tmpPass->next;
            }
            else
            {
                prePass = NULL;
                tmpPass = passengers;
            }
        }
    }
    fp = fopen(systemLogPath, "a+");
    if (fp)
    {
        fprintf(fp, "------------------------------------------------------------\n");
        fclose(fp);
    }
    //outputRoute();
    printf("------------------------------------------------------------\n");
}

//程序说明以及地图，时间间隔等初始化
MYTIMER sTimer;
int initProgram()
{
    FILE* fp = NULL;
    
    //创建存放日志的文件夹
    char folderName[] = "LOG";//文件夹名称
    if (_access(folderName, 0) == -1)// 文件夹不存在则创建文件夹
    {
        _mkdir(folderName);
    }
    char thisTime[64] = { 0 };
    time_t t = time(NULL);
    strftime(thisTime, sizeof(thisTime) - 1, "%Y-%m-%d-%H-%M-%S", localtime(&t));     //年-月-日-时-分-秒
    //创建本次程序运行生成的日志路径以及文件名："xxLog年-月-日-时-分-秒"
    strcat(systemLogPath, "./LOG/systemLog");
    strcat(systemLogPath, thisTime);
    strcat(systemLogPath, ".txt");
    strcat(interruptLogPath, "./LOG/interruptLog");
    strcat(interruptLogPath, thisTime);
    strcat(interruptLogPath, ".txt");
    strcat(otherLogPath, "./LOG/otherLog");
    strcat(otherLogPath, thisTime);
    strcat(otherLogPath, ".txt");

    
    int i, j;
    for (i = 0; i < MAX_CITY; i++)
    {
        citys[i] = { 0 };
    }
    char ch;
    int interval;
    int cflag = 0;//cflag指示城市信息是否已录入
    int pflag = 0;//pflag指示旅客信息是否已录入
    //版本信息
    printf("-------------------------------------------------------\n");
    printf("-------------------------------------------------------\n");
    printf("COVID-19  travel simulation system v8.1 BY xr for test.\n");
    printf("-------------------------------------------------------\n");
    printf("-------------------------------------------------------\n\n");

    fp = fopen(systemLogPath, "a+");
    if (fp)
    {
        fprintf(fp, "-------------------------------------------------------\n");
        fprintf(fp, "-------------------------------------------------------\n");
        fprintf(fp, "COVID-19  travel simulation system v8.1 BY xr for test.\n");
        fprintf(fp, "-------------------------------------------------------\n");
        fprintf(fp, "-------------------------------------------------------\n\n");
        fclose(fp);
    }
    fp = fopen(interruptLogPath, "a+");
    if (fp)
    {
        fprintf(fp, "-------------------------------------------------------\n");
        fprintf(fp, "-------------------------------------------------------\n");
        fprintf(fp, "COVID-19  travel simulation system v8.1 BY xr for test.\n");
        fprintf(fp, "-------------------------------------------------------\n");
        fprintf(fp, "-------------------------------------------------------\n\n");
        fclose(fp);
    }
    printf("要用现实多少秒表示系统一小时？：\n");
    scanf("%d", &interval);
    while (getchar() != '\n');//删除用户冗余输入
    sTimer = { "TIMER1",interval,0,func2 };//初始化定时器
    while (cflag == 0)
    {
        printf("是否手动输入城市以及航班信息？选“否”则使用默认数据。请输入Y/N：");
        ch = getchar();
        while (getchar() != '\n');//删除用户冗余输入
        if (ch == 'Y' || ch == 'y')
        {
            getData();//获取城市数据
            cflag = 1;
        }
        else if (ch == 'N' || ch == 'n')
        {
            getDataDefault();
            cflag = 1;
        }
        else
        {
            printf("输入不合法\n");
        }
    }
    updateTimetable();
    while (pflag == 0)
    {
        printf("是否手动输入旅客信息？选“否”则使用默认数据。请输入Y/N：");
        ch = getchar();
        while (getchar() != '\n');//删除用户冗余输入
        if (ch == 'Y' || ch == 'y')
        {
            getOrder();//获取旅客要求
            pflag = 1;
        }
        else if (ch == 'N' || ch == 'n')
        {
            getOrderDefault();
            pflag = 1;
        }
        else
        {
            printf("***************%d*****************\n", ch);
            printf("输入不合法\n");
        }
    }
    PASS* tmpPass = passengers;
    PASS* prePass = NULL;
    for (i = 0; i < activePass && tmpPass != NULL; i++)
    {
        //printf("findroute %s \n", tmpPass->name);
        findRoute(tmpPass);//计算旅行计划
        //outputRoute(tmpPass);
        printf("为旅客%s生成如下旅行计划：\n", tmpPass->name);
        fp = fopen(systemLogPath, "a+");
        if (fp)
        {
            fprintf(fp, "为旅客%s生成如下旅行计划：\n", tmpPass->name);
            fclose(fp);
        }
        for (j = 0; j < 5; j++)
        {
            if (tmpPass->route[j].type == 1 || tmpPass->route[j].type == 2 || tmpPass->route[j].type == 3)
            {
                int* date = (int*)malloc(sizeof(int) * 3);
                timeChange(date, tmpPass->route[j].startTime);
                fp = fopen(systemLogPath, "a+");
                if (fp)
                {
                    fprintf(fp, "乘坐%s在%d月%d日%d点从%s出发经过%d小时到达%s\n",
                        tmpPass->route[j].name,
                        date[0], date[1], date[2],
                        citys[tmpPass->route[j].startCityID].name,
                        tmpPass->route[j].duration,
                        citys[tmpPass->route[j].endCityID].name);
                    fclose(fp);
                }
                printf("乘坐%s在%d月%d日%d点从%s出发经过%d小时到达%s\n",
                    tmpPass->route[j].name,
                    date[0], date[1], date[2],
                    citys[tmpPass->route[j].startCityID].name,
                    tmpPass->route[j].duration,
                    citys[tmpPass->route[j].endCityID].name);
                free(date);
            }
        }
        printf("------------------------------------------------------------\n");
        fp = fopen(systemLogPath, "a+");
        if (fp)
        {
            fprintf(fp, "------------------------------------------------------------\n");
            fclose(fp);
        }
        prePass = tmpPass;
        tmpPass = tmpPass->next;
    }
    return 1;
}

//键盘中断处理函数
void myBreak(char ch)
{
    while (ch != 'q' && ch != 'Q')
    {
        if (ch == 'i' || ch == 'I')//查询
        {
            inquire();
            break;
        }
        else if (ch == 'p' || ch == 'P')//新旅客
        {
            addPass();
            break;
        }
        else if (ch == 'c' || ch == 'C')//城市交通规则
        {
            cityChange();
            break;
        }
        else
        {
            printf("指令错误，请重新输入，或按下q取消指令。\n");
            ch = getchar();
            while (getchar() != '\n');//删除用户冗余输入
        }
    }
}

int main()
{
    if (initProgram())
    {
        char ch;
        while (1)
        {
            //定时器超时判断
            if (time(NULL) - sTimer.tLast >= sTimer.tInterval) 
            {
                sTimer.tLast = time(NULL);
                global_hour++;
                func2();
            }
            //键盘输入判断
            if (kbhit()) 
            {
                ch = getch();
                //按下ESC退出程序
                if (ch == 27) 
                {
                    break;
                }
                else 
                {
                    myBreak(ch);
                }
            }
        }

        //释放申请的PASS空间
        PASS* tmpPass=passengers;
        while (passengers)
        {
            tmpPass = passengers;
            passengers = passengers->next;
            free(tmpPass);
        }
    }
    
	return 0;
}