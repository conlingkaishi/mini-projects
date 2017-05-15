#pragma once


/*ʵ��һ���򵥵�String�࣬���ڼ򵥵���Ŀ��û���ַ������Ȱ�ȫ��飬���������û������
������дʱ������*/
class CGYString
{
public:
  CGYString();
  explicit CGYString(const char * pszStr);
  CGYString(CGYString & obj);
  virtual ~CGYString();

public:
  const char * get_string_content();
  int get_string_length();
  const char * operator*();
  CGYString & operator=(const char * pszStr);
  CGYString & operator=(const CGYString & obj);
  CGYString & append(const char * pszStr);
  CGYString & append(const CGYString & obj);
  CGYString operator+(const char * pszStr);
  CGYString operator+(const CGYString & obj);
  CGYString & operator+=(const char * pszStr);
  CGYString & operator+=(CGYString & obj);
  char& operator[](int nIndex);
  bool operator==(const char * pszStr);
  bool operator==(const CGYString & obj);
  bool operator!=(const char * pszStr);
  bool operator!=(const CGYString & obj);

private:
  bool set_string(const char * pszStr);
  bool release_string();
  bool append_string(const char * pszStr);

private:
  //int m_nStringLength;    //�ַ�������
  char *m_pString;
};