#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <direct.h>

#include"updateX.h"
#include"initX.h"
#include"routeX.h" 
#include"outputX.h"
#include"logX.h"

void inquire()
{
	FILE* fp = NULL;
	int flag=0;
	int i;
	char inqName[32];
	char command = 'y';
	PASS* tmpPass = passengers;
	PASS* prePass = NULL;
	
	while (command =='y'||command=='Y')
	{
		printf("������Ҫ��ѯ���ÿ����֣�");
		scanf("%s", inqName);
		int* date = (int*)malloc(sizeof(int) * 3);
		timeChange(date, global_hour);//��ϵͳʱ��ת��Ϊ��-��-Сʱ����ʽ
		fp = fopen(interruptLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "��%d��%d��%d���ѯ�ÿ�%s��Ϣ��", date[0], date[1], date[2], inqName);
			fclose(fp);
		}
		while (getchar() != '\n');//ɾ���û���������
		while (tmpPass)//Ѱ����ΪinqName���ÿ��Ƿ����
		{
			if (strcmp(tmpPass->name, inqName) != 0)
			{
				prePass = tmpPass;
				tmpPass = tmpPass->next;
			}
			else
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)//�ÿʹ���
		{
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "�ɹ���", inqName);
				fclose(fp);
			}
			if (tmpPass->status == 2)//�ڳ�����
			{
				fp = fopen(interruptLogPath, "a+");
				if (fp)
				{
					fprintf(fp, "�ÿ�%sλ�ڳ���%s�У�", tmpPass->name, citys[tmpPass->position].name);
					fclose(fp);
				}
				printf("�ÿ�%sλ�ڳ���%s�У�", tmpPass->name, citys[tmpPass->position].name);
				for (i = 0; i < 5; i++)
				{
					if (tmpPass->route[i].type == 1 || tmpPass->route[i].type == 2 || tmpPass->route[i].type == 3)
					{
						if (tmpPass->route[i].startCityID == tmpPass->position)//�ҵ���һ�ཻͨ������ʲô
						{
							int* date=(int*)malloc(sizeof(int) * 3);
							timeChange(date, tmpPass->route[i].startTime);
							fp = fopen(interruptLogPath, "a+");
							if (fp)
							{
								fprintf(fp, "���ڵȴ�%d��%d��%d�������%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
								fclose(fp);
							}
							printf("���ڵȴ�%d������%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
							free(date);
						}
					}
				}
			}
			else if (tmpPass->status == 3)//�ڽ�ͨ������
			{
				int* date = (int*)malloc(sizeof(int) * 3);
				timeChange(date, tmpPass->route[tmpPass->position].endTime);
				fp = fopen(interruptLogPath, "a+");
				if (fp)
				{
					fprintf(fp, "�ÿ����ڳ���%s������%d��%d��%d�㵽��%s\n", tmpPass->route[tmpPass->position].name, date[0], date[1], date[2], citys[tmpPass->route[tmpPass->position].endCityID].name);
					fclose(fp);
				}
				printf("�ÿ����ڳ���%s������%d��%d��%d�㵽��%s\n", tmpPass->route[tmpPass->position].name, date[0], date[1], date[2], citys[tmpPass->route[tmpPass->position].endCityID].name);
				free(date);
			}
			printf("�ÿ͵������г̹滮��\n");
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "�ÿ͵������г̹滮��\n");
				fclose(fp);
			}
			outputRoute(tmpPass);
			printf("------------------------------------------------------------\n");
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "------------------------------------------------------------\n");
				fclose(fp);
			}
		}
		else//�ÿͲ�����
		{
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "ʧ�ܣ����޴���\n");
				fprintf(fp, "------------------------------------------------------------\n");
				fclose(fp);
			}
			printf("δ�ҵ��ÿ�%s\n", inqName);
			printf("------------------------------------------------------------\n");
		}
		flag = 0;
		printf("�Ƿ������ѯ��Y/N��");
		command = getchar();
	}
	while (getchar() != '\n');//ɾ���û���������
}

void addPass()
{
	FILE* fp = NULL;
	char command = 'n';
	PASS* tmpPass;
	PASS* prePass;
	//printf("����ÿ��谴��ʽ������Ϣ����ʽ��Ҫ��0/1�� ��ʱ ��� �յ� ���֡������磺0 0 a b P1 ��ʾP1Ҫ��ͷ���a->b��1 2 a b P2 ��ʾP2��ʱ2Сʱa->b\n���»س�������һ���ÿͣ�\n");
	printf("ȷ��Ҫ������ÿ���Y/N��");
	command = getchar();
	while (getchar() != '\n');//ɾ���û���������
	while (command == 'y' || command == 'Y')
	{
		int* date = (int*)malloc(sizeof(int) * 3);
		timeChange(date, global_hour);
		fp = fopen(interruptLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "��%d��%d��%d������ÿͣ�\n", date[0], date[1], date[2]);
			fclose(fp);
		}
		tmpPass = passengers;//�����½ڵ���passenger����
		if (passengers != NULL)//�����ǰ�����ÿ�
		{
			while (tmpPass != NULL)
			{
				prePass = tmpPass;
				tmpPass = tmpPass->next;
			}
			tmpPass = (PASS*)malloc(sizeof(PASS));
			prePass->next = tmpPass;
			activePass++;
		}
		else
		{
			tmpPass = (PASS*)malloc(sizeof(PASS));
			passengers = tmpPass;
			activePass = 1;
		}
		*tmpPass = { 0 };

		printf("�˿������ǣ�");
		scanf("%s", tmpPass->name);
		getchar();
		printf("Ҫ����ʱ��0-��Ҫ��1Ҫ�󣩣�");
		scanf("%d", &tmpPass->request[0]);
		if (tmpPass->request[0] == 1)
		{
			printf("��ʱ����Сʱ��");
			scanf("%d", &tmpPass->request[1]);

		}
		else if (tmpPass->request[0] == 0)
		{
			tmpPass->request[1] = INFINITE;
		}
		printf("���������ĸ����У����ո�����ĳ���˳������������");
		scanf("%d", &tmpPass->request[2]);
		printf("Ŀ�ĵ����ĸ����У����ո�����ĳ���˳������������");
		scanf("%d", &tmpPass->request[3]);
		getchar();

		
		tmpPass->position = tmpPass->request[2];
		tmpPass->status = 2;
		fp = fopen(interruptLogPath, "a+");
		if (fp)
		{
			if (tmpPass->request[0] == 0)
			{
				fprintf(fp, "�ÿ�������%s���ÿ�Ҫ��ͷ��մ�%s����%s\n", tmpPass->name, citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
			}
			else if (tmpPass->request[0] == 1)
			{
				fprintf(fp, "�ÿ�������%s���ÿ�Ҫ����ʱ%dСʱ��%s����%s\n", tmpPass->name, tmpPass->request[1], citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
			}
			fclose(fp);
		}
		if (tmpPass->request[0] == 0)
		{
			tmpPass->request[1] = INFINITE;
		}
		//printf("%d %d %d %d %s\n", tmpPass->request[0], tmpPass->request[1], tmpPass->request[2], tmpPass->request[3], tmpPass->name);
		tmpPass->next = NULL;

		findRoute(tmpPass);//�������ÿ͵����мƻ�

		//չʾ�ƻ���д����־
		printf("�����������мƻ���\n");
		fp = fopen(interruptLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "�����������мƻ���\n");
			fclose(fp);
		}
		outputRoute(tmpPass);
		printf("------------------------------------------------------------\n");
		fp = fopen(interruptLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "------------------------------------------------------------\n");
			fclose(fp);
		}
		fp = fopen(systemLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "��ǰʱ��%d��%d��%d��,������ÿ�%s\n", date[0], date[1], date[2], tmpPass->name);
			fclose(fp);
		}
		free(date);
		updatePassStage(NULL, tmpPass);//�����ÿ�״̬
		fp = fopen(systemLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "------------------------------------------------------------\n");
			fclose(fp);
		}
		printf("��������ÿͣ�Y/N��");
		command = getchar();
		while (getchar() != '\n');//ɾ���û���������
	}
}

void cityChange()
{
	FILE* fp = NULL;
	char command = 'n';
	char cName[32];
	int i, j, k;
	int sflag = 0;
	int flag = 0;
	printf("��ӽ�ͨ��������������֣��س�����ʾ������\n");
	printf("ȷ��Ҫ����½�ͨ��Y/N��");
	command = getchar();
	while (getchar() != '\n');//ɾ���û���������
	while (command == 'y' || command == 'Y')
	{
		printf("������Ҫ��ӽ�ͨ�ĳ�������");
		scanf("%s", cName);
		getchar();
		for (i = 0, flag = 0; i < cityNum && flag == 0; i++)
		{
			if (strcmp(cName, citys[i].name) == 0)
			{
				flag = 1;
			}
		}
		i--;
		if (flag == 1)
		{
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "����%s����½�ͨ����", cName);
				fclose(fp);
			}
			for (j = 0; j < 3; j++)
			{
				if (citys[i].ruleTable[j].freq == 0)
				{
					break;
				}
			}
			citys[i].ruleTable[j].startCityID = i;
			while (sflag == 0)
			{
				printf("���˽�ͨ�յ�Ϊ����������������֣���");
				scanf("%s", cName);
				getchar();
				for (j = 0, flag = 0; j < cityNum && flag == 0; j++)
				{
					if (strcmp(cName, citys[j].name) == 0)
					{
						flag = 1;
					}
				}
				j--;
				if (flag == 1)
				{
					citys[i].ruleTable[j].endCityID = j;
					sflag = 1;
				}
				else
				{
					printf("û����Ϊ��%s���ĳ���", cName);
				}
			}
			printf("�����μ���Ƶ�ʣ��೤ʱ��һ�ˣ� ���ͣ�1 - 2 - 3:�� - �� - ������ʱ�������գ����ո�ָ���");
			scanf("%d", &citys[i].ruleTable[j].freq);
			scanf("%d", &citys[i].ruleTable[j].type);
			scanf("%d", &citys[i].ruleTable[j].duration);
			scanf("%f", &citys[i].ruleTable[j].risk);
			getchar();
			printf("�������뽻ͨ���֣�");
			scanf("%s", citys[i].ruleTable[j].name);
			getchar();
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "��ͨ���ƣ�%s����ͨ���ͣ��ɻ�����λʱ����գ�%f������վ��%s���յ�վ��%s����ʱ��%d��Ƶ�ʣ�ÿ%dСʱһ�ˡ�\n",
					citys[i].ruleTable[j].name,
					citys[i].ruleTable[j].risk,
					citys[i].ruleTable[j].startCityID,
					citys[i].ruleTable[j].endCityID,
					citys[i].ruleTable[j].duration,
					citys[i].ruleTable[j].freq);
				fprintf(fp, "------------------------------------------------------------\n");
				fclose(fp);
			}
			
		}
		else
		{
			printf("����Ϊ��%s���ĳ���\n", cName);
		}
		printf("------------------------------------------------------------\n");
		printf("������ӽ�ͨ��Y/N��");
		command = getchar();
		while (getchar() != '\n');//ɾ���û���������
	}
}
