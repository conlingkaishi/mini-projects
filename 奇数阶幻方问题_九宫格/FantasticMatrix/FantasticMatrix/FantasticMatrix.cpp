// FantasticMatrix.cpp : Defines the entry point for the console application.
//�����׻÷����⣨�Ź��񣩣�Ҫ��ÿһ�С�ÿһ�С������Խ��ߵĺ���ͬ��

#include "stdafx.h"

#include <windows.h>
#include <stdlib.h>

#define MATRIX_WIDTH 33    //Ĭ�Ͼ�����
#define COLOR_DEFUALT 0x1E    //���׻�ɫ
#define COLOR_NUNMBER 2   //��ɫ������
#define MATRIX_DEFUALT_VALUE 0    //�������ǰĬ�ϵ���ֵ
#define SLEEP_DURATION 5    //ÿ��ʱ����
#define MAX_STR_LEN 30    //����ַ������ȣ����ڴ�ӡ

//��ӡԪ��
int print_number(int nCoordX, int nCoordY, const int nNum, int nColor,
  int nNumWith);

//Ѱ����һ����������(����б�з���1��·���ı䷵��0)
int look_for_next_slot(int *pnMatrix, int nMatrixWidth, int *pnCurrentCoorX,
  int *pnCurrentCoorY);

//��ȡ���ֿ�ȣ����ڴ�ӡ
int get_number_width(int nMatrixSize);

int main()
{
  int nMatrixWidth = MATRIX_WIDTH;
  int nPrintColor = COLOR_DEFUALT;
  int nColorTop = COLOR_DEFUALT + (COLOR_NUNMBER - 1) * 0x10;
  int nNumberWidth = 0;

  int nMatrixSize = 0;
  int *pnMatrix = NULL;
  int i = 0;

  int nCoorX = 0;
  int nCoorY = 0;
  int nCurrentNum = 0;

  //����������
  nMatrixSize = nMatrixWidth * nMatrixWidth;

  //�����ӡ���
  nNumberWidth = get_number_width(nMatrixSize);

  //�����긳��ֵ
  nCoorX = nMatrixWidth / 2;
  nCoorY = nMatrixWidth - 1;

  //����ǰ���ָ���ֵ
  nCurrentNum = 1;

  //����ѿռ�
  pnMatrix = (int *)malloc(sizeof(int) * nMatrixSize);

  if (!pnMatrix)
  {
    _tprintf(_T("����ѿռ�ʧ�ܡ�\r\n"));
    exit(1);
  }

  //��ʼ����
  for (i = 0; i < nMatrixSize; i++)
  {
    *(pnMatrix + i) = MATRIX_DEFUALT_VALUE;
  }

  //��ʼ���
  while (true)
  {
    Sleep(SLEEP_DURATION);

    //��ֵ
    *(pnMatrix + nCoorY * nMatrixWidth + nCoorX) = nCurrentNum;

    //��ӡ
    print_number(nCoorX * nNumberWidth, nCoorY, nCurrentNum, nPrintColor,
      nNumberWidth);

    nCurrentNum++;

    if (nCurrentNum > nMatrixSize)
    {
      break;
    }

    //Ѱ����һ������
    switch (look_for_next_slot(pnMatrix, nMatrixWidth, &nCoorX, &nCoorY))
    {
    case 0:
      //��б�����裬����·���ı䣬���ӡ�ı�����ɫ�仯һ��
      nPrintColor = nPrintColor + 0x10;
      if (nPrintColor > nColorTop)
      {
        nPrintColor = COLOR_DEFUALT;
      }
      break;
    case 1:
      //���������ʲô�������������Ѿ���look_for_next_solt�����б��ı䣩
      break;
    default:
      //����-1������������߼�����
      _tprintf(_T("debug:�߼�����"));
      break;
    }

  }

  //�ͷŶѿռ�
  free((void *)pnMatrix);

  //��ӡ�����س����У���ֹϵͳ��ͣ��Ϣ��ס�÷���Ϣ
  for (i = 0; i < nMatrixWidth; i++)
  {
    _tprintf(_T("\r\n"));
  }

  system("pause");

  return 0;
}

//��ӡԪ��
int print_number(int nCoordX, int nCoordY, const int nNum, int nColor, 
  int nNumWith)
{
  COORD cPos;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbiConsoleInfo;
  WORD wSavedAttributes;
  TCHAR szFormat[MAX_STR_LEN] = { 0 };    //��ʵ���Կ�����Ϊ�����������Լ���������
  int i = 0;

  cPos.X = nCoordX;
  cPos.Y = nCoordY;
  SetConsoleCursorPosition(hConsole, cPos);

  /* Save current attributes */
  GetConsoleScreenBufferInfo(hConsole, &csbiConsoleInfo);
  wSavedAttributes = csbiConsoleInfo.wAttributes;

  SetConsoleTextAttribute(hConsole, nColor);

  _stprintf(szFormat, _T("%%%dd"), nNumWith);

  _tprintf(szFormat, nNum);

  /* Restore original attributes */
  SetConsoleTextAttribute(hConsole, wSavedAttributes);

  return 0;
}

//Ѱ����һ����������(����б�з���1��·���ı䷵��0)
int look_for_next_slot(int *pnMatrix, int nMatrixWidth, int *pnCurrentCoorX, 
  int *pnCurrentCoorY)
{
  int CoordXStorage = *pnCurrentCoorX;
  int CoordYStorage = *pnCurrentCoorY;

  //���ܷ����������·�б��
  if (CoordXStorage - 1 >= 0 && CoordYStorage + 1 < nMatrixWidth &&
    *(pnMatrix + (CoordYStorage + 1) * nMatrixWidth + CoordXStorage - 1) == 
    MATRIX_DEFUALT_VALUE)
  {
    *pnCurrentCoorX = CoordXStorage - 1;
    *pnCurrentCoorY = CoordYStorage + 1;

    return 1;
  }

  //���������ߵ�������⼸�������˳����Ҫ�����ܸı�

  //���������ߵ����1�����·��ѱ�ռ�ã�������һ��
  if (CoordXStorage - 1 >= 0 && CoordYStorage + 1 < nMatrixWidth &&
    *(pnMatrix + (CoordYStorage + 1) * nMatrixWidth + CoordXStorage - 1) !=
    MATRIX_DEFUALT_VALUE)
  {
    *pnCurrentCoorX = CoordXStorage;
    *pnCurrentCoorY = CoordYStorage - 1;

    return 0;
  }

  //���������ߵ����2�����·���X�����Y����ͬʱԽ�磨�����½ǵĸ��ԣ���������һ��
  if (CoordYStorage + 1 >= nMatrixWidth && CoordXStorage - 1 < 0)
  {
    *pnCurrentCoorX = CoordXStorage;
    *pnCurrentCoorY = CoordYStorage - 1;

    return 0;
  }

  //���������ߵ����3��Y����Խ��,������һ�񣬲�����Y�����0
  if (CoordYStorage + 1 >= nMatrixWidth)
  {
    *pnCurrentCoorX = CoordXStorage - 1;
    *pnCurrentCoorY = 0;

    return 0;
  }

  //���������ߵ����4��X����Խ��,������һ�񣬲�����X�����Ϊ���
  if (CoordXStorage - 1 < 0)
  {
    *pnCurrentCoorX = nMatrixWidth - 1;
    *pnCurrentCoorY = CoordYStorage + 1;

    return 0;
  }

  return -1;
}

//��ȡ���ֿ�ȣ����ڴ�ӡ
int get_number_width(int nMatrixSize)
{
  int nCount = 1;

  while (nMatrixSize >= 10)
  {
    nMatrixSize = nMatrixSize / 10;
    nCount++;
  }

  return nCount;
}