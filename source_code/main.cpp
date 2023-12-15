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

//��ʼ�� ��Ҫȫ�ֱ���
int activePass = 0; //��Ծ�˿���
int global_hour = -1; //ϵͳʱ��
int cityNum = 0;//������

PASS* passengers = NULL;
CITY citys[MAX_CITY] = { 0 };
char systemLogPath[64] = { 0 };
char interruptLogPath[64] = { 0 };
char otherLogPath[64] = { 0 };

//��ʱ����ʱ����������ϵͳ��ÿСʱִ��һ��
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
        fprintf(fp, "1Сʱ��ȥ�ˣ���ǰʱ����%d��%d��%d��.\n", date[0], date[1], date[2]);
        fclose(fp);
    }
    printf("1Сʱ��ȥ�ˣ���ǰʱ����%d��%d��%d��.\n", date[0], date[1], date[2]);
    updateTimetable();//���½�ͨʱ���
    //outputCitys();
    if (passengers == NULL)
    {
        fp = fopen(systemLogPath, "a+");
        if (fp)
        {
            fprintf(fp, "��ǰ���ÿ�ʹ�ñ�ϵͳ\n");
            fclose(fp);
        }
        printf("��ǰ���ÿ�ʹ�ñ�ϵͳ\n");
    }
    else
    {
        while(tmpPass)
        {
            tmpPass = updatePassStage(prePass, tmpPass);//�����ÿ�״̬�����
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

//����˵���Լ���ͼ��ʱ�����ȳ�ʼ��
MYTIMER sTimer;
int initProgram()
{
    FILE* fp = NULL;
    
    //���������־���ļ���
    char folderName[] = "LOG";//�ļ�������
    if (_access(folderName, 0) == -1)// �ļ��в������򴴽��ļ���
    {
        _mkdir(folderName);
    }
    char thisTime[64] = { 0 };
    time_t t = time(NULL);
    strftime(thisTime, sizeof(thisTime) - 1, "%Y-%m-%d-%H-%M-%S", localtime(&t));     //��-��-��-ʱ-��-��
    //�������γ����������ɵ���־·���Լ��ļ�����"xxLog��-��-��-ʱ-��-��"
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
    int cflag = 0;//cflagָʾ������Ϣ�Ƿ���¼��
    int pflag = 0;//pflagָʾ�ÿ���Ϣ�Ƿ���¼��
    //�汾��Ϣ
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
    printf("Ҫ����ʵ�������ʾϵͳһСʱ����\n");
    scanf("%d", &interval);
    while (getchar() != '\n');//ɾ���û���������
    sTimer = { "TIMER1",interval,0,func2 };//��ʼ����ʱ��
    while (cflag == 0)
    {
        printf("�Ƿ��ֶ���������Լ�������Ϣ��ѡ������ʹ��Ĭ�����ݡ�������Y/N��");
        ch = getchar();
        while (getchar() != '\n');//ɾ���û���������
        if (ch == 'Y' || ch == 'y')
        {
            getData();//��ȡ��������
            cflag = 1;
        }
        else if (ch == 'N' || ch == 'n')
        {
            getDataDefault();
            cflag = 1;
        }
        else
        {
            printf("���벻�Ϸ�\n");
        }
    }
    updateTimetable();
    while (pflag == 0)
    {
        printf("�Ƿ��ֶ������ÿ���Ϣ��ѡ������ʹ��Ĭ�����ݡ�������Y/N��");
        ch = getchar();
        while (getchar() != '\n');//ɾ���û���������
        if (ch == 'Y' || ch == 'y')
        {
            getOrder();//��ȡ�ÿ�Ҫ��
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
            printf("���벻�Ϸ�\n");
        }
    }
    PASS* tmpPass = passengers;
    PASS* prePass = NULL;
    for (i = 0; i < activePass && tmpPass != NULL; i++)
    {
        //printf("findroute %s \n", tmpPass->name);
        findRoute(tmpPass);//�������мƻ�
        //outputRoute(tmpPass);
        printf("Ϊ�ÿ�%s�����������мƻ���\n", tmpPass->name);
        fp = fopen(systemLogPath, "a+");
        if (fp)
        {
            fprintf(fp, "Ϊ�ÿ�%s�����������мƻ���\n", tmpPass->name);
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
                    fprintf(fp, "����%s��%d��%d��%d���%s��������%dСʱ����%s\n",
                        tmpPass->route[j].name,
                        date[0], date[1], date[2],
                        citys[tmpPass->route[j].startCityID].name,
                        tmpPass->route[j].duration,
                        citys[tmpPass->route[j].endCityID].name);
                    fclose(fp);
                }
                printf("����%s��%d��%d��%d���%s��������%dСʱ����%s\n",
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

//�����жϴ�����
void myBreak(char ch)
{
    while (ch != 'q' && ch != 'Q')
    {
        if (ch == 'i' || ch == 'I')//��ѯ
        {
            inquire();
            break;
        }
        else if (ch == 'p' || ch == 'P')//���ÿ�
        {
            addPass();
            break;
        }
        else if (ch == 'c' || ch == 'C')//���н�ͨ����
        {
            cityChange();
            break;
        }
        else
        {
            printf("ָ��������������룬����qȡ��ָ�\n");
            ch = getchar();
            while (getchar() != '\n');//ɾ���û���������
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
            //��ʱ����ʱ�ж�
            if (time(NULL) - sTimer.tLast >= sTimer.tInterval) 
            {
                sTimer.tLast = time(NULL);
                global_hour++;
                func2();
            }
            //���������ж�
            if (kbhit()) 
            {
                ch = getch();
                //����ESC�˳�����
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

        //�ͷ������PASS�ռ�
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