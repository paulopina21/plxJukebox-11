

#include "FTPDirectory.h"
#include "FTPParse.h"
#include "URL.h"
#include "utils/URIUtils.h"
#include "FileCurl.h"
#include "FileItem.h"
#include "utils/StringUtils.h"
#include "utils/CharsetConverter.h"
#include "climits"

using namespace XFILE;

CFTPDirectory::CFTPDirectory(void){}
CFTPDirectory::~CFTPDirectory(void){}

bool CFTPDirectory::GetDirectory(const CStdString& strPath, CFileItemList &items)
{
  CFileCurl reader;

  CURL url(strPath);

  CStdString path = url.GetFileName();
  if( !path.IsEmpty() && !path.Right(1).Equals("/") )
  {
    path += "/";
    url.SetFileName(path);
  }

  if (!reader.Open(url))
    return false;


  char buffer[MAX_PATH + 1024];
  while( reader.ReadString(buffer, sizeof(buffer)) )
  {
    CStdString strBuffer = buffer;

    StringUtils::RemoveCRLF(strBuffer);

    CFTPParse parse;
    if (parse.FTPParse(strBuffer))
    {
      if( parse.getName().length() == 0 )
        continue;

      if( parse.getFlagtrycwd() == 0 && parse.getFlagtryretr() == 0 )
        continue;

      /* buffer name */
      CStdString name;
      name.assign(parse.getName());

      if( name.Equals("..") || name.Equals(".") )
        continue;

      /* this should be conditional if we ever add    */
      /* support for the utf8 extension in ftp client */
      g_charsetConverter.unknownToUTF8(name);

      CFileItemPtr pItem(new CFileItem(name));

      pItem->m_bIsFolder = (bool)(parse.getFlagtrycwd() != 0);
      CStdString filePath = path + name;
      if (pItem->m_bIsFolder)
        URIUtils::AddSlashAtEnd(filePath);

      /* qualify the url with host and all */
      url.SetFileName(filePath);
      pItem->SetPath(url.Get());

      pItem->m_dwSize = parse.getSize();
      pItem->m_dateTime=parse.getTime();

      items.Add(pItem);
    }
  }

  return true;
}

bool CFTPDirectory::Exists(const char* strPath)
{
  CFileCurl ftp;
  CURL url(strPath);
  return ftp.Exists(url);
}
