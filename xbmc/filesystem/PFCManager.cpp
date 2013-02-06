#include "system.h"
#include "PFCManager.h"
#include "URL.h"
#include "utils/CharsetConverter.h"
#include "utils/log.h"
#include "utils/EndianSwap.h"
#include "utils/URIUtils.h"
#include "SpecialProtocol.h"
#include "tinyXML/tinyxml.h"

//#include "Rijndael.h"

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

CPFCManager::CPFCManager()  {
}

CPFCManager::~CPFCManager()  {

}

bool CPFCManager::CheckSign(sRPFHeader& RPFHeader) {
  if (RPFHeader.Signature[0] == RPF_PACKFILE_SGN0 && RPFHeader.Signature[1] == RPF_PACKFILE_SGN1 && RPFHeader.Signature[2] == RPF_PACKFILE_SGN2
      && RPFHeader.Signature[3] == RPF_PACKFILE_SGN3)
  {
    CLog::Log(LOGDEBUG, "PFCManager: File signed! Files declared: %i", RPFHeader.FileEntries);
    return true;
  }

  return false;
}

bool CPFCManager::Open(const CStdString& strFile, sRPFHeader& RPFHeader) {
  CLog::Log(LOGDEBUG, "CPFCManager::%s: Opening: %s", __FUNCTION__, strFile.c_str());
  if (!m_actualFile.Open(strFile))
  {
    CLog::Log(LOGERROR, "PFCManager: Can't open file: %s", strFile.c_str());
    return false;
  }

  if (m_actualFile.Read(&RPFHeader, sizeof(sRPFHeader)) != sizeof(sRPFHeader)) {
    CLog::Log(LOGERROR, "PFCManager: Reading Header: %s", strFile.c_str());
    return false;
  }

  if (!CheckSign(RPFHeader))
  {
    CLog::Log(LOGERROR, "PFCManager: Not a PFC: %s", strFile.c_str());
    return false;
  }

  CLog::Log(LOGDEBUG, "CPFCManager::%s: Openned: %s", __FUNCTION__, strFile.c_str());
  return true;
}

bool CPFCManager::GetFromCache(const CStdString& strFile, sFileMap& item, bool bAutoCache) {
  struct __stat64 sStatData = { };
  CLog::Log(LOGDEBUG, "CPFCManager::%s: Working: %s...", __FUNCTION__, strFile.c_str());

  for (VECPFCFILESMAP::iterator it = m_filesCache.begin(); it != m_filesCache.end(); ++it)
  {
    if (strFile == it->strPFCFileName)
    {
      if (CFile::Stat(strFile, &sStatData))
      {
        CLog::Log(LOGDEBUG, "CPFCManager::%s: failed to stat file %s", __FUNCTION__, strFile.c_str());
        return false;
      }

      if (sStatData.st_mtime == it->st_modtime)
      {
        item = *it;
        return true;
      }
      CLog::Log(LOGDEBUG, "CPFCManager::%s: %s outdated...", __FUNCTION__, strFile.c_str());
      m_filesCache.erase(it);
    }
  }

  CLog::Log(LOGDEBUG, "CPFCManager::%s: %s not in cache...", __FUNCTION__, strFile.c_str());
  if (bAutoCache) return AppendToCache(strFile, item);

  return false;
}

bool CPFCManager::AppendToCache(const CStdString& strFile, sFileMap& item) {
  CLog::Log(LOGDEBUG, "CPFCManager::%s: Working: %s...", __FUNCTION__, strFile.c_str());

  struct __stat64 sStatData = { };

  if (CFile::Stat(strFile, &sStatData) != 0)
  {
    CLog::Log(LOGERROR, "CPFCManager::%s: failed to stat file %s", __FUNCTION__, strFile.c_str());
    return false;
  }

  sFileMap fileMap;
  fileMap.strPFCFileName = strFile;
  if (!Open(strFile,  fileMap.sHeader)) return false;
  //fileMap.sHeader = m_fileHeader;

  try
  {
    fileMap.st_modtime = sStatData.st_mtime;
  }
  catch (...)
  {
    CLog::Log(LOGDEBUG, "CPFCManager::%s: failed getting stat info %s", __FUNCTION__, strFile.c_str());
    fileMap.st_modtime = 0;
  }
//	else
//	  fileMap.st_modtime = 0;

  uint32_t headerEntries = fileMap.sHeader.FileEntries;
  uint32_t iFileTableSize = ENTRYSIZE* fileMap.sHeader.FileEntries;

  if (headerEntries > 0)
  {
    int64_t seekpos = m_actualFile.GetLength() - iFileTableSize;

    if (!m_actualFile.Seek(seekpos, SEEK_SET))
    {
      CLog::Log(LOGERROR, "PFCManager: Can't seek: %s!", strFile.c_str());
      return false;
    }

    fileMap.vecFiles.clear();
    fileMap.vecFiles.resize(headerEntries);

    if (m_actualFile.Read(fileMap.vecFiles.data(), iFileTableSize) != iFileTableSize)
    {
      CLog::Log(LOGERROR, "PFCManager: Corrupted file: %s!", strFile.c_str());
      return false;
    }
      CLog::Log(LOGDEBUG, "CPFCManager::%s: Adding: %i entries to cache", __FUNCTION__, fileMap.vecFiles.size());
      m_filesCache.push_back(fileMap);
      item = fileMap;
      CLog::Log(LOGDEBUG, "CPFCManager::%s: OK", __FUNCTION__);
  }
  else
  {
    CLog::Log(LOGERROR, "PFCManager: Broken or empty file: %s!", strFile.c_str());
    return false;
  }
  if (fileMap.vecFiles.size() <= 0) return false;

//  try
//  {
//    m_filesCache.push_back(fileMap);
//    item = fileMap;
//  }
//  catch (...)
//  {
//    CLog::Log(LOGERROR, "PFCManager: Oops, Something wrong with memory allocation to the cache: %s!", strFile.c_str());
//    return false;
//  }
  return true;
}

bool CPFCManager::IsCached(const CStdString& strFile) {
  struct __stat64 sStatData = { };
  CLog::Log(LOGDEBUG, "CPFCManager::%s: Working: %s...", __FUNCTION__, strFile.c_str());

  for (VECPFCFILESMAP::iterator it = m_filesCache.begin(); it != m_filesCache.end(); ++it)
  {
    if (strFile == it->strPFCFileName)
    {
      if (CFile::Stat(strFile, &sStatData))
      {
        CLog::Log(LOGDEBUG, "CPFCManager::%s: failed to stat file %s", __FUNCTION__, strFile.c_str());
        return false;
      }

      if (sStatData.st_mtime == it->st_modtime)
      {
        return true;
      }
      CLog::Log(LOGDEBUG, "CPFCManager::%s: %s outdated...", __FUNCTION__, strFile.c_str());
      m_filesCache.erase(it);
    }
  }

  return false;
}


ePACKTYPE CPFCManager::GetPFCType(const CStdString& strPath) {
  CURL urlPath(strPath);
  CStdString strFile = urlPath.GetHostName();

  sFileMap fileMap;

  if (GetFromCache(strFile, fileMap, true))
  { // already listed, just return it, else append to cache
    return fileMap.sHeader.PackType;
  }

  return RPF_PACK_TYPE_NONE;
}

bool CPFCManager::GetEntriesList(const CStdString& strPath, VECFILEENTRY& items) {
  CURL urlPath(strPath);
  CStdString strFile = urlPath.GetHostName();

  CLog::Log(LOGDEBUG, "%s - Processing %s", __FUNCTION__, strFile.c_str());

  sFileMap fileMap;

  if (GetFromCache(strFile, fileMap, true))
  { // already listed, just return it, else append to cache
    items = fileMap.vecFiles;
    return true;
  }

  return false;
}

bool CPFCManager::GetFileEntry(const CStdString& strPath, sFileEntry& item) {
  VECFILEENTRY items;
  // we need to list the pfs
  if (!GetEntriesList(strPath, items)) return false;

  CURL urlPath(strPath);
  CStdString strFileName = urlPath.GetFileName();

  for (VECFILEENTRY::iterator it2 = items.begin(); it2 != items.end(); ++it2)
  {
    if (CStdString(it2->FileName) == strFileName)
    {
      memcpy(&item, &(*it2), sizeof(sFileEntry));
      return true;
    }
  }

  return false;
}

CAlbum CPFCManager::GetAlbumInfo(const CStdString& strPath) {
  CAlbum resultAlbum;

  TiXmlDocument xmlDocument;
  if (!GetDefsFile(strPath, xmlDocument)) return resultAlbum;

  TiXmlElement *artistElement = xmlDocument.RootElement()->FirstChildElement("artist");

  if (artistElement)
  {
    resultAlbum.Load(artistElement->FirstChildElement("album"), true, true);
  }

  return resultAlbum;
}

CArtist CPFCManager::GetArtistInfo(const CStdString& strPath) {
  CArtist resultAlbum;

  TiXmlDocument xmlDocument;
  if (!GetDefsFile(strPath, xmlDocument)) return resultAlbum;

  TiXmlElement *artistElement = xmlDocument.RootElement()->FirstChildElement("artist");

  if (artistElement)
  {
    resultAlbum.Load(artistElement, true, true);
  }

  return resultAlbum;
}

bool CPFCManager::GetDefsFile(const CStdString& strPath, TiXmlDocument& xmlDocument) {

//	CStdString strTemp = strPath;
//
//	if (!URIUtils::IsURL(strTemp)) {
//		CURL::Encode(strTemp);
//	}

  CURL urlPath(strPath);
  CStdString strFile = urlPath.GetHostName();

  URIUtils::CreateArchivePath(strFile, "pfc", strPath, DEFSFILE);

  char* defFile;
  CStdString strDoc;

  XFILE::CFile file;

  if (file.Open(strFile))
  {
    int size = (int) file.GetLength();

    try
    {
      defFile = new char[size + 1];
    }
    catch (...)
    {
      CLog::Log(LOGERROR, "%s: Exception while creating file buffer", __FUNCTION__);
      return false;
    }

    if (!defFile)
    {
      file.Close();
      return false;
    }

    file.Read(defFile, size);
    defFile[size] = 0;
    strDoc = defFile;

    file.Close();
    free(defFile);
  }

  // Laureon: Convert the document to UTF8...
  if (strDoc.Find("encoding=") == -1) g_charsetConverter.unknownToUTF8(strDoc);

  xmlDocument.Parse(strDoc.c_str());

  if (!xmlDocument.RootElement()) return false;

  return true;
}

bool CPFCManager::ExtractArchive(const CStdString& strArchive, const CStdString& strPath) {
  CStdString strPackPath;
  URIUtils::CreateArchivePath(strPackPath, "pfc", strArchive, "");

  VECFILEENTRY entry;
  GetEntriesList(strPackPath, entry);
  for (VECFILEENTRY::iterator it = entry.begin(); it != entry.end(); ++it)
  {

    if (it->FileName[strlen(it->FileName) - 1] == '/') // skip dirs
      continue;

    CStdString strFilePath(it->FileName);

    URIUtils::CreateArchivePath(strPackPath, "pfc", strArchive, strFilePath);
    if (!CFile::Cache(strPackPath.c_str(), (strPath + strFilePath).c_str())) return false;
  }

  return true;
}

void CPFCManager::CleanUp(const CStdString& strArchive, const CStdString& strPath) {
  CStdString strZipPath;
  URIUtils::CreateArchivePath(strZipPath, "pfc", strArchive, "");

  VECFILEENTRY entry;
  GetEntriesList(strZipPath, entry);
  for (VECFILEENTRY::iterator it = entry.begin(); it != entry.end(); ++it)
  {
    if (it->FileName[strlen(it->FileName) - 1] == '/') // skip dirs
      continue;
    CStdString strFilePath(it->FileName);
    CLog::Log(LOGDEBUG, "delete file: %s", (strPath + strFilePath).c_str());
    CFile::Delete((strPath + strFilePath).c_str());
  }

}

// Read local file header
//void CPfsManager::readHeader(const char* buffer, S_FILERECORD& info)
//{
//	info.header = Endian_SwapLE32(*(unsigned int*)buffer);
//	info.version = Endian_SwapLE16(*(unsigned short*)(buffer+4));
//	info.flags = Endian_SwapLE16(*(unsigned short*)(buffer+6));
//	info.method = Endian_SwapLE16(*(unsigned short*)(buffer+8));
//	info.mod_time = Endian_SwapLE16(*(unsigned short*)(buffer+10));
//	info.mod_date = Endian_SwapLE16(*(unsigned short*)(buffer+12));
//	info.crc32 = Endian_SwapLE32(*(unsigned int*)(buffer+14));
//	info.CryptedFileSize = Endian_SwapLE32(*(unsigned int*)(buffer+18));
//	info.UncryptedFileSize = Endian_SwapLE32(*(unsigned int*)(buffer+22));
//	info.flength = Endian_SwapLE16(*(unsigned short*)(buffer+26));
//	info.elength = Endian_SwapLE16(*(unsigned short*)(buffer+28));
//}
//
//// Read central file header (from central directory)
//void CPfsManager::readCHeader(const char* buffer, S_FILERECORD& info)
//{
//	info.header = Endian_SwapLE32(*(unsigned int*)buffer);
//	// Skip version made by
//	info.version = Endian_SwapLE16(*(unsigned short*)(buffer+6));
//	info.flags = Endian_SwapLE16(*(unsigned short*)(buffer+8));
//	info.method = Endian_SwapLE16(*(unsigned short*)(buffer+10));
//	info.mod_time = Endian_SwapLE16(*(unsigned short*)(buffer+12));
//	info.mod_date = Endian_SwapLE16(*(unsigned short*)(buffer+14));
//	info.crc32 = Endian_SwapLE32(*(unsigned int*)(buffer+16));
//	info.CryptedFileSize = Endian_SwapLE32(*(unsigned int*)(buffer+20));
//	info.UncryptedFileSize = Endian_SwapLE32(*(unsigned int*)(buffer+24));
//	info.flength = Endian_SwapLE16(*(unsigned short*)(buffer+28));
//	info.eclength = Endian_SwapLE16(*(unsigned short*)(buffer+30));
//	info.clength = Endian_SwapLE16(*(unsigned short*)(buffer+32));
//	// Skip disk number start, internal/external file attributes
//	info.lhdrOffset = Endian_SwapLE32(*(unsigned int*)(buffer+42));
//
//}

void CPFCManager::release(const CStdString& strPath) {
  CURL url(strPath);
  CStdString strFile = url.GetHostName();

  for (VECPFCFILESMAP::iterator it = m_filesCache.begin(); it != m_filesCache.end(); ++it)
  {
    if (strFile == it->strPFCFileName)
    {
      m_filesCache.erase(it);
    }
  }

}
