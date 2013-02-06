
#include "FileFileReader.h"
#include "URL.h"

using namespace XFILE;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************************
CFileFileReader::CFileFileReader()
{
}

//*********************************************************************************************
CFileFileReader::~CFileFileReader()
{
  Close();
}

//*********************************************************************************************
bool CFileFileReader::Open(const CURL& url)
{
  CStdString strURL = url.Get();
  strURL = strURL.Mid(13);
  return m_reader.Open(strURL,READ_CACHED);
}

bool CFileFileReader::Exists(const CURL& url)
{
  return CFile::Exists(url.Get().Mid(13));
}

int CFileFileReader::Stat(const CURL& url, struct __stat64* buffer)
{
  return CFile::Stat(url.Get().Mid(13),buffer);
}


//*********************************************************************************************
bool CFileFileReader::OpenForWrite(const CURL& url, bool bOverWrite)
{
  return false;
}

//*********************************************************************************************
unsigned int CFileFileReader::Read(void *lpBuf, int64_t uiBufSize)
{
  return m_reader.Read(lpBuf,uiBufSize);
}

//*********************************************************************************************
int CFileFileReader::Write(const void *lpBuf, int64_t uiBufSize)
{
  return 0;
}

//*********************************************************************************************
void CFileFileReader::Close()
{
  m_reader.Close();
}

//*********************************************************************************************
int64_t CFileFileReader::Seek(int64_t iFilePosition, int iWhence)
{
  return m_reader.Seek(iFilePosition,iWhence);
}

//*********************************************************************************************
int64_t CFileFileReader::GetLength()
{
  return m_reader.GetLength();
}

//*********************************************************************************************
int64_t CFileFileReader::GetPosition()
{
  return m_reader.GetPosition();
}


