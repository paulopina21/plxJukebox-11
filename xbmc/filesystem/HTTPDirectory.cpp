

#include "HTTPDirectory.h"
#include "URL.h"
#include "FileCurl.h"
#include "FileItem.h"
#include "utils/RegExp.h"
#include "settings/AdvancedSettings.h"
#include "utils/StringUtils.h"
#include "utils/CharsetConverter.h"
#include "utils/log.h"
#include "utils/URIUtils.h"
#include "utils/HTMLUtil.h"
#include "climits"

using namespace XFILE;

CHTTPDirectory::CHTTPDirectory(void){}
CHTTPDirectory::~CHTTPDirectory(void){}

bool CHTTPDirectory::GetDirectory(const CStdString& strPath, CFileItemList &items)
{
  CFileCurl http;
  CURL url(strPath);

  CStdString strName, strLink;
  CStdString strBasePath = url.GetFileName();

  if(!http.Open(url))
  {
    CLog::Log(LOGERROR, "%s - Unable to get http directory", __FUNCTION__);
    return false;
  }

  CRegExp reItem(true); // HTML is case-insensitive
  reItem.RegComp("<a href=\"(.*)\">(.*)</a>");

  /* read response from server into string buffer */
  char buffer[MAX_PATH + 1024];
  while(http.ReadString(buffer, sizeof(buffer)-1))
  {
    CStdString strBuffer = buffer;
    StringUtils::RemoveCRLF(strBuffer);

    if (reItem.RegFind(strBuffer.c_str()) >= 0)
    {
      strLink = reItem.GetReplaceString("\\1");
      strName = reItem.GetReplaceString("\\2");

      if(strLink[0] == '/')
        strLink = strLink.Mid(1);

      CStdString strNameTemp = strName.Trim();
      CStdString strLinkTemp = strLink;
      URIUtils::RemoveSlashAtEnd(strLinkTemp);
      URIUtils::RemoveSlashAtEnd(strNameTemp);
      CURL::Decode(strLinkTemp);

      if (strNameTemp == strLinkTemp && strLinkTemp != "..")
      {
        CStdStringW wName, wLink, wConverted;

        g_charsetConverter.unknownToUTF8(strName);
        g_charsetConverter.utf8ToW(strName, wName, false);
        HTML::CHTMLUtil::ConvertHTMLToW(wName, wConverted);
        g_charsetConverter.wToUTF8(wConverted, strName);
        URIUtils::RemoveSlashAtEnd(strName);

        g_charsetConverter.unknownToUTF8(strLink);
        g_charsetConverter.utf8ToW(strLink, wLink, false);
        HTML::CHTMLUtil::ConvertHTMLToW(wLink, wConverted);
        g_charsetConverter.wToUTF8(wConverted, strLink);

        CFileItemPtr pItem(new CFileItem(strName));
        pItem->SetProperty("IsHTTPDirectory", true);
        url.SetFileName(strBasePath + strLink);
        pItem->SetPath(url.Get());

        if(URIUtils::HasSlashAtEnd(pItem->GetPath()))
          pItem->m_bIsFolder = true;

        if (!pItem->m_bIsFolder && g_advancedSettings.m_bHTTPDirectoryStatFilesize)
        {
          CFileCurl file;
          file.Open(url);
          pItem->m_dwSize= file.GetLength();
          file.Close();
        }

        if (!pItem->m_bIsFolder && pItem->m_dwSize == 0)
        {
          CRegExp reSize(true);
          reSize.RegComp(">*([0-9.]+)(B|K|M|G| )</td>");
          if (reSize.RegFind(strBuffer.c_str()) >= 0)
          {
            double Size = atof(reSize.GetReplaceString("\\1"));
            CStdString strUnit = reSize.GetReplaceString("\\2");

            if (strUnit == "K")
              Size = Size * 1024;
            else if (strUnit == "M")
              Size = Size * 1024 * 1024;
            else if (strUnit == "G")
              Size = Size * 1000 * 1024 * 1024;

            pItem->m_dwSize = (int64_t)Size;
          }
        }

        items.Add(pItem);
      }
    }
  }
  http.Close();

  items.SetProperty("IsHTTPDirectory", true);

  return true;
}

bool CHTTPDirectory::Exists(const char* strPath)
{
  CFileCurl http;
  CURL url(strPath);
  struct __stat64 buffer;

  if( http.Stat(url, &buffer) != 0 )
  {
    return false;
  }

  if (buffer.st_mode == _S_IFDIR)
	  return true;

  return false;
}
