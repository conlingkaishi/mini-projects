// MazeGeneration.cpp : Defines the entry point for the console application.
//

//��������Թ�

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>

//�趨·�����Ӷ�(�ո��ܶ�) ��������Ϊ0.0��0.6֮��
#define PATH_DENSITY 0.45

//�趨�Թ���С����һ�������������Σ�
#define MAZE_WIDTH 32
#define MAZE_HEIGHT 32

//�趨��ڵ����꣬Ĭ��Ϊ���Ͻ�(1, 1)
#define MAZE_ENTRANCE_COOR_X 1
#define MAZE_ENTRANCE_COOR_Y 1
//�趨���ڵ����꣬Ĭ��Ϊ���½�
#define MAZE_EXIT_COOR_X MAZE_WIDTH - 2
#define MAZE_EXIT_COOR_Y MAZE_HEIGHT - 2 

//���α�ʾ��
#define MAZE_PATH 0
#define MAZE_WALL 1
#define MAZE_ENTRANCE 2
#define MAZE_EXIT 3

//�趨·���������̶�(���ڴ�ֵ������˴�·������)
#define PATH_GENERATION_TOLERANCE 5

//�趨���ѭ���������˳���ѭ����
#define MAX_LOOP_TIME 600

int generate_maze(char chMaze[][MAZE_WIDTH]);

//��ͨ��·
int generate_path(char chMaze[][MAZE_WIDTH], int nStartCoorX, int nStartCoorY,
  int nEndCoorX, int nEndCoorY);

//���һ������Ŀյص����꣨�����������·������Ϊ���·������㣩
int get_a_random_path_coordinate(char chMaze[][MAZE_WIDTH], int *pnCoorX,
  int *pnCoorY);

//��ӡ�Թ�
int print_maze(char chMaze[][MAZE_WIDTH]);

float get_path_density(char chMaze[][MAZE_WIDTH]);

int main()
{
  char chMaze[MAZE_HEIGHT][MAZE_WIDTH] = { 0 };
 
  srand((unsigned int)time(0));

  while (true)
  {
    generate_maze(chMaze);
    print_maze(chMaze);
    system("pause");
  }

  return 0;
}

int generate_maze(char chMaze[][MAZE_WIDTH])
{
  int i = 0;
  int j = 0;

  int nTempStartCoorX = 0;
  int nTempStartCoorY = 0;
  int nTempEndCoorX = 0;
  int nTempEndCoorY = 0;

  //��ȫ����ʼ��Ϊǽ
  for (i = 0; i < MAZE_HEIGHT; i++)
  {
    for (j = 0; j < MAZE_WIDTH; j++)
    {
      chMaze[i][j] = MAZE_WALL;
    }
  }

  //������㵽�յ��ͨ·
  generate_path(chMaze, MAZE_ENTRANCE_COOR_X, MAZE_ENTRANCE_COOR_Y,
    MAZE_EXIT_COOR_X, MAZE_EXIT_COOR_Y);

  //debug //print_maze(chMaze);

  //�������·��
  while (get_path_density(chMaze) < PATH_DENSITY)
  {
    get_a_random_path_coordinate(chMaze, &nTempStartCoorX, &nTempStartCoorY);

    nTempEndCoorX = (rand() % (MAZE_WIDTH - 2)) + 1;
    nTempEndCoorY = (rand() % (MAZE_HEIGHT - 2)) + 1;

    generate_path(chMaze, nTempStartCoorX, nTempStartCoorY, nTempEndCoorX,
      nTempEndCoorY);

    //debug //print_maze(chMaze);
  }

  //��ǳ���ڵ�
  chMaze[MAZE_ENTRANCE_COOR_Y][MAZE_ENTRANCE_COOR_X] = MAZE_ENTRANCE;
  chMaze[MAZE_EXIT_COOR_Y][MAZE_EXIT_COOR_X] = MAZE_EXIT;

  return 0;
}

//��ͨ��·
int generate_path(char chMaze[][MAZE_WIDTH], int nStartCoorX, int nStartCoorY,
  int nEndCoorX, int nEndCoorY)
{
  /*nTolerance���ڼ�ⲻ�ò����ɿ��Ϊ2��·���������Ҫ����������������࣬��˵��·
  ���޽⣬���غ�����*/
  int nTolerance = 0;

  /*nWhileLoopCount����Ӧ�Է�����ѭ����������˼���������һ��ֵ��ǿ������ѭ����*/
  int nWhileLoopCount = 0;

  int nDirection = -1;
  int nCurrentCoorX = nStartCoorX;
  int nCurrentCoorY = nStartCoorY;

  while (true)
  {
    if (nWhileLoopCount++ >= MAX_LOOP_TIME)
    {
      return -1;
    }

    if (nTolerance > PATH_GENERATION_TOLERANCE)
    {
      return -1;
    }

    if (nCurrentCoorX == nEndCoorX && nCurrentCoorY == nEndCoorY)
    {
      return 0;
    }

    nDirection = rand() % 4;

    switch (nDirection)
    {
    case 0:   //����
      //�������������Ҫ���£������
      if (nStartCoorY < nEndCoorY)
      {
        continue;
      }

      //��������Թ��߽磬�����
      if (nCurrentCoorY <= 1)
      {
        continue;
      }

      //�������γɿ��Ϊ2��·��������nTolerance������
      if (nCurrentCoorX >= 1 && 
        chMaze[nCurrentCoorY][nCurrentCoorX - 1] == MAZE_PATH &&
        chMaze[nCurrentCoorY - 1][nCurrentCoorX -1] == MAZE_PATH)
      {
        nTolerance++;
        continue;
      }
      
      //����Ҳ��γɿ��Ϊ2��·��������nTolerance������
      if (nCurrentCoorX <= MAZE_WIDTH - 2 &&
        chMaze[nCurrentCoorY][nCurrentCoorX + 1] == MAZE_PATH &&
        chMaze[nCurrentCoorY - 1][nCurrentCoorX + 1] == MAZE_PATH)
      {
        nTolerance++;
        continue;
      }

      //�Ϸ����
      chMaze[nCurrentCoorY - 1][nCurrentCoorX] = MAZE_PATH;
      nCurrentCoorY--;
      nTolerance = 0;

      break;
    case 1:   //����
      //�������������Ҫ���ϣ������
      if (nStartCoorY > nEndCoorY)
      {
        continue;
      }

      //��������Թ��߽磬�����
      if (nCurrentCoorY >= MAZE_HEIGHT - 2)
      {
        continue;
      }

      //�������γɿ��Ϊ2��·��������nTolerance������
      if (nCurrentCoorX >= 1 &&
        chMaze[nCurrentCoorY][nCurrentCoorX - 1] == MAZE_PATH &&
        chMaze[nCurrentCoorY + 1][nCurrentCoorX - 1] == MAZE_PATH)
      {
        nTolerance++;
        continue;
      }

      //����Ҳ��γɿ��Ϊ2��·��������nTolerance������
      if (nCurrentCoorX <= MAZE_WIDTH - 2 &&
        chMaze[nCurrentCoorY][nCurrentCoorX + 1] == MAZE_PATH &&
        chMaze[nCurrentCoorY + 1][nCurrentCoorX + 1] == MAZE_PATH)
      {
        nTolerance++;
        continue;
      }

      //�Ϸ����
      chMaze[nCurrentCoorY + 1][nCurrentCoorX] = MAZE_PATH;
      nCurrentCoorY++;
      nTolerance = 0;

      break;
    case 2:   //����
      //�������������Ҫ���ң������
      if (nStartCoorX < nEndCoorX)
      {
        continue;
      }

      //��������Թ��߽磬�����
      if (nCurrentCoorX <= 1)
      {
        continue;
      }

      //����Ϸ��γɿ��Ϊ2��·��������nTolerance������
      if (nCurrentCoorY >= 1 &&
        chMaze[nCurrentCoorY - 1][nCurrentCoorX] == MAZE_PATH &&
        chMaze[nCurrentCoorY - 1][nCurrentCoorX - 1] == MAZE_PATH)
      {
        nTolerance++;
        continue;
      }

      //����·��γɿ��Ϊ2��·��������nTolerance������
      if (nCurrentCoorY <= MAZE_HEIGHT - 2 &&
        chMaze[nCurrentCoorY + 1][nCurrentCoorX] == MAZE_PATH &&
        chMaze[nCurrentCoorY + 1][nCurrentCoorX - 1] == MAZE_PATH)
      {
        nTolerance++;
        continue;
      }

      //�Ϸ����
      chMaze[nCurrentCoorY][nCurrentCoorX - 1] = MAZE_PATH;
      nCurrentCoorX--;
      nTolerance = 0;
      
      break;
    case 3:   //����
      //�������������Ҫ���������
      if (nStartCoorX > nEndCoorX)
      {
        continue;
      }

      //��������Թ��߽磬�����
      if (nCurrentCoorX >= MAZE_WIDTH - 2)
      {
        continue;
      }

      //����Ϸ��γɿ��Ϊ2��·��������nTolerance������
      if (nCurrentCoorY >= 1 &&
        chMaze[nCurrentCoorY - 1][nCurrentCoorX] == MAZE_PATH &&
        chMaze[nCurrentCoorY - 1][nCurrentCoorX + 1] == MAZE_PATH)
      {
        nTolerance++;
        continue;
      }

      //����·��γɿ��Ϊ2��·��������nTolerance������
      if (nCurrentCoorY <= MAZE_HEIGHT - 2 &&
        chMaze[nCurrentCoorY + 1][nCurrentCoorX] == MAZE_PATH &&
        chMaze[nCurrentCoorY + 1][nCurrentCoorX + 1] == MAZE_PATH)
      {
        nTolerance++;
        continue;
      }

      //�Ϸ����
      chMaze[nCurrentCoorY][nCurrentCoorX + 1] = MAZE_PATH;
      nCurrentCoorX++;
      nTolerance = 0;

      break;
    default:
      break;
    }
  }

  return -1;
}

//���һ������Ŀյص����꣨�����������·������Ϊ���·������㣩
int get_a_random_path_coordinate(char chMaze[][MAZE_WIDTH], int *pnCoorX, 
  int *pnCoorY)
{
  int nRandomizedCoorX = 0;
  int nRandomizedCoorY = 0;

  while (true)
  {
    nRandomizedCoorX = (rand() % (MAZE_WIDTH - 2)) + 1;
    nRandomizedCoorY = (rand() & (MAZE_HEIGHT - 2)) + 1;

    if (chMaze[nRandomizedCoorY][nRandomizedCoorX] == MAZE_PATH)
    {
      *pnCoorX = nRandomizedCoorX;
      *pnCoorY = nRandomizedCoorY;
      return 0;
    }
  }

  return -1;
}

//��ӡ�Թ�
int print_maze(char chMaze[][MAZE_WIDTH])
{
  int i = 0;
  int j = 0;

  system("cls");

  for (i = 0; i < MAZE_HEIGHT; i++)
  {
    for (j = 0; j < MAZE_WIDTH; j++)
    {
      switch (chMaze[i][j])
      {
      case MAZE_PATH:
        printf("  ");
        break;
      case MAZE_WALL:
        printf("��");
        break;
      case MAZE_ENTRANCE:
        printf("��");
        break;
      case MAZE_EXIT:
        printf("��");
        break;
      default:
        break;
      }
    }

    printf("\r\n");
  }

  printf("\r\n\r\n");

  return 0;
}

float get_path_density(char chMaze[][MAZE_WIDTH])
{
  int nPathCount = 0;
  int i = 0;
  int j = 0;
  float fPathDensity = 0.0f;

  for (i = 0; i < MAZE_HEIGHT; i++)
  {
    for (j = 0; j < MAZE_WIDTH; j++)
    {
      if (chMaze[i][j] == MAZE_PATH)
      {
        nPathCount++;
      }
    }
  }

  fPathDensity = (float)(((float)nPathCount) / (MAZE_WIDTH * MAZE_HEIGHT));

  return fPathDensity;
}