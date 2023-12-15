#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <direct.h>
#include<time.h>

#include"logX.h"
#include"initX.h"

void GenerateCityLog()
{
	int i, j;
	FILE* fp = NULL;
	fp = fopen(systemLogPath, "a+");
	if (fp)
	{
		fprintf(fp, "此次程序运行有%d个城市，如下：\n", cityNum);
		for (i = 0; i < cityNum; i++)
		{
			fprintf(fp, "%d. 城市名：%s；单位时间风险值：%f；各种交通方式发车表：\n", i + 1, citys[i].name, citys[i].risk);
			for (j = 0; j < 3; j++)
			{
				if (citys[i].ruleTable[j].freq)
				{
					if (citys[i].ruleTable[j].type == 1)
					{
						fprintf(fp, "交通名称：%s；交通类型：飞机；单位时间风险：%f；出发站：%s；终点站：%s；耗时：%d；频率：每%d小时一趟。\n",
							citys[i].ruleTable[j].name,
							citys[i].ruleTable[j].risk,
							citys[citys[i].ruleTable[j].startCityID].name,
							citys[citys[i].ruleTable[j].endCityID].name,
							citys[i].ruleTable[j].duration,
							citys[i].ruleTable[j].freq);
					}
					else if (citys[i].ruleTable[j].type == 2)
					{
						fprintf(fp, "交通名称：%s；交通类型：火车；单位时间风险：%f；出发站：%s；终点站：%s；耗时：%d；频率：每%d小时一趟。\n",
							citys[i].ruleTable[j].name,
							citys[i].ruleTable[j].risk,
							citys[citys[i].ruleTable[j].startCityID].name,
							citys[citys[i].ruleTable[j].endCityID].name,
							citys[i].ruleTable[j].duration,
							citys[i].ruleTable[j].freq);
					}
					else if (citys[i].ruleTable[j].type == 3)
					{
						fprintf(fp, "交通名称：%s；交通类型：汽车；单位时间风险：%f；出发站：%s；终点站：%s；耗时：%d；频率：每%d小时一趟。\n",
							citys[i].ruleTable[j].name,
							citys[i].ruleTable[j].risk,
							citys[citys[i].ruleTable[j].startCityID].name,
							citys[citys[i].ruleTable[j].endCityID].name,
							citys[i].ruleTable[j].duration,
							citys[i].ruleTable[j].freq);
					}
				}
			}
		}
		fprintf(fp, "------------------------------------------------------------\n");
		fclose(fp);
	}
}

void timeChange(int* date, int hours)
{
	//date[3]:月-日-小时
	date[1] = (hours / 24) % 30 + 1;
	date[0] = (hours / 720) % 12 + 1;
	date[2] = hours % 24;
}