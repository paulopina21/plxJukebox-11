

#include "FileTuxBox.h"
#include <errno.h>

//Reserved for TuxBox Recording!

using namespace XFILE;

CFileTuxBox::CFileTuxBox()
{}

CFileTuxBox::~CFileTuxBox()
{
}

int64_t CFileTuxBox::GetPosition()
{
  return 0;
}

int64_t CFileTuxBox::GetLength()
{
  return 0;
}

bool CFileTuxBox::Open(const CURL& url)
{
  return true;
}

unsigned int CFileTuxBox::Read(void* lpBuf, int64_t uiBufSize)
{
  return 0;
}

int64_t CFileTuxBox::Seek(int64_t iFilePosition, int iWhence)
{
  return 0;
}

void CFileTuxBox::Close()
{
}

bool CFileTuxBox::Exists(const CURL& url)
{
  return true;
}

int CFileTuxBox::Stat(const CURL& url, struct __stat64* buffer)
{
  errno = ENOENT;
  return -1;
}

