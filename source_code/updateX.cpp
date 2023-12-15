#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <direct.h>
#include <string.h>

#include"updateX.h"
#include"initX.h"
#include"logX.h"

#define PREDAYS 7

void updateTimetable()
{
	FILE* fp = NULL;
	fp = fopen(otherLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "ʱ�䣺%d\n",global_hour);
		fclose(fp);
	}
	int i, j, k;
	for (i = 0; i < cityNum; i++)
	{
		citys[i].transNum = 0;
		for (j = 0; j < 10; j++)
		{
			if (citys[i].ruleTable[j].freq)
			{
				//printf("rule\n");
				//Ԥ��PREDAYSʱ���ڵ�ȫ����ͨ��Ϣ
				for (k = 0; k <= (PREDAYS * 24); k++)
				{
					if ((global_hour + k) % citys[i].ruleTable[j].freq == 0)
					{
						//printf("freq\n");
						strcpy(citys[i].timeTable[citys[i].transNum].name, citys[i].ruleTable[j].name);
						citys[i].timeTable[citys[i].transNum].type = citys[i].ruleTable[j].type;
						citys[i].timeTable[citys[i].transNum].startCityID = citys[i].ruleTable[j].startCityID;
						citys[i].timeTable[citys[i].transNum].endCityID = citys[i].ruleTable[j].endCityID;
						citys[i].timeTable[citys[i].transNum].duration = citys[i].ruleTable[j].duration;
						citys[i].timeTable[citys[i].transNum].risk = citys[i].ruleTable[j].risk;
						citys[i].timeTable[citys[i].transNum].startTime = global_hour + k;
						citys[i].timeTable[citys[i].transNum].endTime = global_hour + k + citys[i].timeTable[citys[i].transNum].duration;
						fp = fopen(otherLogPath, "a+");
						if (fp)
						{
							fprintf(fp, "%s %d %d %d %d %d %d %f\n",
								citys[i].timeTable[citys[i].transNum].name,
								citys[i].timeTable[citys[i].transNum].type,
								citys[i].timeTable[citys[i].transNum].startCityID,
								citys[i].timeTable[citys[i].transNum].startTime,
								citys[i].timeTable[citys[i].transNum].endCityID,
								citys[i].timeTable[citys[i].transNum].endTime,
								citys[i].timeTable[citys[i].transNum].duration,
								citys[i].timeTable[citys[i].transNum].risk);
							fclose(fp);
						}
						citys[i].transNum++;
					}//end of if
				}//end of for(k)
			}//end of if
		}//end of for(j)
	}//end of for(i)
	fp = fopen(otherLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "------------------------------------\n");
		fclose(fp);
	}
}

PASS* updatePassStage(PASS* prePass, PASS* tmpPass)
{
	FILE* fp = NULL;
	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "�ÿ�%s��ע�⣺\n", tmpPass->name);
		fclose(fp);
	}
	printf("�ÿ�%s��ע�⣺\n", tmpPass->name);
	int i;
	if (tmpPass->status == 2)//�ڳ�����
	{
		for (i = 0; i < 5; i++)
		{
			if (tmpPass->route[i].type == 1 || tmpPass->route[i].type == 2 || tmpPass->route[i].type == 3)
			{
				if (tmpPass->route[i].startCityID == tmpPass->position)//�ҵ���һ�ཻͨ������ʲô
				{
					if (global_hour == tmpPass->route[i].startTime)//����ǳ���ʱ��
					{
						fp = fopen(systemLogPath, "a+");
						if (fp)
						{
							fprintf(fp, "�����%s\n", tmpPass->route[i].name);
							fclose(fp);
						}
						printf("�����%s\n", tmpPass->route[i].name);
						tmpPass->status = 3;//����״̬
						tmpPass->position = i;//����λ��
						tmpPass->risk = tmpPass->risk + tmpPass->route[i].risk * citys[tmpPass->route[i].startCityID].risk;
						//printf("%f\n", tmpPass->risk);
						return tmpPass;
					}
					else
					{
						int* date = (int*)malloc(sizeof(int) * 3);
						timeChange(date, tmpPass->route[i].startTime);
						fp = fopen(systemLogPath, "a+");
						if (fp)
						{
							fprintf(fp, "��ȴ�%d��%d��%d�������%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
							fclose(fp);
						}
						printf("��ȴ�%d��%d��%d�������%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
						free(date);
						tmpPass->risk = tmpPass->risk + citys[tmpPass->position].risk;
						//printf("%f\n", tmpPass->risk);
						return tmpPass;
					}
				}
			}
		}
	}
	else if (tmpPass->status == 3)//�ڽ�ͨ������
	{
		if (global_hour == tmpPass->route[tmpPass->position].endTime)//�����ǰ��ͨ�����Ѵ��յ�
		{
			if (tmpPass->route[tmpPass->position].endCityID == tmpPass->request[3])//�ѵִ�����Ŀ�ĵ�
			{
				fp = fopen(systemLogPath, "a+");
				if (fp)
				{
					fprintf(fp, "���Ѵ�Ŀ�ĵأ��ۼƷ�����%f,��лʹ��!\n", tmpPass->risk);
					fclose(fp);
				}
				printf("���Ѵ�Ŀ�ĵأ��ۼƷ�����%f,��лʹ��!\n",tmpPass->risk);
				tmpPass->status = 2;
				tmpPass->position = tmpPass->route[tmpPass->position].endCityID;
				if (prePass != NULL)
				{
					prePass->next = tmpPass->next;
					free(tmpPass);
					activePass--;
					return prePass;
				}
				else
				{
					passengers = tmpPass->next;
					free(tmpPass);
					activePass--;
					return NULL;
				}
			}
			else
			{
				fp = fopen(systemLogPath, "a+");
				if (fp)
				{
					fprintf(fp, "��������%s�ѵ���%s\n", tmpPass->route[tmpPass->position].name, citys[tmpPass->route[tmpPass->position].endCityID].name);
					fclose(fp);
				}
				printf("��������%s�ѵ���%s\n", tmpPass->route[tmpPass->position].name, citys[tmpPass->route[tmpPass->position].endCityID].name);
				tmpPass->status = 2;
				tmpPass->position = tmpPass->route[tmpPass->position].endCityID;
				for (i = 0; i < 5; i++)
				{
					if (tmpPass->route[i].type == 1 || tmpPass->route[i].type == 2 || tmpPass->route[i].type == 3)
					{
						if (tmpPass->route[i].startCityID == tmpPass->position)//�ҵ���һ�ཻͨ������ʲô
						{
							if (global_hour == tmpPass->route[i].startTime)//����ǳ���ʱ��
							{
								fp = fopen(systemLogPath, "a+");
								if (fp)
								{
									fprintf(fp, "�����%s\n", tmpPass->route[i].name);
									fclose(fp);
								}
								printf("�����%s\n", tmpPass->route[i].name);
								tmpPass->status = 3;//����״̬
								tmpPass->position = i;//����λ��
								tmpPass->risk = tmpPass->risk + tmpPass->route[i].risk * citys[tmpPass->route[i].startCityID].risk;
								//printf("%f\n", tmpPass->risk);
								return tmpPass;
							}
							else
							{
								int* date = (int*)malloc(sizeof(int) * 3);
								timeChange(date, tmpPass->route[i].startTime);
								fp = fopen(systemLogPath, "a+");
								if (fp)
								{
									fprintf(fp, "��ȴ�%d��%d��%d�������%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
									fclose(fp);
								}
								printf("��ȴ�%d��%d��%d�������%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
								free(date);
								tmpPass->risk = tmpPass->risk + citys[tmpPass->position].risk;
								//printf("%f\n", tmpPass->risk);
								return tmpPass;
							}
						}
					}
				}
			}
		}
		else
		{
			int* date = (int*)malloc(sizeof(int) * 3);
			timeChange(date, tmpPass->route[tmpPass->position].endTime);
			fp = fopen(systemLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "��������%s����%d��%d��%d�㵽��%s\n", tmpPass->route[tmpPass->position].name, date[0], date[1], date[2], citys[tmpPass->route[tmpPass->position].endCityID].name);
				fclose(fp);
			}
			printf("��������%s����%d��%d��%d�㵽��%s\n", tmpPass->route[tmpPass->position].name, date[0], date[1], date[2], citys[tmpPass->route[tmpPass->position].endCityID].name);
			free(date);
			tmpPass->risk = tmpPass->risk + tmpPass->route[tmpPass->position].risk * citys[tmpPass->position].risk;
			//printf("%f\n", tmpPass->risk);
			return tmpPass;
		}
	}
}