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
		fprintf(fp, "时间：%d\n",global_hour);
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
				//预置PREDAYS时间内的全部交通信息
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
		fprintf(fp, "旅客%s请注意：\n", tmpPass->name);
		fclose(fp);
	}
	printf("旅客%s请注意：\n", tmpPass->name);
	int i;
	if (tmpPass->status == 2)//在城市中
	{
		for (i = 0; i < 5; i++)
		{
			if (tmpPass->route[i].type == 1 || tmpPass->route[i].type == 2 || tmpPass->route[i].type == 3)
			{
				if (tmpPass->route[i].startCityID == tmpPass->position)//找到下一班交通工具是什么
				{
					if (global_hour == tmpPass->route[i].startTime)//如果是出发时间
					{
						fp = fopen(systemLogPath, "a+");
						if (fp)
						{
							fprintf(fp, "请乘坐%s\n", tmpPass->route[i].name);
							fclose(fp);
						}
						printf("请乘坐%s\n", tmpPass->route[i].name);
						tmpPass->status = 3;//更新状态
						tmpPass->position = i;//更新位置
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
							fprintf(fp, "请等待%d月%d日%d点出发的%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
							fclose(fp);
						}
						printf("请等待%d月%d日%d点出发的%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
						free(date);
						tmpPass->risk = tmpPass->risk + citys[tmpPass->position].risk;
						//printf("%f\n", tmpPass->risk);
						return tmpPass;
					}
				}
			}
		}
	}
	else if (tmpPass->status == 3)//在交通工具上
	{
		if (global_hour == tmpPass->route[tmpPass->position].endTime)//如果当前交通工具已达终点
		{
			if (tmpPass->route[tmpPass->position].endCityID == tmpPass->request[3])//已抵达最终目的地
			{
				fp = fopen(systemLogPath, "a+");
				if (fp)
				{
					fprintf(fp, "您已达目的地，累计风险是%f,感谢使用!\n", tmpPass->risk);
					fclose(fp);
				}
				printf("您已达目的地，累计风险是%f,感谢使用!\n",tmpPass->risk);
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
					fprintf(fp, "您乘坐的%s已到达%s\n", tmpPass->route[tmpPass->position].name, citys[tmpPass->route[tmpPass->position].endCityID].name);
					fclose(fp);
				}
				printf("您乘坐的%s已到达%s\n", tmpPass->route[tmpPass->position].name, citys[tmpPass->route[tmpPass->position].endCityID].name);
				tmpPass->status = 2;
				tmpPass->position = tmpPass->route[tmpPass->position].endCityID;
				for (i = 0; i < 5; i++)
				{
					if (tmpPass->route[i].type == 1 || tmpPass->route[i].type == 2 || tmpPass->route[i].type == 3)
					{
						if (tmpPass->route[i].startCityID == tmpPass->position)//找到下一班交通工具是什么
						{
							if (global_hour == tmpPass->route[i].startTime)//如果是出发时间
							{
								fp = fopen(systemLogPath, "a+");
								if (fp)
								{
									fprintf(fp, "请乘坐%s\n", tmpPass->route[i].name);
									fclose(fp);
								}
								printf("请乘坐%s\n", tmpPass->route[i].name);
								tmpPass->status = 3;//更新状态
								tmpPass->position = i;//更新位置
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
									fprintf(fp, "请等待%d月%d日%d点出发的%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
									fclose(fp);
								}
								printf("请等待%d月%d日%d点出发的%s\n", date[0], date[1], date[2], tmpPass->route[i].name);
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
				fprintf(fp, "您乘坐的%s将于%d月%d日%d点到达%s\n", tmpPass->route[tmpPass->position].name, date[0], date[1], date[2], citys[tmpPass->route[tmpPass->position].endCityID].name);
				fclose(fp);
			}
			printf("您乘坐的%s将于%d月%d日%d点到达%s\n", tmpPass->route[tmpPass->position].name, date[0], date[1], date[2], citys[tmpPass->route[tmpPass->position].endCityID].name);
			free(date);
			tmpPass->risk = tmpPass->risk + tmpPass->route[tmpPass->position].risk * citys[tmpPass->position].risk;
			//printf("%f\n", tmpPass->risk);
			return tmpPass;
		}
	}
}