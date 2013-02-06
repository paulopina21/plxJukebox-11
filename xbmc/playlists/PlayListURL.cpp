

#include "PlayListURL.h"
#include "filesystem/File.h"
#include "utils/URIUtils.h"
#include "utils/StringUtils.h"

using namespace PLAYLIST;
using namespace XFILE;

// example url file
//[DEFAULT]
//BASEURL=http://msdn2.microsoft.com/en-us/library/ms812698.aspx
//[InternetShortcut]
//URL=http://msdn2.microsoft.com/en-us/library/ms812698.aspx

CPlayListURL::CPlayListURL(void)
{}

CPlayListURL::~CPlayListURL(void)
{}

bool CPlayListURL::Load(const CStdString& strFileName)
{
  char szLine[4096];
  CStdString strLine;

  Clear();

  m_strPlayListName = URIUtils::GetFileName(strFileName);
  URIUtils::GetParentPath(strFileName, m_strBasePath);

  CFile file;
  if (!file.Open(strFileName) )
  {
    file.Close();
    return false;
  }

  while (file.ReadString(szLine, 1024))
  {
    strLine = szLine;
    StringUtils::RemoveCRLF(strLine);

    if (strLine.Left(18) == "[InternetShortcut]")
    {
      file.ReadString(szLine,1024);
      strLine  = szLine;
      StringUtils::RemoveCRLF(strLine);
      if (strLine.Left(4) == "URL=")
      {
        CFileItemPtr newItem(new CFileItem(strLine.Mid(4),false));
        Add(newItem);
      }
    }
  }

  file.Close();
  return true;
}

