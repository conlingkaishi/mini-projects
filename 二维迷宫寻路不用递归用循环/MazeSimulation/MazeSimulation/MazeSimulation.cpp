// MazeSimulation.cpp : Defines the entry point for the console application.
//

/*
*��ѭ��������ݹ飬������Թ����⡣
*��������ģ�⡰�ơ��ĸ�������õ�������ȣ�����ͨ�˴���Թ�ͨ������Ϊһ����·����ͨ����
*��ÿ���ո�����Ϊһ����衣С��ÿ���߹�һ���ո�ʱ�����ÿո��ϵ����������裩���һ�㡣
*����С�ˣ����ƣ�ÿ������ѡ��ʱ���ͻ�ѡ�����ͨ�����Ǹ��ո񣨵���Խ�͵���Խ�󣩣�Ҳ����
*������ѡ���߱Ƚ��µ�·�����������߾�·��
*/

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//�Թ��ַ�(Ϊ���Թ�������Ӿ�Ч����ֱ�ۣ�����ĸ��������)��
//Xͨ·��M��Чͨ·��Y�յ�, P���
#define X -5
#define M -5  /*����Ϊ-5��ԭ����Ϊ���Թ���ģ��С����ģԽ����Թ��������ʼ����ҪԽ
              С,����-10000������ֵ���õù�������ף���Ϸ�����У��յ�ͻȻ�����ǽ��
              ������ִ������Ӧ����ֹͣ��Ϸ���Ѵ���ֵ��СһЩ��
              ���鷳�Ļ�������ֱ�ӵ���-99999999����������֧�ֵ���С�� + 1����*/ 
#define WALL 1
#define Y -10  //�յ��ֵ�����-5С

//�Թ���ȡ��߶�
#define MAZE_WIDTH 18
#define MAZE_HEIGHT 18

//(С���ƶ�)����
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define OPTIMIZATION_1_FLAG

//���Թ�
int draw_maze(int nMaze[][MAZE_WIDTH], int nPlayerCoordX, int nPlayerCoordY);

//����������������С���������
int find_minimun_number_from_array(int nArray[], int nArrayCount);

/*���Թ��Ż������������ǽ���Ͱ����ֵ��ΪWALL+1����Ȼ���滹����ʾΪ��·����ʵ��������
�Ѿ��ܴ󣬲������ٴ��������ˡ�*/
int is_player_sorrounded_by_wall(int nArray[], int nArrayCount);

int main()
{
  //�Թ�(����)����
  //1ǽ�� 0(X/M)ͨ·/��Чͨ·; 2(Y)�յ�; 100(P)���
  int nMaze[MAZE_HEIGHT][MAZE_WIDTH] =
  {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, X, 1, 1, 1, 1, M, 1, M, M, X, X, X, X, 1, 1, 1, 1 },
    { 1, X, 1, M, 1, 1, M, 1, 1, 1, X, 1, 1, X, X, X, X, 1 },
    { 1, X, 1, M, 1, M, M, M, 1, 1, X, 1, 1, 1, 1, 1, X, 1 },
    { 1, X, 1, M, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, 1, X, 1 },
    { 1, X, 1, M, 1, M, 1, 1, X, 1, 1, 1, 1, 1, 1, 1, X, 1 },
    { 1, X, 1, M, M, M, M, M, X, 1, M, 1, M, M, M, X, X, 1 },
    { 1, X, 1, 1, 1, M, 1, 1, X, 1, M, 1, 1, 1, 1, X, 1, 1 },
    { 1, X, 1, 1, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, X, 1, 1 },
    { 1, X, X, 1, 1, 1, 1, 1, 1, 1, X, 1, 1, M, M, X, M, 1 },
    { 1, 1, X, X, X, 1, 1, 1, M, M, X, 1, 1, 1, 1, X, 1, 1 },
    { 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, 1, 1, X, 1, 1 },
    { 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, X, X, X, 1, 1 },
    { 1, 1, M, 1, X, X, X, X, X, X, X, 1, 1, X, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, M, 1, 1, 1, 1, 1, 1, 1, X, M, M, M, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, M, 1, 1, 1, 1, X, 1, 1, 1, 1 },
    { 1, 1, Y, X, X, X, X, X, X, X, X, X, X, X, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
  };

  //С��Ŀǰ����
  int nCurrentCoordX = 1;
  int nCurrentCoordY = 1;

  //����������Χ�ĸ�������ֵ�����飬��0��3�ǡ��������ҡ���˳��
  int nSurrounding[4] = { 0 };

  //��������յ㣬����ѭ����С��һֱ����ȥ��Y�����յ��ֵ
  while (nMaze[nCurrentCoordY][nCurrentCoordX] != Y) 
  {
    nSurrounding[0] = nMaze[nCurrentCoordY - 1][nCurrentCoordX];  //��ֵ
    nSurrounding[1] = nMaze[nCurrentCoordY][nCurrentCoordX - 1];  //��ֵ
    nSurrounding[2] = nMaze[nCurrentCoordY + 1][nCurrentCoordX];  //��ֵ
    nSurrounding[3] = nMaze[nCurrentCoordY][nCurrentCoordX + 1];  //��ֵ

    //ÿ�δӴ˴��뿪���������ֵ������1����ʼֵΪ-5��
    nMaze[nCurrentCoordY][nCurrentCoordX] += 1;

    //�Ż�(����ע�͵��Ż����֣���Ӱ�����ս��)
    if (is_player_sorrounded_by_wall(nSurrounding, _countof(nSurrounding)))
    {
      nMaze[nCurrentCoordY][nCurrentCoordX] = WALL + 1;
    }

    //�����ƣ�ѡ����һ�����ĸ������ߣ����Ҹ��ĵ�ǰ����
    switch (find_minimun_number_from_array(nSurrounding,
      _countof(nSurrounding)))
    {
    case UP:
      nCurrentCoordY--;
      break;
    case LEFT:
      nCurrentCoordX--;
      break;
    case DOWN:
      nCurrentCoordY++;
      break;
    case RIGHT:
      nCurrentCoordX++;
      break;
    default:
      break;
    }

    //���½��棨����С��λ�ã�
    draw_maze(nMaze, nCurrentCoordX, nCurrentCoordY);

    Sleep(50);
  }
  
  return 0;
}

/*���Թ��Ż������������ǽ���Ͱ����ֵ��ΪWALL+1����Ȼ���滹����ʾΪ��·����ʵ��������
�Ѿ��ܴ󣬲������ٴ��������ˡ�*/
int is_player_sorrounded_by_wall(int nArray[], int nArrayCount)
{
  int i = 0;
  int nCount = 0;

  for (i = 0; i < nArrayCount; i++)
  {
    if (nArray[i] >= WALL)
    {
      nCount++;
    }
  }

  if (nCount == 3)
  {
    return 1;
  }

  return 0;
}

//����������������С���������
int find_minimun_number_from_array(int nArray[], int nArrayCount)
{
  int i = 0;
  int nCurrentMin = 0;
  int nCurrentSerial = 0;

  //��ʼ����СֵΪ���е�0��
  nCurrentMin = nArray[0];

  for (i = 0; i < nArrayCount; i++)
  {
    if (nCurrentMin > nArray[i])
    {
      nCurrentMin = nArray[i];
      nCurrentSerial = i;
    }
  }

  return nCurrentSerial;
}

//���Թ�
int draw_maze(int nMaze[][MAZE_WIDTH], int nPlayerCoordX, int nPlayerCoordY)
{
  int i = 0;
  int j = 0;

  system("cls");

  /*for (i = 0; i < MAZE_HEIGHT; i++)
  {
    for (j = 0; j < MAZE_WIDTH; j++)
    {
      if (i == nPlayerCoordY && j == nPlayerCoordX)
      {
        printf("��");
        continue;
      }

      switch (nMaze[i][j])
      {
      case WALL:
        printf("��");
        break;
      case Y:
        printf("��");
        break;
      //case -5: //case X: //case M:
      //-5 �� -1 ���ǿյ�
      default:
        printf("  ");
        break;
        break;
      }
    }

    printf("\r\n");
  }*/

  for (i = 0; i < 324; i++)
  {
    if (i == nPlayerCoordX + nPlayerCoordY * 18)
    {
      printf("��");
      continue;
    }

    if (i % 18 == 0)
    {
      printf("\r\n");

    }

    switch ((int) *((int *)nMaze + i))
    {
    case WALL:
      printf("��");
      break;
    case Y:
      printf("��");
      break;
      //case -5: //case X: //case M:
      //-5 �� -1 ���ǿյ�
    default:
      printf("  ");
      break;
    }
  }

  return 0;
}

/*
�����Թ���ͼ���ã�������ԣ�����ֱ�Ӹ���main������Ӧ����

###################Ĭ������#############################��
//�Թ�(����)����
//1ǽ�� 0(X/M)ͨ·/��Чͨ·; 2(Y)�յ�; 100(P)���
int nMaze[MAZE_HEIGHT][MAZE_WIDTH] =
{
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, X, 1, 1, 1, 1, M, 1, M, M, X, X, X, X, 1, 1, 1, 1 },
{ 1, X, 1, M, 1, 1, M, 1, 1, 1, X, 1, 1, X, X, X, X, 1 },
{ 1, X, 1, M, 1, M, M, M, 1, 1, X, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, 1, M, 1, 1, X, 1, 1, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, M, M, M, M, X, 1, M, 1, M, M, M, X, X, 1 },
{ 1, X, 1, 1, 1, M, 1, 1, X, 1, M, 1, 1, 1, 1, X, 1, 1 },
{ 1, X, 1, 1, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, X, X, 1, 1, 1, 1, 1, 1, 1, X, 1, 1, M, M, X, M, 1 },
{ 1, 1, X, X, X, 1, 1, 1, M, M, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, X, X, X, 1, 1 },
{ 1, 1, M, 1, X, X, X, X, X, X, X, 1, 1, X, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, M, 1, 1, 1, 1, 1, 1, 1, X, M, M, M, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, M, 1, 1, 1, 1, X, 1, 1, 1, 1 },
{ 1, 1, Y, X, X, X, X, X, X, X, X, X, X, X, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

//С��Ŀǰ����
int nCurrentCoordX = 1;
int nCurrentCoordY = 1;

###################����1#############################��
//�Թ�(����)����
//1ǽ�� 0(X/M)ͨ·/��Чͨ·; 2(Y)�յ�; 100(P)���
int nMaze[MAZE_HEIGHT][MAZE_WIDTH] =
{
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, Y, 1, 1, 1, 1, M, 1, M, M, X, X, X, X, 1, 1, 1, 1 },
{ 1, X, 1, M, 1, 1, M, 1, 1, 1, X, 1, 1, X, X, X, X, 1 },
{ 1, X, 1, M, 1, M, M, M, 1, 1, X, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, 1, M, 1, 1, X, 1, 1, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, M, M, M, M, X, 1, M, 1, M, M, M, X, X, 1 },
{ 1, X, 1, 1, 1, M, 1, 1, X, 1, M, 1, 1, 1, 1, X, 1, 1 },
{ 1, X, 1, 1, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, X, X, 1, 1, 1, 1, 1, 1, 1, X, 1, 1, M, M, X, M, 1 },
{ 1, 1, X, X, X, 1, 1, 1, M, M, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, X, X, X, 1, 1 },
{ 1, 1, M, 1, X, X, X, X, X, X, X, 1, 1, X, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, M, 1, 1, 1, 1, 1, 1, 1, X, M, M, M, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, M, 1, 1, 1, 1, X, 1, 1, 1, 1 },
{ 1, 1, X, X, X, X, X, X, X, X, X, X, X, X, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

//С��Ŀǰ����
int nCurrentCoordX = 2;
int nCurrentCoordY = 16;

###################����2#############################��
//�Թ�(����)����
//1ǽ�� 0(X/M)ͨ·/��Чͨ·; 2(Y)�յ�; 100(P)���
int nMaze[MAZE_HEIGHT][MAZE_WIDTH] =
{
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, X, 1, 1, 1, 1, M, 1, M, M, X, X, X, X, 1, 1, 1, 1 },
{ 1, X, 1, M, 1, 1, M, 1, 1, 1, X, 1, 1, X, X, X, X, 1 },
{ 1, X, 1, M, 1, M, M, M, 1, 1, X, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, 1, M, 1, 1, X, 1, 1, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, M, M, M, M, X, M, M, 1, M, M, M, X, X, 1 },
{ 1, X, 1, 1, 1, M, 1, 1, X, 1, M, 1, 1, 1, 1, X, 1, 1 },
{ 1, X, 1, 1, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, X, X, 1, 1, M, 1, 1, M, 1, X, 1, 1, M, M, X, M, 1 },
{ 1, 1, X, X, X, M, M, M, M, M, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, X, X, X, 1, 1 },
{ 1, 1, M, 1, X, X, X, X, X, X, X, 1, 1, X, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, M, 1, 1, M, 1, 1, 1, 1, X, M, M, M, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, M, 1, 1, 1, 1, X, 1, 1, 1, 1 },
{ 1, 1, Y, X, X, X, X, X, X, X, X, X, X, X, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

//С��Ŀǰ����
int nCurrentCoordX = 1;
int nCurrentCoordY = 1;

###################����3#############################��
//�Թ�(����)����
//1ǽ�� 0(X/M)ͨ·/��Чͨ·; 2(Y)�յ�; 100(P)���
int nMaze[MAZE_HEIGHT][MAZE_WIDTH] =
{
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, X, 1, 1, 1, 1, M, 1, M, M, X, X, X, X, 1, 1, 1, 1 },
{ 1, X, 1, M, 1, 1, M, 1, 1, 1, X, 1, 1, X, X, X, X, 1 },
{ 1, X, 1, M, 1, M, M, M, 1, 1, X, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, 1, M, 1, 1, X, 1, 1, 1, 1, 1, 1, 1, X, 1 },
{ 1, X, 1, M, M, M, M, M, X, M, M, 1, M, M, M, X, X, 1 },
{ 1, X, 1, 1, 1, M, 1, 1, X, 1, M, 1, 1, 1, 1, X, 1, 1 },
{ 1, X, 1, 1, 1, M, 1, 1, X, X, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, X, X, 1, 1, M, 1, 1, M, 1, X, 1, 1, M, M, X, M, 1 },
{ 1, 1, X, X, X, M, M, M, M, M, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, 1, 1, X, 1, 1 },
{ 1, 1, M, 1, X, 1, 1, 1, M, 1, X, 1, 1, X, X, X, 1, 1 },
{ 1, 1, M, 1, X, X, X, X, X, X, X, 1, 1, X, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, M, 1, 1, M, 1, 1, 1, 1, X, M, M, Y, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, M, 1, 1, 1, 1, X, 1, 1, 1, 1 },
{ 1, 1, X, X, X, X, X, X, X, X, X, X, X, X, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

//С��Ŀǰ����
int nCurrentCoordX = 1;
int nCurrentCoordY = 1;
*/