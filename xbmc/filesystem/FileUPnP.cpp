

#include "FileUPnP.h"
#include "UPnPDirectory.h"
#include "FileFactory.h"
#include "FileItem.h"
#include "utils/log.h"

using namespace XFILE;

CFileUPnP::CFileUPnP()
{
}

CFileUPnP::~CFileUPnP()
{
}

bool CFileUPnP::Open(const CURL& url)
{
  CFileItem item_new;
  if (CUPnPDirectory::GetResource(url.Get(), item_new))
  {
    //CLog::Log(LOGDEBUG,"FileUPnP - file redirect to %s.", item_new.GetPath().c_str());
    IFile *pNewImp = CFileFactory::CreateLoader(item_new.GetPath());    
    CURL *pNewUrl = new CURL(item_new.GetPath());    
    if (pNewImp)
    {
      throw new CRedirectException(pNewImp, pNewUrl);
    }
    SAFE_DELETE(pNewUrl);    
  }
  return false;
}

int CFileUPnP::Stat(const CURL& url, struct __stat64* buffer)
{
  CFileItem item_new;
  if (CUPnPDirectory::GetResource(url.Get(), item_new))
  {
    //CLog::Log(LOGDEBUG,"FileUPnP - file redirect to %s.", item_new.GetPath().c_str());
    IFile *pNewImp = CFileFactory::CreateLoader(item_new.GetPath());
    CURL *pNewUrl = new CURL(item_new.GetPath());
    if (pNewImp)
    {
      throw new CRedirectException(pNewImp, pNewUrl);
    }
    SAFE_DELETE(pNewUrl);
  }
  return -1;
}

bool CFileUPnP::Exists(const CURL& url)
{
  CFileItem item_new;
  if (CUPnPDirectory::GetResource(url.Get(), item_new))
  {
    //CLog::Log(LOGDEBUG,"FileUPnP - file redirect to %s.", item_new.GetPath().c_str());
    IFile *pNewImp = CFileFactory::CreateLoader(item_new.GetPath());
    CURL *pNewUrl = new CURL(item_new.GetPath());
    if (pNewImp)
    {
      throw new CRedirectException(pNewImp, pNewUrl);
    }
    SAFE_DELETE(pNewUrl);
  }
  return false;
}
