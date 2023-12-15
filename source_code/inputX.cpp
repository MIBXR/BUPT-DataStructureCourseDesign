#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <direct.h>

#include"inputX.h"
#include"initX.h"
#include"logX.h"

void getData()
{
	int i,j;
	char tmpName[32] = { 0 };
	printf("�ܹ��ж��ٳ��У�");
	scanf("%d",&cityNum);
	printf("�������г��з��ռ����������ո�ָ������%d�����У������31�ַ�������������\n���»س�����һ�����У�\n", MAX_CITY);
	for (i = 0; i < cityNum; i++)
	{
		scanf("%f", &citys[i].risk);//�������
		getchar();
		scanf("%s", citys[i].name);//���������
		while (getchar() != '\n');//ɾ���û���������
	}
	for (i = 0; i < cityNum; i++)
	{
		printf("����%s�Ľ�ͨ������,�س������������Ϣ��\n",citys[i].name);
		int ruleNum = 0;
		scanf("%d",&ruleNum);//���������
		for (j = 0; j < ruleNum; j++)
		{
			printf("��%d������\n", j + 1);
			printf("��ͨ�����ǣ��31�ַ�����");
			scanf("%s", citys[i].ruleTable[j].name);
			getchar();
			printf("��ͨ������(�ɻ�-1����-2������-3����");
			scanf("%d", &citys[i].ruleTable[j].type);
			printf("��λʱ������ǣ�");
			scanf("%f", &citys[i].ruleTable[j].risk);
			citys[i].ruleTable[j].startCityID = i;
			printf("�յ�վ�ǵڼ������У����ո�����ĳ���˳������������");
			scanf("%d", &citys[i].ruleTable[j].endCityID);
			printf("��ʱ���٣�");
			scanf("%d", &citys[i].ruleTable[j].duration);
			printf("Ƶ���Ƕ��٣��೤ʱ��һ�ˣ���");
			scanf("%d", &citys[i].ruleTable[j].freq);
			getchar();
			//printf("%d %d %d %d %d %f %s\n", 
			//	citys[i].ruleTable[j].freq, 
			//	citys[i].ruleTable[j].type, 
			//	citys[i].ruleTable[j].startCityID, 
			//	citys[i].ruleTable[j].endCityID, 
			//	citys[i].ruleTable[j].duration,
			//	citys[i].ruleTable[j].risk,
			//	citys[i].ruleTable[j].name); //�����ô���
		}
	}
	while (getchar() != '\n');//ɾ���û���������

	GenerateCityLog();//���ɳ�����Ϣ��־
}
void getDataDefault()//��ȡĬ�ϳ�����Ϣ
{
	cityNum = 10;
	citys[0].risk = 0.2;
	strcpy(citys[0].name, "city0");
	citys[1].risk = 0.9;
	strcpy(citys[1].name, "city1");
	citys[2].risk = 0.5;
	strcpy(citys[2].name, "city2");
	citys[3].risk = 0.2;
	strcpy(citys[3].name, "city3");
	citys[4].risk = 0.5;
	strcpy(citys[4].name, "city4");
	citys[5].risk = 0.9;
	strcpy(citys[5].name, "city5");
	citys[6].risk = 0.2;
	strcpy(citys[6].name, "city6");
	citys[7].risk = 0.2;
	strcpy(citys[7].name, "city7");
	citys[8].risk = 0.9;
	strcpy(citys[8].name, "city8");
	citys[9].risk = 0.5;
	strcpy(citys[9].name, "city9");
	citys[0].ruleTable[0].freq = 12;
	citys[0].ruleTable[0].type = 2;
	citys[0].ruleTable[0].startCityID = 0;
	citys[0].ruleTable[0].endCityID = 1;
	citys[0].ruleTable[0].duration = 8;
	citys[0].ruleTable[0].risk = 5;
	strcpy(citys[0].ruleTable[0].name, "train0-1:8h");
	citys[0].ruleTable[1].freq = 12;
	citys[0].ruleTable[1].type = 2;
	citys[0].ruleTable[1].startCityID = 0;
	citys[0].ruleTable[1].endCityID = 9;
	citys[0].ruleTable[1].duration = 7;
	citys[0].ruleTable[1].risk = 5;
	strcpy(citys[0].ruleTable[1].name, "train0-9:7h");
	citys[0].ruleTable[2].freq = 24;
	citys[0].ruleTable[2].type = 1;
	citys[0].ruleTable[2].startCityID = 0;
	citys[0].ruleTable[2].endCityID = 5;
	citys[0].ruleTable[2].duration = 4;
	citys[0].ruleTable[2].risk = 9;
	strcpy(citys[0].ruleTable[2].name, "plane0-5:4h");
	citys[1].ruleTable[0].freq = 6;
	citys[1].ruleTable[0].type = 3;
	citys[1].ruleTable[0].startCityID = 1;
	citys[1].ruleTable[0].endCityID = 2;
	citys[1].ruleTable[0].duration = 2;
	citys[1].ruleTable[0].risk = 2;
	strcpy(citys[1].ruleTable[0].name, "car1-2:2h");
	citys[1].ruleTable[1].freq = 4;
	citys[1].ruleTable[1].type = 3;
	citys[1].ruleTable[1].startCityID = 1;
	citys[1].ruleTable[1].endCityID = 9;
	citys[1].ruleTable[1].duration = 2;
	citys[1].ruleTable[1].risk = 2;
	strcpy(citys[1].ruleTable[1].name, "car1-9:2h");
	citys[1].ruleTable[2].freq = 24;
	citys[1].ruleTable[2].type = 1;
	citys[1].ruleTable[2].startCityID = 1;
	citys[1].ruleTable[2].endCityID = 6;
	citys[1].ruleTable[2].duration = 3;
	citys[1].ruleTable[2].risk = 9;
	strcpy(citys[1].ruleTable[2].name, "plane1-6:3h");
	citys[2].ruleTable[0].freq = 6;
	citys[2].ruleTable[0].type = 3;
	citys[2].ruleTable[0].startCityID = 2;
	citys[2].ruleTable[0].endCityID = 1;
	citys[2].ruleTable[0].duration = 2;
	citys[2].ruleTable[0].risk = 2;
	strcpy(citys[2].ruleTable[0].name, "car2-1:2h");
	citys[2].ruleTable[1].freq = 8;
	citys[2].ruleTable[1].type = 3;
	citys[2].ruleTable[1].startCityID = 2;
	citys[2].ruleTable[1].endCityID = 9;
	citys[2].ruleTable[1].duration = 3;
	citys[2].ruleTable[1].risk = 2;
	strcpy(citys[2].ruleTable[1].name, "car2-9:3h");
	citys[2].ruleTable[2].freq = 24;
	citys[2].ruleTable[2].type = 2;
	citys[2].ruleTable[2].startCityID = 2;
	citys[2].ruleTable[2].endCityID = 8;
	citys[2].ruleTable[2].duration = 9;
	citys[2].ruleTable[2].risk = 5;
	strcpy(citys[2].ruleTable[2].name, "train2-8:9h");
	citys[3].ruleTable[0].freq = 12;
	citys[3].ruleTable[0].type = 2;
	citys[3].ruleTable[0].startCityID = 3;
	citys[3].ruleTable[0].endCityID = 2;
	citys[3].ruleTable[0].duration = 7;
	citys[3].ruleTable[0].risk = 5;
	strcpy(citys[3].ruleTable[0].name, "train3-2:7h");
	citys[3].ruleTable[1].freq = 8;
	citys[3].ruleTable[1].type = 3;
	citys[3].ruleTable[1].startCityID = 3;
	citys[3].ruleTable[1].endCityID = 8;
	citys[3].ruleTable[1].duration = 4;
	citys[3].ruleTable[1].risk = 2;
	strcpy(citys[3].ruleTable[1].name, "car3-8:4h");
	citys[3].ruleTable[2].freq = 6;
	citys[3].ruleTable[2].type = 3;
	citys[3].ruleTable[2].startCityID = 3;
	citys[3].ruleTable[2].endCityID = 4;
	citys[3].ruleTable[2].duration = 2;
	citys[3].ruleTable[2].risk = 2;
	strcpy(citys[3].ruleTable[2].name, "car3-4:2h");
	citys[4].ruleTable[0].freq = 6;
	citys[4].ruleTable[0].type = 3;
	citys[4].ruleTable[0].startCityID = 4;
	citys[4].ruleTable[0].endCityID = 3;
	citys[4].ruleTable[0].duration = 2;
	citys[4].ruleTable[0].risk = 2;
	strcpy(citys[4].ruleTable[0].name, "car4-3:2h");
	citys[4].ruleTable[1].freq = 8;
	citys[4].ruleTable[1].type = 3;
	citys[4].ruleTable[1].startCityID = 4;
	citys[4].ruleTable[1].endCityID = 5;
	citys[4].ruleTable[1].duration = 5;
	citys[4].ruleTable[1].risk = 2;
	strcpy(citys[4].ruleTable[1].name, "car4-5:5h");
	citys[4].ruleTable[2].freq = 24;
	citys[4].ruleTable[2].type = 1;
	citys[4].ruleTable[2].startCityID = 4;
	citys[4].ruleTable[2].endCityID = 7;
	citys[4].ruleTable[2].duration = 5;
	citys[4].ruleTable[2].risk = 9;
	strcpy(citys[4].ruleTable[2].name, "plane4-7:5h");
	citys[5].ruleTable[0].freq = 12;
	citys[5].ruleTable[0].type = 3;
	citys[5].ruleTable[0].startCityID = 5;
	citys[5].ruleTable[0].endCityID = 8;
	citys[5].ruleTable[0].duration = 7;
	citys[5].ruleTable[0].risk = 2;
	strcpy(citys[5].ruleTable[0].name, "car5-8:7h");
	citys[5].ruleTable[1].freq = 12;
	citys[5].ruleTable[1].type = 2;
	citys[5].ruleTable[1].startCityID = 5;
	citys[5].ruleTable[1].endCityID = 6;
	citys[5].ruleTable[1].duration = 6;
	citys[5].ruleTable[1].risk = 5;
	strcpy(citys[5].ruleTable[1].name, "train5-6:6h");/*
	citys[5].ruleTable[2].freq = 4;
	citys[5].ruleTable[2].type = 3;
	citys[5].ruleTable[2].startCityID = 5;
	citys[5].ruleTable[2].endCityID = 4;
	citys[5].ruleTable[2].duration = 3;
	citys[5].ruleTable[2].risk = 2;
	strcpy(citys[5].ruleTable[2].name, "car5-4:2h");*/
	citys[6].ruleTable[0].freq = 24;
	citys[6].ruleTable[0].type = 3;
	citys[6].ruleTable[0].startCityID = 6;
	citys[6].ruleTable[0].endCityID = 0;
	citys[6].ruleTable[0].duration = 8;
	citys[6].ruleTable[0].risk = 2;
	strcpy(citys[6].ruleTable[0].name, "car6-0:8h");
	citys[6].ruleTable[1].freq = 24;
	citys[6].ruleTable[1].type = 1;
	citys[6].ruleTable[1].startCityID = 6;
	citys[6].ruleTable[1].endCityID = 4;
	citys[6].ruleTable[1].duration = 3;
	citys[6].ruleTable[1].risk = 9;
	strcpy(citys[6].ruleTable[1].name, "plane6-4:3h");
	citys[7].ruleTable[0].freq = 12;
	citys[7].ruleTable[0].type = 2;
	citys[7].ruleTable[0].startCityID = 7;
	citys[7].ruleTable[0].endCityID = 1;
	citys[7].ruleTable[0].duration = 7;
	citys[7].ruleTable[0].risk = 5;
	strcpy(citys[7].ruleTable[0].name, "train7-1:7h");
	citys[7].ruleTable[1].freq = 6;
	citys[7].ruleTable[1].type = 3;
	citys[7].ruleTable[1].startCityID = 7;
	citys[7].ruleTable[1].endCityID = 8;
	citys[7].ruleTable[1].duration = 4;
	citys[7].ruleTable[1].risk = 2;
	strcpy(citys[7].ruleTable[1].name, "car7-8:4h");
	citys[7].ruleTable[2].freq = 8;
	citys[7].ruleTable[2].type = 3;
	citys[7].ruleTable[2].startCityID = 7;
	citys[7].ruleTable[2].endCityID = 5;
	citys[7].ruleTable[2].duration = 6;
	citys[7].ruleTable[2].risk = 2;
	strcpy(citys[7].ruleTable[2].name, "car7-5:6h");
	citys[8].ruleTable[0].freq = 8;
	citys[8].ruleTable[0].type = 3;
	citys[8].ruleTable[0].startCityID = 8;
	citys[8].ruleTable[0].endCityID = 3;
	citys[8].ruleTable[0].duration = 4;
	citys[8].ruleTable[0].risk = 2;
	strcpy(citys[8].ruleTable[0].name, "car8-3:4h");
	citys[8].ruleTable[1].freq = 24;
	citys[8].ruleTable[1].type = 3;
	citys[8].ruleTable[1].startCityID = 8;
	citys[8].ruleTable[1].endCityID = 4;
	citys[8].ruleTable[1].duration = 1;
	citys[8].ruleTable[1].risk = 2;
	strcpy(citys[8].ruleTable[1].name, "car8-4:1h");
	citys[9].ruleTable[0].freq = 12;
	citys[9].ruleTable[0].type = 2;
	citys[9].ruleTable[0].startCityID = 9;
	citys[9].ruleTable[0].endCityID = 0;
	citys[9].ruleTable[0].duration = 7;
	citys[9].ruleTable[0].risk = 5;
	strcpy(citys[9].ruleTable[0].name, "train9-0:7h");
	citys[9].ruleTable[1].freq = 24;
	citys[9].ruleTable[1].type = 1;
	citys[9].ruleTable[1].startCityID = 9;
	citys[9].ruleTable[1].endCityID = 3;
	citys[9].ruleTable[1].duration = 4;
	citys[9].ruleTable[1].risk = 9;
	strcpy(citys[9].ruleTable[1].name, "plane9-3:4h");
	citys[9].ruleTable[2].freq = 6;
	citys[9].ruleTable[2].type = 3;
	citys[9].ruleTable[2].startCityID = 9;
	citys[9].ruleTable[2].endCityID = 7;
	citys[9].ruleTable[2].duration = 2;
	citys[9].ruleTable[2].risk = 2;
	strcpy(citys[9].ruleTable[2].name, "car9-7:2h");
	citys[9].ruleTable[3].freq = 4;
	citys[9].ruleTable[3].type = 3;
	citys[9].ruleTable[3].startCityID = 9;
	citys[9].ruleTable[3].endCityID = 8;
	citys[9].ruleTable[3].duration = 2;
	citys[9].ruleTable[3].risk = 2;
	strcpy(citys[9].ruleTable[3].name, "car9-8:2h");

	GenerateCityLog();//���ɳ�����Ϣ��־
}
void getOrder()
{
	FILE* fp = NULL;
	int i, j;
	printf("�ܹ��ж����ÿͣ�");
	scanf("%d", &activePass);//�����ʼ�ÿ���
	getchar();

	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "�˴γ������г�ʼ��%d���ÿͣ����£�\n", activePass);//������־�ļ�
		fclose(fp);
	}

	PASS* tmpPass = (PASS*)malloc(sizeof(PASS));
	*tmpPass = { 0 };
	//printf("%d\n", tmpPass->route[0].type);
	PASS* prePass = tmpPass;
	if (activePass)
	{
		passengers = tmpPass;
	}
	for (i = 0; i < activePass; i++)
	{
		prePass = tmpPass;
		printf("��%d���˿ͣ�\n", i + 1);
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
		
		fp = fopen(systemLogPath, "a+");
		if (fp)
		{
			if (tmpPass->request[0] == 0)
			{
				fprintf(fp, "�ÿ�������%s���ÿ�Ҫ��ͷ��մ�%s����%s\n", tmpPass->name,citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
			}
			else if (tmpPass->request[0] == 1)
			{
				fprintf(fp, "�ÿ�������%s���ÿ�Ҫ����ʱ%dСʱ��%s����%s\n", tmpPass->name, tmpPass->request[1], citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
			}
			fclose(fp);
		}
		//printf("%d %d %d %d %s\n", tmpPass->request[0], tmpPass->request[1], tmpPass->request[2], tmpPass->request[3], tmpPass->name); //�����ô���
		tmpPass = (PASS*)malloc(sizeof(PASS));
		*tmpPass = { 0 };
		prePass->next = tmpPass;
	}
	free(tmpPass);
	prePass->next = NULL;
	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "------------------------------------------------------------\n");//��־�ָ��У����ڲ鿴
		fclose(fp);
	}
}
void getOrderDefault()//����Ĭ���ÿ���Ϣ
{
	FILE* fp = NULL;
	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "�˴γ������г�ʼ��2���ÿͣ����£�\n");
		fclose(fp);
	}
	activePass = 2;
	PASS* tmpPass = (PASS*)malloc(sizeof(PASS));
	*tmpPass = { 0 };
	passengers = tmpPass;
	PASS* prePass = tmpPass;
	tmpPass->request[0] = 0;
	tmpPass->request[1] = INFINITE;
	tmpPass->request[2] = 0;
	tmpPass->request[3] = 4;
	strcpy(tmpPass->name, "P1");
	tmpPass->position = tmpPass->request[2];
	tmpPass->status = 2;
	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "�ÿ�������%s���ÿ�Ҫ��ͷ��մ�%s����%s\n", tmpPass->name, citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
		fclose(fp);
	}
	//printf("%d %d %d %d %s\n", tmpPass->request[0], tmpPass->request[1], tmpPass->request[2], tmpPass->request[3], tmpPass->name);
	tmpPass = (PASS*)malloc(sizeof(PASS));
	*tmpPass = { 0 };
	prePass->next = tmpPass;
	tmpPass->request[0] = 1;
	tmpPass->request[1] = 24;
	tmpPass->request[2] = 1;
	tmpPass->request[3] = 8;
	strcpy(tmpPass->name, "P2");
	tmpPass->position = tmpPass->request[2];
	tmpPass->status = 2;
	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "�ÿ�������%s���ÿ�Ҫ����ʱ24Сʱ��%s����%s\n", tmpPass->name, citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
		fclose(fp);
	}
	//printf("%d %d %d %d %s\n", tmpPass->request[0], tmpPass->request[1], tmpPass->request[2], tmpPass->request[3], tmpPass->name);
	tmpPass->next = NULL;
}