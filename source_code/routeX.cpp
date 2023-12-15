#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <direct.h>
#include <string.h>

#include"routeX.h" 
#include"initX.h"

void generateG(float** arcs, int** offsets, int* prev, int** seri, float* dist, int vex)
{
	int i, j, k, m, n;
	i = vex;//更新点vex在offsets[i]下的相邻边权值
	//printf("Generate %d\n", i);
	for (k = 0; k < cityNum; k++)
	{
		arcs[i][k] = INFINITE;
		if (i != k)
		{
			offsets[i][k] = INFINITE;
		}
	}
	for (m = 0; m < cityNum; m++)//清除非当前城市的nflag标志
	{
		if (m != i)
		{
			for (n = 0; n < citys[m].transNum; n++)
			{
				citys[m].timeTable[n].nflag == 0;////////////////?
			}
		}
	}
	//更新有向图信息，记录新的交通下标与新的时间偏移量
	for (j = 0; j < citys[i].transNum; j++)
	{
		if ((citys[i].timeTable[j].nflag == 0) && (citys[i].timeTable[j].startTime >= offsets[prev[i]][i]) && (citys[i].timeTable[j].startTime >= global_hour))
		{
			float tmprisk = (citys[i].timeTable[j].startTime  - offsets[prev[i]][i]) * citys[i].risk + citys[i].timeTable[j].duration * citys[i].timeTable[j].risk * citys[i].risk;
			if (tmprisk < arcs[i][citys[i].timeTable[j].endCityID])
			{
				arcs[i][citys[i].timeTable[j].endCityID] = tmprisk;
				offsets[i][citys[i].timeTable[j].endCityID] = citys[i].timeTable[j].endTime;
				seri[i][citys[i].timeTable[j].endCityID] = j;
				//printf("%d %d:%f\n", i, citys[i].timeTable[j].endCityID, arcs[i][citys[i].timeTable[j].endCityID]);
			}
		}
	}
}

void findRoute(PASS* tmpPass)//魔改Dij求最短路径
{
	int start = tmpPass->request[2];
	int end = tmpPass->request[3];
	int i, j, k;
	float min, tmp;
	float** arcs = (float **)malloc(sizeof(float *) * cityNum);//arcs[i][j]记录有向图i->j两点间的权值
	int** offsets = (int**)malloc(sizeof(int*) * cityNum);//offsets[i]记录i城市所选交通的时间偏差量
	int* flag = (int*)malloc(sizeof(int) * cityNum);//flag[i]=1表示start到i的最小风险路径已经找到
	int* prev = (int*)malloc(sizeof(int) * cityNum);//prev[i]表示到i的最小风险路径的前驱点
	int** seri = (int**)malloc(sizeof(int*) * cityNum);//seri[i][j]表示从i城市出发到j城市的是哪趟交通
	float* dist = (float*)malloc(sizeof(float) * cityNum);//dist[i]表示start到i目前所得最小风险总和
	//float* predist = (float*)malloc(sizeof(float) * cityNum);//predist[i]记录上一个dist[i]，便于回溯（最终未使用）
	//int* peri = (int*)malloc(sizeof(int) * cityNum);//peri[i]表示到i城市所花时间（最终未使用）
	for (i = 0; i < cityNum; i++)//初始化参数值
	{
		offsets[i] = (int*)malloc(sizeof(int) * cityNum);
		flag[i] = 0;
		prev[i] = start;
		seri[i] = (int*)malloc(sizeof(int) * cityNum);
		dist[i] = INFINITE;
		//predist[i] = INFINITE;
		arcs[i]= (float *)malloc(sizeof(float) * cityNum);
		for (j = 0; j < cityNum; j++)
		{
			offsets[i][j] = INFINITE;
			seri[i][j] = 0;
			arcs[i][j] = INFINITE;
		}//end of for j
	}//end of for i
	if (global_hour == -1)
	{
		offsets[start][start] = 0;
	}
	else if (global_hour >= 0)
	{
		offsets[start][start] = global_hour;
	}
	generateG(arcs, offsets, prev, seri, dist, start);//以start点为起始，更新图
	for (i = 0; i < cityNum; i++)
	{
		dist[i] = arcs[start][i];
	}
	//对start点初始化
	flag[start] = 1;
	dist[start] = 0;
	for (i = 1; i < 1000; i++)//1000次循环未计算出则认为计算失败，显示错误信息
	{
		if (flag[end] == 0)
		{
			min = INFINITE;
			for (j = 0; j < cityNum; j++)
			{
				if (flag[j] == 0 && dist[j] < min)
				{
					min = dist[j];
					k = j;
				}
			}
			flag[k] = 1;//本轮找出的点
			if (offsets[prev[k]][k] > tmpPass->request[1])//如果所花时间已经超过旅客要求，则回溯
			{
				flag[k] = 0;
				citys[prev[k]].timeTable[seri[prev[k]][k]].nflag = 1;
				dist[k] = INFINITE;
				//dist[k] = predist[k];
				generateG(arcs, offsets, prev, seri, dist, prev[k]);
				int tmpflag = 0;
				int tmpprev = prev[k];
				prev[k] = start;
				while (tmpflag == 0 && k != start)//寻找下一个回溯点
				{
					k = tmpprev;
					flag[k] = 0;
					tmpprev = prev[k];
					for (j = 0; j < cityNum; j++)
					{
						if (offsets[k][j] < tmpPass->request[1])
						{
							flag[k] = 1;
							tmpflag = 1;
							prev[j] = k;
							dist[j] = dist[k] + arcs[k][j];
							min = dist[j];
							generateG(arcs, offsets, prev, seri, dist, j);
						}
					}
					if (tmpflag == 0)
					{
						citys[prev[k]].timeTable[seri[prev[k]][k]].nflag = 1;
						dist[k] = INFINITE;
						prev[k] = start;
						flag[k] = 0;
						//dist[k] = predist[k];
						generateG(arcs, offsets, prev, seri, dist, tmpprev);/////////////////////////////////
					}
				}
				if (flag[start] == 0)
				{
					printf("无法完成乘客要求\n");
					break;
				}
				else
				{
					k = j - 1;
					min = dist[k];
					for (j = 0; j < cityNum; j++)
					{
						if (arcs[prev[k]][j] == INFINITE) tmp = INFINITE;
						else tmp = min + arcs[prev[k]][j];
						if (flag[j] == 0 && tmp < dist[j])
						{
							//predist[j] = dist[j];
							dist[j] = tmp;
							prev[j] = prev[k];
						}
					}
				}
				
			}//end of if overtime
			else///如果所花时间还未超过旅客要求，则继续
			{
				generateG(arcs, offsets, prev, seri, dist, k);
				for (j = 0; j < cityNum; j++)
				{
	 				if (arcs[k][j] == INFINITE) tmp = INFINITE;
					else tmp = min + arcs[k][j];
					if (flag[j] == 0 && tmp < dist[j])
					{
						dist[j] = tmp;
						prev[j] = k;
					}
				}
			}//end of else
		}//end of if (flag[end] == 0)
		else break;//已达终点，结束循环
	}//end of for i
	if (flag[end] == 0 || flag[start] == 0)
	{
		printf("暂时无法完成请求，请稍后再试\n");
	}
	else
	{
		//存储计算所得的旅行方案
		i = 0;
		j = end;
		while (j != start)//计算换乘数
		{
			j = prev[j];
			i++;
		}
		j = end;
		i--;
		while (i >= 0)
		{
			int jtmp = j;
			j = prev[j];
			strcpy(tmpPass->route[i].name, citys[j].timeTable[seri[j][jtmp]].name);
			tmpPass->route[i].type = citys[j].timeTable[seri[j][jtmp]].type;
			tmpPass->route[i].startCityID = citys[j].timeTable[seri[j][jtmp]].startCityID;
			tmpPass->route[i].endCityID = citys[j].timeTable[seri[j][jtmp]].endCityID;
			tmpPass->route[i].duration = citys[j].timeTable[seri[j][jtmp]].duration;
			tmpPass->route[i].risk = citys[j].timeTable[seri[j][jtmp]].risk;
			tmpPass->route[i].startTime = citys[j].timeTable[seri[j][jtmp]].startTime;
			tmpPass->route[i].endTime = citys[j].timeTable[seri[j][jtmp]].endTime;
			i--;
		}
		//tmpPass->status = 1;
	}
	

	//释放申请的空间
	for (i = 0; i < cityNum; i++)
	{
		free(seri[i]);
		free(arcs[i]);
	}
	free(seri);
	free(arcs);
	free(offsets);
	free(flag);
	free(dist);

	//nflag归位
	for (i = 0; i < cityNum; i++)
	{
		for (j = 0; j < citys[i].transNum; j++)
		{
			citys[i].timeTable[j].nflag == 0;
		}
	}
}