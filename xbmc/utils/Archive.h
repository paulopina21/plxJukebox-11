#pragma once



#include "StdString.h"
#include "system.h" // for SYSTEMTIME

namespace XFILE
{
  class CFile;
}
class CVariant;

class CArchive;

class IArchivable
{
public:
  virtual void Archive(CArchive& ar) = 0;
  virtual ~IArchivable() {}
};

class CArchive
{
public:
  CArchive(XFILE::CFile* pFile, int mode);
  ~CArchive();
  // storing
  CArchive& operator<<(float f);
  CArchive& operator<<(double d);
  CArchive& operator<<(int i);
  CArchive& operator<<(unsigned int i);
  CArchive& operator<<(int64_t i64);
  CArchive& operator<<(uint64_t ui64);
  CArchive& operator<<(bool b);
  CArchive& operator<<(char c);
  CArchive& operator<<(const CStdString& str);
  CArchive& operator<<(const CStdStringW& str);
  CArchive& operator<<(const SYSTEMTIME& time);
  CArchive& operator<<(IArchivable& obj);
  CArchive& operator<<(const CVariant& variant);

  // loading
  CArchive& operator>>(float& f);
  CArchive& operator>>(double& d);
  CArchive& operator>>(int& i);
  CArchive& operator>>(unsigned int& i);
  CArchive& operator>>(int64_t& i64);
  CArchive& operator>>(uint64_t& ui64);
  CArchive& operator>>(bool& b);
  CArchive& operator>>(char& c);
  CArchive& operator>>(CStdString& str);
  CArchive& operator>>(CStdStringW& str);
  CArchive& operator>>(SYSTEMTIME& time);
  CArchive& operator>>(IArchivable& obj);
  CArchive& operator>>(CVariant& variant);

  bool IsLoading();
  bool IsStoring();

  void Close();

  enum Mode {load = 0, store};

protected:
  void FlushBuffer();
  XFILE::CFile* m_pFile;
  int m_iMode;
  uint8_t *m_pBuffer;
  int m_BufferPos;
};

