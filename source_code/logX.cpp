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
		fprintf(fp, "�˴γ���������%d�����У����£�\n", cityNum);
		for (i = 0; i < cityNum; i++)
		{
			fprintf(fp, "%d. ��������%s����λʱ�����ֵ��%f�����ֽ�ͨ��ʽ������\n", i + 1, citys[i].name, citys[i].risk);
			for (j = 0; j < 3; j++)
			{
				if (citys[i].ruleTable[j].freq)
				{
					if (citys[i].ruleTable[j].type == 1)
					{
						fprintf(fp, "��ͨ���ƣ�%s����ͨ���ͣ��ɻ�����λʱ����գ�%f������վ��%s���յ�վ��%s����ʱ��%d��Ƶ�ʣ�ÿ%dСʱһ�ˡ�\n",
							citys[i].ruleTable[j].name,
							citys[i].ruleTable[j].risk,
							citys[citys[i].ruleTable[j].startCityID].name,
							citys[citys[i].ruleTable[j].endCityID].name,
							citys[i].ruleTable[j].duration,
							citys[i].ruleTable[j].freq);
					}
					else if (citys[i].ruleTable[j].type == 2)
					{
						fprintf(fp, "��ͨ���ƣ�%s����ͨ���ͣ��𳵣���λʱ����գ�%f������վ��%s���յ�վ��%s����ʱ��%d��Ƶ�ʣ�ÿ%dСʱһ�ˡ�\n",
							citys[i].ruleTable[j].name,
							citys[i].ruleTable[j].risk,
							citys[citys[i].ruleTable[j].startCityID].name,
							citys[citys[i].ruleTable[j].endCityID].name,
							citys[i].ruleTable[j].duration,
							citys[i].ruleTable[j].freq);
					}
					else if (citys[i].ruleTable[j].type == 3)
					{
						fprintf(fp, "��ͨ���ƣ�%s����ͨ���ͣ���������λʱ����գ�%f������վ��%s���յ�վ��%s����ʱ��%d��Ƶ�ʣ�ÿ%dСʱһ�ˡ�\n",
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
	//date[3]:��-��-Сʱ
	date[1] = (hours / 24) % 30 + 1;
	date[0] = (hours / 720) % 12 + 1;
	date[2] = hours % 24;
}