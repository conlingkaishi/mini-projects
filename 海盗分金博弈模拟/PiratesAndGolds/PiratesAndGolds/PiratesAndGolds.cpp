// PiratesAndGolds.cpp : Defines the entry point for the console application.
//

/*
�����ֽ���
��Ϸ���򣺰��������ϾͿ���ͨ���������ӵ����

��Ʊ���(�Լ��϶�ͶƱ���Լ���ͳ����Ҫ����Ʊ��):
|��ǰ������� |��Ҫ��Ʊ�� |
|----------- |---------- |
|1 |0 |
|2 |0 |
|3 |1 |
|4 |1 |
|5 |2 |
|6 |2 |
|7 |3 |
|8 |3 |
......
��ʽ(C�������γ���)�� 
��ǰ�������Ϊ����ʱ: ��ǰ������� / 2
��ǰ�������Ϊż��ʱ: ��ǰ������� / 2 - 1

�㷨ģ��
5�˵����

5
100

5   4
0   100

5   4   3
1   0   99

5   4   3   2
0   1   0   99

5   4   3   2   1
1   0   1   0   98

*/

#include "stdafx.h"
#include <windows.h>

#define PIRATE_NUMBER 208
#define GOLD_SUM 100

//���ڱ�Ǵ˺���ͶƱ�����Ĭ��Ϊdefault������Ʊ����Ϊ�˺�������õĽ�����
#define VOTE_TAG_DEFAULT -1

/*�ڼ���ģ���б����ĺ�������ʹ�����ý�ң����ǻ��ǻ�������֧��ǰ����ˣ���Ϊ�����֧��
ǰ����ˣ��ֵ���������ͷĿʱ����������*/
#define VOTE_TAG_VOTE_FOR_LIVING -2   

//���ڴ�ӡ��ɫ
#define GREEN 0x2F
#define RED 0xCF

//#define __DEBUG_MODE

/*����Ŀǰ��������������Ҫ����Ʊ����Ʊ���������Լ�����һƱ��*/
int get_needed_vote_number(int nCurrentSurvivals);

//����ͶƱ���ͳ������(����ͷ���Լ�ͶƱ�����ͳ�ƣ���Ϊ����ͬ��)
int reset_vote_status(int nVoteStatus[], int nCurrentSurvivals);

//����������ͷ�죩�ҵ�Ŀǰ���ֽ������ٵĺ���
int find_the_poorest_pirate(int nGoldPossession[], int nVoteStatus[],
  int nCurrentSurvivals);

//���·���Ƹ�
int redistribute_golds(int nGoldPossession[], int nVoteStatus[],
  int nCurrentSurvivals);

//��ӡ��ǰ������
int print_current_gold_possession(int nGoldPossession[], int nVoteStatus[],
  int nCurrentSurvivals);

//��ӡ��ɫ����
int print_with_color(const char* chString, int nColor);

//ͳ�Ʒ���Ʊ����
int get_negative_vote_number(int nVoteStatus[], int nCurrentSurvivals);

//ͳ��Ϊ�˸���ԭ�򣨱��粻�뵱ͷĿ����Ϊ��ͷĿ��������Ҫ���棩һ����Ͷ�����޳�Ʊ������
int get_granted_positive_vote_number(int nVoteStatus[], int nCurrentSurvivals);

//�������к���״̬Ϊ��Į
int reset_vote_status_to_indifference(int nVoteStatus[], int nCurrentSurvivals);

int main()
{
  int nGoldPossession[PIRATE_NUMBER] = { 0 };
  int nVoteStatus[PIRATE_NUMBER] = { 0 };
  int nGoldSum = GOLD_SUM;
  int nVoteNumberNeeded = 0;
  int nBefriendTarget = 0;    //�����ݴ浱ǰ��Ҫ����£���������
  int nGoldDelivered = 0;

  /*��־λ�����ڱ���Ƿ��к���Ϊ�������������޳ɺ���ͷĿ�ľ�������Ϊ�ڼ���ģ����������
  �����Ϻ���ͷĿ��������������״̬��ԭ������Ϊ�����ĺ������ˣ��ͻᵼ�±����������ϴ�
  ���Ի����������������ϴ�һ����������������С���Ǿ�������һ������ɡ����ԭ���������޳�
  ͷĿ������״̬��������û��Ǯ�����Ͷ����Ʊ��״̬������������ʵ�������̬ת�䣨һ��
  �б������ϴ������������ô���е�Ϊ��������������޳ɵ��ˣ������Ĭ�ϵġ���Į��״̬����
  ��������һ��������ϴ��Լ�������*/
  int bFlagAnyoneCrysForLiving = -1;    

  int i = 0;
  int j = 0;

  /*ģ�ⲩ�Ĺ��̡���Ϊi���˼������ܣ���������Ŀǰ���ĺ���������Ϊ�˿ɶ��ԣ�i��ֵ��1��
  ʼ��*/
  for (i = 1; i <= PIRATE_NUMBER; i++)
  {
    if (i == 203)
    {
      system("cls");
    }

    //����ͶƱͳ��
    reset_vote_status(nVoteStatus, i);

    /*̽���Ƿ���Ϊ�������������Ͷ�޳�Ʊ���ˣ�����Ϊ�˵��б������ϴ������������������
    ���к�����״̬Ϊ����Į����*/
    if (get_granted_positive_vote_number(nVoteStatus, i))
    {
      bFlagAnyoneCrysForLiving = 1;
    }
    else
    {
      bFlagAnyoneCrysForLiving = 0;
    }

    //���÷����Ľ����Ŀ
    nGoldDelivered = 0;

    //�ȸ��Լ�ͶһƱ���˴��޹ز����߼�����Ϊ�˷���������ͶƱ���ͳ�ƣ�
    nVoteStatus[i - 1] = GOLD_SUM;

    //�����Ҫ��Ʊ������
    nVoteNumberNeeded = get_needed_vote_number(i);

    //��Ϊ�ڼ���ģ���б��������Բ��뵱ͷĿ��һ����Ͷ�޳�Ʊ�ĺ�������Ҫ����Ʊ��
    nVoteNumberNeeded -= get_granted_positive_vote_number(nVoteStatus, i);

    //��ʼ��Ʊ��Ϊ�����ԣ��ҵ�Ŀǰ�ֵý������ٵ��ˣ�����������+1����
    /*�˴��߼������Ͻ�����Ϊ�ٶ�����ȥ�Ľ��С�ڽ�������Ϳ��Լ�����Ʊ���������˽�ʣ1ö
    ��ҵ���Ҫ����2ö�����Ͻ�Ҳſ�����Ʊ�ɹ�����������˵��ǣ������ֽ����ѧ�������
    �ǿ����ҵ�һ�����Ҳû�еĺ������л�¸����ʵ�ϣ�ÿ�λ�¸���ǰ�һ��������0��ұ�Ϊ1
    ��ҡ�*/
    /*��֮������ı�����ͶƱ�߼���������Ҫһ�����ϵĺ����޳ɣ����������ڵ�һ�����һ��
    ���ϣ�����ѭ��������Ҫ�޸ġ�*/
    while (nVoteNumberNeeded > 0 && nGoldDelivered < GOLD_SUM)
    {
      nBefriendTarget = find_the_poorest_pirate(nGoldPossession, nVoteStatus,
        i);

      //����ƱĿ�����ý��+1
      nVoteStatus[nBefriendTarget] = nGoldPossession[nBefriendTarget] + 1;
      nGoldDelivered += nVoteStatus[nBefriendTarget];


      //��Ʊ�ɹ�
      nVoteNumberNeeded--;
    }

    /*�������Ʊ������֤������ͷĿ��������Ǵ˺���ͷĿ��ͶƱ����Ϊ
    VOTE_TAG_VOTE_FOR_LIVING,�����������Ը��ǿ�ҵģ���������һ��ģ�⿪ʼʱ����ͶƱͳ
    �ƵĹ����У�����Ը���ᱻĨȥ�����
    int reset_vote_status(int nVoteStatus[], int nCurrentSurvivals)
    ��������*/
    if (nVoteNumberNeeded > 0)
    {
      nVoteStatus[i - 1] = VOTE_TAG_VOTE_FOR_LIVING;
    }

    //���·���Ƹ�
    redistribute_golds(nGoldPossession, nVoteStatus, i);

#ifdef __DEBUG_MODE
    //����ģʽ����ӡ��ǰ������
    print_current_gold_possession(nGoldPossession, nVoteStatus, i);

#endif // __DEBUG_MODE

    //�����ϴ��������������������к�����״̬Ϊ��Į
    if (i != PIRATE_NUMBER && bFlagAnyoneCrysForLiving == 1
        && nVoteNumberNeeded == 0)
    {
      reset_vote_status_to_indifference(nVoteStatus, i);
    }
  }
  
  //��ӡ���ս��
  print_current_gold_possession(nGoldPossession, nVoteStatus, PIRATE_NUMBER);

  return 0;
}

/*����Ŀǰ��������������Ҫ����Ʊ����Ʊ���������Լ�����һƱ��*/
int get_needed_vote_number(int nCurrentSurvivals)
{
  //ż�����
  if (nCurrentSurvivals % 2 == 0)
  {
    return nCurrentSurvivals / 2 - 1;
  }
  else
  {
    return nCurrentSurvivals / 2;
  }

  return -1;
}

//����ͶƱ���ͳ������(����ͷ���Լ�ͶƱ�����ͳ�ƣ���Ϊ����ͬ��)
/*��Ϊ�����ڲ�Ӱ���Լ����������£����ڿ������������������ǵ�Ĭ��ͶƱ���Ƿ���Ʊ��
VOTE_TAG_DEFAULT�����ڼ���ģ���б����ĺ��������ǻ�������Ͷ�޳�Ʊ��
VOTE_TAG_VOTE_FOR_LIVING����Ϊ�˻�����*/
int reset_vote_status(int nVoteStatus[], int nCurrentSurvivals)
{
  int i = 0;
  
  for (i = 0; i < nCurrentSurvivals - 1; i++)
  {
    if (nVoteStatus[i] != VOTE_TAG_VOTE_FOR_LIVING)
    {
      nVoteStatus[i] = VOTE_TAG_DEFAULT;
    }
  }

  return 0;
}

//�������к���״̬Ϊ��Į
int reset_vote_status_to_indifference(int nVoteStatus[], int nCurrentSurvivals)
{
  int i = 0;

  for (i = 0; i < nCurrentSurvivals - 1; i++)
  {
    nVoteStatus[i] = VOTE_TAG_DEFAULT;
  }

  return 0;
}

//����������ͷ�죩�ҵ�Ŀǰ���ֽ������ٵĺ���
int find_the_poorest_pirate(int nGoldPossession[], int nVoteStatus[], 
  int nCurrentSurvivals)
{
  int nMinimumGold = GOLD_SUM + 1;
  int nThePoorestPirate = -1;
  int i = 0;

  for (i = 0; i < nCurrentSurvivals - 1; i++)
  {
    //�����������ĳ��н�ұ�Ŀǰ��С�������С����������ͶƱ״̬�ǡ�δ����Ʊ��
    if (nGoldPossession[i] < nMinimumGold && nVoteStatus[i] == VOTE_TAG_DEFAULT)
    {
      nMinimumGold = nGoldPossession[i];
      nThePoorestPirate = i;
    }
  }

  return nThePoorestPirate;
}

//���·���Ƹ�
int redistribute_golds(int nGoldPossession[], int nVoteStatus[], 
  int nCurrentSurvivals)
{
  int i = 0;
  int nGoldDelivered = 0;

  //1.�������˵ĲƸ�����
  for (i = 0; i < nCurrentSurvivals; i++)
  {
    nGoldPossession[i] = 0;
  }

  //2.������Ʊͳ�ƣ�������������µĽ���
  for (i = 0; i < nCurrentSurvivals - 1; i++)
  {
    if (nVoteStatus[i] >= 0)
    {
      nGoldPossession[i] = nVoteStatus[i];
      nGoldDelivered += nGoldPossession[i];
    }
  }

  //3.ʣ�µĽ��ӣ����ϴ�����
  nGoldPossession[nCurrentSurvivals - 1] = GOLD_SUM - nGoldDelivered;

  return 0;
}

//��ӡ��ǰ������
int print_current_gold_possession(int nGoldPossession[], int nVoteStatus[],
  int nCurrentSurvivals)
{
  int i = 0;
  int nNegativeVote = 0;

  nNegativeVote = get_negative_vote_number(nVoteStatus, nCurrentSurvivals);

  //����
  for (i = 0; i < nCurrentSurvivals; i++)
  {
    printf("%3d��%5d��� ", 
           i + 1,
           nGoldPossession[i]);

    nVoteStatus[i] == VOTE_TAG_DEFAULT ? 
                      print_with_color("����", RED) : 
                      print_with_color("�޳�", GREEN);

    if (i != nCurrentSurvivals - 1 
        && nVoteStatus[i] == VOTE_TAG_VOTE_FOR_LIVING)
    {
      printf(" Ϊ�˲���ͷĿ");
    }

    printf("\r\n");
  }

  printf("������Ŀ��%d �޳�Ʊ%3d ����Ʊ%3d\r\n"
    "���Խ��ս����Խ�ߣ���������Ǻ���ͷĿ��\r\n"
    "\r\n",
    nCurrentSurvivals, nCurrentSurvivals - nNegativeVote, nNegativeVote);

  nCurrentSurvivals - nNegativeVote >= nNegativeVote ?
                                     print_with_color("����ͷĿ���", GREEN) :
                                     print_with_color("����ͷĿ����", RED);
  printf("\r\n");

  printf("=====================================\r\n"
         "\r\n");   //DEBUGģʽ�»��δ�ӡ

  return 0;
}

//ͳ�Ʒ���Ʊ����
int get_negative_vote_number(int nVoteStatus[], int nCurrentSurvivals)
{
  int i = 0;
  int nCount = 0;

  for (i = 0; i < nCurrentSurvivals - 1; i++)
  {
    if (nVoteStatus[i] == VOTE_TAG_DEFAULT)
    {
      nCount++;
    }
  }

  return nCount;
}

//ͳ��Ϊ�˸���ԭ�򣨱��粻�뵱ͷĿ����Ϊ��ͷĿ��������Ҫ���棩һ����Ͷ�����޳�Ʊ������
int get_granted_positive_vote_number(int nVoteStatus[], int nCurrentSurvivals)
{
  int i = 0;
  int nCount = 0;

  for (i = 0; i < nCurrentSurvivals - 1; i++)
  {
    if (nVoteStatus[i] == VOTE_TAG_VOTE_FOR_LIVING)
    {
      nCount++;
    }
  }

  return nCount;
}

//��ӡ��ɫ����
int print_with_color(const char* chString, int nColor)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbiConsoleInfo;
  WORD wSavedAttributes;

  /* Save current attributes */
  GetConsoleScreenBufferInfo(hConsole, &csbiConsoleInfo);
  wSavedAttributes = csbiConsoleInfo.wAttributes;

  //��ӡ
  SetConsoleTextAttribute(hConsole, nColor);
  printf(chString);

  /* Restore original attributes */
  SetConsoleTextAttribute(hConsole, wSavedAttributes);

  return 0;
}