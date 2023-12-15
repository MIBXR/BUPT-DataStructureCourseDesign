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
	printf("总共有多少城市：");
	scanf("%d",&cityNum);
	printf("输入所有城市风险及城市名，空格分隔，最多%d个城市，名字最长31字符，不得重名。\n按下回车读入一个城市：\n", MAX_CITY);
	for (i = 0; i < cityNum; i++)
	{
		scanf("%f", &citys[i].risk);//读入风险
		getchar();
		scanf("%s", citys[i].name);//读入城市名
		while (getchar() != '\n');//删除用户冗余输入
	}
	for (i = 0; i < cityNum; i++)
	{
		printf("输入%s的交通规则数,回车后输入具体信息：\n",citys[i].name);
		int ruleNum = 0;
		scanf("%d",&ruleNum);//读入规则数
		for (j = 0; j < ruleNum; j++)
		{
			printf("第%d个规则：\n", j + 1);
			printf("交通名称是（最长31字符）：");
			scanf("%s", citys[i].ruleTable[j].name);
			getchar();
			printf("交通类型是(飞机-1，火车-2，汽车-3）：");
			scanf("%d", &citys[i].ruleTable[j].type);
			printf("单位时间风险是：");
			scanf("%f", &citys[i].ruleTable[j].risk);
			citys[i].ruleTable[j].startCityID = i;
			printf("终点站是第几个城市（按刚刚输入的城市顺序从零计数）：");
			scanf("%d", &citys[i].ruleTable[j].endCityID);
			printf("耗时多少：");
			scanf("%d", &citys[i].ruleTable[j].duration);
			printf("频率是多少（多长时间一趟）：");
			scanf("%d", &citys[i].ruleTable[j].freq);
			getchar();
			//printf("%d %d %d %d %d %f %s\n", 
			//	citys[i].ruleTable[j].freq, 
			//	citys[i].ruleTable[j].type, 
			//	citys[i].ruleTable[j].startCityID, 
			//	citys[i].ruleTable[j].endCityID, 
			//	citys[i].ruleTable[j].duration,
			//	citys[i].ruleTable[j].risk,
			//	citys[i].ruleTable[j].name); //调试用代码
		}
	}
	while (getchar() != '\n');//删除用户冗余输入

	GenerateCityLog();//生成城市信息日志
}
void getDataDefault()//读取默认城市信息
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

	GenerateCityLog();//生成城市信息日志
}
void getOrder()
{
	FILE* fp = NULL;
	int i, j;
	printf("总共有多少旅客：");
	scanf("%d", &activePass);//读入初始旅客数
	getchar();

	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "此次程序运行初始有%d个旅客，如下：\n", activePass);//更新日志文件
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
		printf("第%d个乘客：\n", i + 1);
		printf("乘客名字是：");
		scanf("%s", tmpPass->name);
		getchar();
		printf("要求限时吗（0-不要求，1要求）：");
		scanf("%d", &tmpPass->request[0]);
		if (tmpPass->request[0] == 1)
		{
			printf("限时多少小时：");
			scanf("%d", &tmpPass->request[1]);

		}
		else if (tmpPass->request[0] == 0)
		{
			tmpPass->request[1] = INFINITE;
		}
		printf("出发地是哪个城市（按刚刚输入的城市顺序从零计数）：");
		scanf("%d", &tmpPass->request[2]);
		printf("目的地是哪个城市（按刚刚输入的城市顺序从零计数）：");
		scanf("%d", &tmpPass->request[3]);
		getchar();

		tmpPass->position = tmpPass->request[2];
		tmpPass->status = 2;
		
		fp = fopen(systemLogPath, "a+");
		if (fp)
		{
			if (tmpPass->request[0] == 0)
			{
				fprintf(fp, "旅客姓名：%s；旅客要求低风险从%s到达%s\n", tmpPass->name,citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
			}
			else if (tmpPass->request[0] == 1)
			{
				fprintf(fp, "旅客姓名：%s；旅客要求限时%d小时从%s到达%s\n", tmpPass->name, tmpPass->request[1], citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
			}
			fclose(fp);
		}
		//printf("%d %d %d %d %s\n", tmpPass->request[0], tmpPass->request[1], tmpPass->request[2], tmpPass->request[3], tmpPass->name); //调试用代码
		tmpPass = (PASS*)malloc(sizeof(PASS));
		*tmpPass = { 0 };
		prePass->next = tmpPass;
	}
	free(tmpPass);
	prePass->next = NULL;
	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "------------------------------------------------------------\n");//日志分隔行，便于查看
		fclose(fp);
	}
}
void getOrderDefault()//读入默认旅客信息
{
	FILE* fp = NULL;
	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "此次程序运行初始有2个旅客，如下：\n");
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
		fprintf(fp, "旅客姓名：%s；旅客要求低风险从%s到达%s\n", tmpPass->name, citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
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
		fprintf(fp, "旅客姓名：%s；旅客要求限时24小时从%s到达%s\n", tmpPass->name, citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
		fclose(fp);
	}
	//printf("%d %d %d %d %s\n", tmpPass->request[0], tmpPass->request[1], tmpPass->request[2], tmpPass->request[3], tmpPass->name);
	tmpPass->next = NULL;
}