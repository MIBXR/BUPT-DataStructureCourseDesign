#ifndef _INITX_H_
#define _INITX_H_



#define MAX_PASS 5 //���˿���
#define MAX_CITY 20 //��������
#define MAX_TRANS 1000 //ÿ��������󺽰���
#define INFINITE 65535//����

//ģ�ⶨʱ��
typedef struct myTimer
{
    char tName[20];
    int tInterval;
    time_t tLast;
    void (*pfunc)();
}MYTIMER;

//��ͨ��Ϣ�ṹ����
typedef struct trans
{
    char name[32];//����
    int type;//����0-1-2-3:��-��-��-��
    int startCityID;//��ʼվ
    int startTime;//����ʱ�䣺Сʱ
    int endCityID;//�յ�վ
    int endTime;//����ʱ�䣺Сʱ
    int duration;//��;��ʱ
    float risk;//��;����
    int nflag;//����λ��=1ʱ����
}TRANS;

//�ÿ�״̬�ṹ����
typedef struct pass
{
    char name[32];//����
    int status;//״̬��0-��Ч 1-�ȴ�������з��� 2-�ڳ����� 3-��·��
    int request[4];//Ҫ��0Xab��ʾ�ͷ���a->b��1X��ʾ��ʱXСʱa->b
    int position;//��ǰλ�ã��ڳ��ж������ڽ�ͨ�����ϣ�
    TRANS route[5];//���˱����5��
    float risk;//��ֹ��Ŀǰ���ۼƷ���ֵ
    struct pass *next;//��һ���˿�
}PASS;

//��ͨ���߱��Ź���
typedef struct rule
{
    int freq;//Ƶ�ʣ�����Сʱһ��
    char name[32];//����
    int type;//����1-2-3:��-��-��
    int startCityID;//��ʼվ
    int endCityID;//�յ�վ
    int duration;//��;��ʱ
    float risk;//��;����
}RULE;

//���нṹ����
typedef struct city
{
    char name[32];//������
    float risk;//���з���
    RULE ruleTable[10];
    int transNum;
    TRANS timeTable[MAX_TRANS];//����ǰ���1���ڵ�ʱ�̱�
}CITY;

extern PASS *passengers;//�ÿ�����ͷ
extern CITY citys[MAX_CITY];//������Ϣ����
extern int activePass; //��Ծ�˿���
extern int global_hour; //ϵͳʱ��
extern int cityNum;//��������
extern char systemLogPath[64];//ϵͳ��־�ļ�·�������·����
extern char interruptLogPath[64];//��ѯ��־�ļ�·�������·����
extern char otherLogPath[64];//������־�ļ�·�������·����


#endif // !_INITX_H_