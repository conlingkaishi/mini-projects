#pragma once

#include "GYString.h"
//#include <stdio.h>
#include "GYDynamicArray.h"

typedef int charnumber_t;

//�ļ������࣬��ʱûд��飨new��fopen�Ŀ�ָ���飩
class CGYFileOperator
{
public:
#define MAX_STRING_SIZE 2048
public:
  //CGYFileOperator();
  CGYFileOperator(const char * pszFileName);
  virtual ~CGYFileOperator();

public:
  //�����ļ��Ĵ�С���ֽ�����
  charnumber_t get_file_size_byte();
  //�ļ�ӳ�䵽�ڴ�
  int map_file_to_memory(char ** pszMemDest, charnumber_t nStartPoint = 0,
    charnumber_t nCharNum = -1, bool isEndWith0 = true);
private:
  CGYString m_StrFileName;

  //����ļ������ڣ���һ������ʱ���������ļ�
  int create_file_in_disk();
public:

  //��ȡ�ļ����ݣ����붯̬����
  int split_file_content_into_dynamic_array(
    CGYDynamicArray<CGYString> &storageArray, char chDelimiter = ' ', 
    bool isEndWith0 = true);
};

