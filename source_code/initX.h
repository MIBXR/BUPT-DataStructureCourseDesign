#ifndef _INITX_H_
#define _INITX_H_



#define MAX_PASS 5 //最大乘客数
#define MAX_CITY 20 //最大城市数
#define MAX_TRANS 1000 //每个城市最大航班数
#define INFINITE 65535//无穷

//模拟定时器
typedef struct myTimer
{
    char tName[20];
    int tInterval;
    time_t tLast;
    void (*pfunc)();
}MYTIMER;

//交通信息结构定义
typedef struct trans
{
    char name[32];//名字
    int type;//类型0-1-2-3:无-飞-火-汽
    int startCityID;//起始站
    int startTime;//出发时间：小时
    int endCityID;//终点站
    int endTime;//到达时间：小时
    int duration;//旅途耗时
    float risk;//旅途风险
    int nflag;//屏蔽位，=1时屏蔽
}TRANS;

//旅客状态结构定义
typedef struct pass
{
    char name[32];//名字
    int status;//状态：0-无效 1-等待获得旅行方案 2-在城市中 3-在路上
    int request[4];//要求：0Xab表示低风险a->b，1X表示限时X小时a->b
    int position;//当前位置（在城市逗留或在交通工具上）
    TRANS route[5];//换乘表，最多5趟
    float risk;//截止到目前的累计风险值
    struct pass *next;//下一个乘客
}PASS;

//交通工具编排规则
typedef struct rule
{
    int freq;//频率：多少小时一次
    char name[32];//名字
    int type;//类型1-2-3:飞-火-汽
    int startCityID;//起始站
    int endCityID;//终点站
    int duration;//旅途耗时
    float risk;//旅途风险
}RULE;

//城市结构定义
typedef struct city
{
    char name[32];//城市名
    float risk;//城市风险
    RULE ruleTable[10];
    int transNum;
    TRANS timeTable[MAX_TRANS];//城市前后各1周内的时刻表
}CITY;

extern PASS *passengers;//旅客链表头
extern CITY citys[MAX_CITY];//城市信息数组
extern int activePass; //活跃乘客数
extern int global_hour; //系统时间
extern int cityNum;//城市数量
extern char systemLogPath[64];//系统日志文件路径（相对路径）
extern char interruptLogPath[64];//查询日志文件路径（相对路径）
extern char otherLogPath[64];//其他日志文件路径（相对路径）


#endif // !_INITX_H_