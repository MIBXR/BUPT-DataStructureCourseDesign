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
		printf("请输入要查询的旅客名字：");
		scanf("%s", inqName);
		int* date = (int*)malloc(sizeof(int) * 3);
		timeChange(date, global_hour);//将系统时间转化为月-日-小时的形式
		fp = fopen(interruptLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "于%d月%d日%d点查询旅客%s信息，", date[0], date[1], date[2], inqName);
			fclose(fp);
		}
		while (getchar() != '\n');//删除用户冗余输入
		while (tmpPass)//寻找名为inqName的旅客是否存在
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
		if (flag == 1)//旅客存在
		{
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "成功：", inqName);
				fclose(fp);
			}
			if (tmpPass->status == 2)//在城市中
			{
				fp = fopen(interruptLogPath, "a+");
				if (fp)
				{
					fprintf(fp, "旅客%s位于城市%s中，", tmpPass->name, citys[tmpPass->position].name);
					fclose(fp);
				}
				printf("旅客%s位于城市%s中，", tmpPass->name, citys[tmpPass->position].name);
				for (i = 0; i < 5; i++)
				{
					if (tmpPass->route[i].type == 1 || tmpPass->route[i].type == 2 || tmpPass->route[i].type == 3)
					{
						if (tmpPass->route[i].startCityID == tmpPass->position)//找到下一班交通工具是什么
						{
							int* date=(int*)malloc(sizeof(int) * 3);
							timeChange(date, tmpPass->route[i].startTime);
							fp = fopen(interruptLogPath, "a+");
							if (fp)
							{
								fprintf(fp, "正在等待%d月%d日%d点出发的%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
								fclose(fp);
							}
							printf("正在等待%d出发的%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
							free(date);
						}
					}
				}
			}
			else if (tmpPass->status == 3)//在交通工具上
			{
				int* date = (int*)malloc(sizeof(int) * 3);
				timeChange(date, tmpPass->route[tmpPass->position].endTime);
				fp = fopen(interruptLogPath, "a+");
				if (fp)
				{
					fprintf(fp, "旅客正在乘坐%s，将于%d月%d日%d点到达%s\n", tmpPass->route[tmpPass->position].name, date[0], date[1], date[2], citys[tmpPass->route[tmpPass->position].endCityID].name);
					fclose(fp);
				}
				printf("旅客正在乘坐%s，将于%d月%d日%d点到达%s\n", tmpPass->route[tmpPass->position].name, date[0], date[1], date[2], citys[tmpPass->route[tmpPass->position].endCityID].name);
				free(date);
			}
			printf("旅客的完整行程规划：\n");
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "旅客的完整行程规划：\n");
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
		else//旅客不存在
		{
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "失败：查无此人\n");
				fprintf(fp, "------------------------------------------------------------\n");
				fclose(fp);
			}
			printf("未找到旅客%s\n", inqName);
			printf("------------------------------------------------------------\n");
		}
		flag = 0;
		printf("是否继续查询？Y/N：");
		command = getchar();
	}
	while (getchar() != '\n');//删除用户冗余输入
}

void addPass()
{
	FILE* fp = NULL;
	char command = 'n';
	PASS* tmpPass;
	PASS* prePass;
	//printf("添加旅客需按格式输入信息，格式“要求（0/1） 限时 起点 终点 名字”。例如：0 0 a b P1 表示P1要求低风险a->b，1 2 a b P2 表示P2限时2小时a->b\n按下回车读入下一个旅客：\n");
	printf("确认要添加新旅客吗？Y/N：");
	command = getchar();
	while (getchar() != '\n');//删除用户冗余输入
	while (command == 'y' || command == 'Y')
	{
		int* date = (int*)malloc(sizeof(int) * 3);
		timeChange(date, global_hour);
		fp = fopen(interruptLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "在%d月%d日%d点添加旅客：\n", date[0], date[1], date[2]);
			fclose(fp);
		}
		tmpPass = passengers;//链接新节点至passenger链表
		if (passengers != NULL)//如果当前还有旅客
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
		fp = fopen(interruptLogPath, "a+");
		if (fp)
		{
			if (tmpPass->request[0] == 0)
			{
				fprintf(fp, "旅客姓名：%s；旅客要求低风险从%s到达%s\n", tmpPass->name, citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
			}
			else if (tmpPass->request[0] == 1)
			{
				fprintf(fp, "旅客姓名：%s；旅客要求限时%d小时从%s到达%s\n", tmpPass->name, tmpPass->request[1], citys[tmpPass->request[2]].name, citys[tmpPass->request[3]].name);
			}
			fclose(fp);
		}
		if (tmpPass->request[0] == 0)
		{
			tmpPass->request[1] = INFINITE;
		}
		//printf("%d %d %d %d %s\n", tmpPass->request[0], tmpPass->request[1], tmpPass->request[2], tmpPass->request[3], tmpPass->name);
		tmpPass->next = NULL;

		findRoute(tmpPass);//计算新旅客的旅行计划

		//展示计划并写入日志
		printf("生成如下旅行计划：\n");
		fp = fopen(interruptLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "生成如下旅行计划：\n");
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
			fprintf(fp, "当前时间%d月%d日%d点,添加新旅客%s\n", date[0], date[1], date[2], tmpPass->name);
			fclose(fp);
		}
		free(date);
		updatePassStage(NULL, tmpPass);//更新旅客状态
		fp = fopen(systemLogPath, "a+");
		if (fp)
		{
			fprintf(fp, "------------------------------------------------------------\n");
			fclose(fp);
		}
		printf("继续添加旅客？Y/N：");
		command = getchar();
		while (getchar() != '\n');//删除用户冗余输入
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
	printf("添加交通需先输入城市名字，回车后按提示操作。\n");
	printf("确认要添加新交通吗？Y/N：");
	command = getchar();
	while (getchar() != '\n');//删除用户冗余输入
	while (command == 'y' || command == 'Y')
	{
		printf("请输入要添加交通的城市名：");
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
				fprintf(fp, "城市%s添加新交通规则：", cName);
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
				printf("此趟交通终点为？（请输入城市名字）：");
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
					printf("没有名为“%s”的城市", cName);
				}
			}
			printf("请依次键入频率（多长时间一趟） 类型（1 - 2 - 3:飞 - 火 - 汽），时长，风险：（空格分隔）");
			scanf("%d", &citys[i].ruleTable[j].freq);
			scanf("%d", &citys[i].ruleTable[j].type);
			scanf("%d", &citys[i].ruleTable[j].duration);
			scanf("%f", &citys[i].ruleTable[j].risk);
			getchar();
			printf("最后，请键入交通名字：");
			scanf("%s", citys[i].ruleTable[j].name);
			getchar();
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "交通名称：%s；交通类型：飞机；单位时间风险：%f；出发站：%s；终点站：%s；耗时：%d；频率：每%d小时一趟。\n",
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
			printf("无名为“%s”的城市\n", cName);
		}
		printf("------------------------------------------------------------\n");
		printf("继续添加交通？Y/N：");
		command = getchar();
		while (getchar() != '\n');//删除用户冗余输入
	}
}
