

#include "SFTPDirectory.h"
#ifdef HAS_FILESYSTEM_SFTP
#include "URL.h"

using namespace XFILE;

CSFTPDirectory::CSFTPDirectory(void)
{
}

CSFTPDirectory::~CSFTPDirectory(void)
{
}

bool CSFTPDirectory::GetDirectory(const CStdString& strPath, CFileItemList &items)
{
  CURL url(strPath);

  CSFTPSessionPtr session = CSFTPSessionManager::CreateSession(url);
  return session->GetDirectory(url.GetWithoutFilename().c_str(), url.GetFileName().c_str(), items);
}
#endif
