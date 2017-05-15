#include "stdafx.h"
#include "GYFileOperator.h"

#include <string.h>

/*
CGYFileOperator::CGYFileOperator()
{
}*/

CGYFileOperator::CGYFileOperator(const char * pszFileName)
  :m_StrFileName(pszFileName)
{
  create_file_in_disk();
}

CGYFileOperator::~CGYFileOperator()
{
}

//����ļ������ڣ���һ������ʱ���������ļ�
int CGYFileOperator::create_file_in_disk()
{
  FILE *pTmp = fopen(*m_StrFileName, "a");
  fclose(pTmp);

  return 0;
}

//�����ļ��Ĵ�С���ֽ�����
charnumber_t CGYFileOperator::get_file_size_byte()
{
  charnumber_t cntFileSizeByte = 0;
  struct stat st;

  stat(*m_StrFileName, &st);

  cntFileSizeByte = st.st_size;

  return cntFileSizeByte;
}

//�ļ�ӳ�䵽�ڴ�
int CGYFileOperator::map_file_to_memory(char ** pszMemDest, 
  charnumber_t nStartPoint, charnumber_t nCharNum, bool isEndWith0)
{
  charnumber_t nCharNumToRead = 0;
  FILE *pFile = fopen(*m_StrFileName, "rb+");

  nCharNumToRead = 
    nCharNum == -1 ? get_file_size_byte() - nStartPoint : nCharNum;

  if (isEndWith0 == true)
  {
    nCharNumToRead++;
  }

  *pszMemDest = new char[nCharNumToRead];

  fseek(pFile, nStartPoint, SEEK_SET);

  fread(*pszMemDest, sizeof(char), nCharNumToRead, pFile);

  if (isEndWith0 == true)
  {
    (*pszMemDest)[nCharNumToRead - 1] = '\0';
  }

  fclose(pFile);

  return 0;
}

//��ȡ�ļ����ݣ����붯̬����
int CGYFileOperator::split_file_content_into_dynamic_array(
  CGYDynamicArray<CGYString> &storageArray, char chDelimiter, bool isEndWith0)
{
  FILE *pFile = fopen(*m_StrFileName, "r+");

  /*char szFormater[MAX_STRING_SIZE] = { '\0' };

  sprintf(szFormater, "%%s%c", chDelimiter);

  char szBuff[MAX_STRING_SIZE] = { '\0' };

  CGYString strTmp("");

  while (!feof(pFile))
  {
    fscanf(pFile, szFormater, szBuff);

    strTmp = szBuff;
    strTmp += "\0";
    storageArray.insert_element(strTmp);
  }*/

  char *pMemTmp = NULL;

  char szBuff[MAX_STRING_SIZE] = { '\0' };
  int nBuffPosCounter = 0;
  CGYString strTmp("");
  map_file_to_memory(&pMemTmp);

  while (*pMemTmp != '\0')
  {
    szBuff[nBuffPosCounter] = *pMemTmp;

    if (*pMemTmp == chDelimiter)
    {
      szBuff[nBuffPosCounter] = '\0';
      nBuffPosCounter = 0;
      strTmp = szBuff;
      storageArray.insert_element(strTmp);
    }
    else
    {
      nBuffPosCounter++;
    }

    pMemTmp++;
  }

  fclose(pFile);

  return 0;
}
