#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <direct.h>
#include <string.h>

#include"outputX.h"
#include"initX.h"
#include"logX.h"

void outputCitys()
{
	int i, j;
	for (i = 0; i < cityNum; i++)
	{
		printf("city\n");
		for (j = 0; j < citys[i].transNum; j++)
		{
			printf("trans\n");
			printf("%s %d %d %d %d %d %d %f\n",
				citys[i].timeTable[j].name,
				citys[i].timeTable[j].type,
				citys[i].timeTable[j].startCityID,
				citys[i].timeTable[j].startTime,
				citys[i].timeTable[j].endCityID,
				citys[i].timeTable[j].endTime,
				citys[i].timeTable[j].duration,
				citys[i].timeTable[j].risk);
		}
	}
}

void outputRoute(PASS* tmpPass)
{
	FILE* fp = NULL;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (tmpPass->route[i].type == 1 || tmpPass->route[i].type == 2 || tmpPass->route[i].type == 3)
		{
			int* date = (int*)malloc(sizeof(int) * 3);
			timeChange(date, tmpPass->route[i].startTime);//转换时间
			fp = fopen(interruptLogPath, "a+");
			if (fp)
			{
				fprintf(fp, "乘坐%s在%d月%d日%d点从%s出发经过%d小时到达%s\n",
					tmpPass->route[i].name,
					date[0], date[1], date[2],
					citys[tmpPass->route[i].startCityID].name,
					tmpPass->route[i].duration,
					citys[tmpPass->route[i].endCityID].name);
				fclose(fp);
			}
			printf("乘坐%s在%d月%d日%d点从%s出发经过%d小时到达%s\n",
				tmpPass->route[i].name,
				date[0], date[1], date[2],
				citys[tmpPass->route[i].startCityID].name,
				tmpPass->route[i].duration,
				citys[tmpPass->route[i].endCityID].name);
			free(date);
		}
	}
}