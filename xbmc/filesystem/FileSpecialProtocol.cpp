

#include "FileSpecialProtocol.h"
#include "SpecialProtocol.h"
#include "URL.h"

#include <sys/stat.h>

using namespace XFILE;

CFileSpecialProtocol::CFileSpecialProtocol(void)
{
}

CFileSpecialProtocol::~CFileSpecialProtocol(void)
{
  Close();
}

bool CFileSpecialProtocol::Open(const CURL& url)
{
  CStdString strFileName=CSpecialProtocol::TranslatePath(url);

  return m_file.Open(strFileName);
}

bool CFileSpecialProtocol::OpenForWrite(const CURL& url, bool bOverWrite /*=false */)
{
  CStdString strFileName=CSpecialProtocol::TranslatePath(url);

  return m_file.OpenForWrite(strFileName,bOverWrite);
}

bool CFileSpecialProtocol::Delete(const CURL& url)
{
  CStdString strFileName=CSpecialProtocol::TranslatePath(url);
  
  return m_file.Delete(strFileName);
}

bool CFileSpecialProtocol::Exists(const CURL& url)
{
  CStdString strFileName=CSpecialProtocol::TranslatePath(url);

  return m_file.Exists(strFileName);
}

int CFileSpecialProtocol::Stat(const CURL& url, struct __stat64* buffer)
{
  CStdString strFileName=CSpecialProtocol::TranslatePath(url);

  return m_file.Stat(strFileName, buffer);
}

bool CFileSpecialProtocol::Rename(const CURL& url, const CURL& urlnew)
{
  CStdString strFileName=CSpecialProtocol::TranslatePath(url);
  CStdString strFileName2=CSpecialProtocol::TranslatePath(urlnew);

  return m_file.Rename(strFileName,strFileName2);
}

int CFileSpecialProtocol::Stat(struct __stat64* buffer)
{
  return m_file.Stat(buffer);
}

unsigned int CFileSpecialProtocol::Read(void* lpBuf, int64_t uiBufSize)
{
  return m_file.Read(lpBuf, uiBufSize);
}
  
int CFileSpecialProtocol::Write(const void* lpBuf, int64_t uiBufSize)
{
  return m_file.Write(lpBuf,uiBufSize);
}

int64_t CFileSpecialProtocol::Seek(int64_t iFilePosition, int iWhence /*=SEEK_SET*/)
{
  return m_file.Seek(iFilePosition, iWhence);
}

void CFileSpecialProtocol::Close()
{
  m_file.Close();
}

int64_t CFileSpecialProtocol::GetPosition()
{
  return m_file.GetPosition();
}

int64_t CFileSpecialProtocol::GetLength()
{
  return m_file.GetLength();
}



