#include "PFCDirectory.h"
//#include "PFCManager.h"
#include "FilePFC.h"
#include "utils/log.h"
#include "utils/CharsetConverter.h"
#include "utils/URIUtils.h"
#include "Util.h"
#include "URL.h"
#include "FileItem.h"

#include <vector>

using namespace std;
namespace XFILE {

CPFCDirectory::CPFCDirectory()
{
}

CPFCDirectory::~CPFCDirectory()
{
}

bool CPFCDirectory::GetDirectory(const CStdString& strPathOrig, CFileItemList& items)
{
	CStdString strPath;

	/* if this isn't a proper archive path, assume it's the path to a archive file */
	if (!strPathOrig.Left(6).Equals("pfc://"))
		URIUtils::CreateArchivePath(strPath, "pfc", strPathOrig, "");
	else
		strPath = strPathOrig;

	CURL url(strPath);

	CStdString strArchive = url.GetHostName();
	CStdString strOptions = url.GetOptions();
	CStdString strPathInZip = url.GetFileName();

	url.SetOptions(""); // delete options to have a clean path to add stuff too
	url.SetFileName(""); // delete filename too as our names later will contain it

	CStdString strSlashPath = url.Get();

	CStdString strBuffer;

	// the RAR code depends on things having a "/" at the end of the path
	URIUtils::AddSlashAtEnd(strSlashPath);

	VECFILEENTRY entries;
	// turn on fast lookups
	bool bWasFast(items.GetFastLookup());
	items.SetFastLookup(true);

	CFilePFC PFCFile;
	if ( !PFCFile.Open(strPath) ) return false;
	if (!PFCFile.GetEntriesList(entries)) return false;

	CStdString strSkip;
	vector<CStdString> baseTokens;

	if (!strPathInZip.IsEmpty()) CUtil::Tokenize(strPathInZip, baseTokens, "/");

	for (VECFILEENTRY::iterator itFileEntry = entries.begin(); itFileEntry != entries.end(); ++itFileEntry)
	{

		CStdString strEntryName(itFileEntry->FileName);
		strEntryName.Replace('\\', '/');

		if (strEntryName == strPathInZip) // skip the listed dir
			continue;

		vector<CStdString> pathTokens;
		CUtil::Tokenize(strEntryName, pathTokens, "/");

		if (pathTokens.size() < baseTokens.size() + 1) continue;

		bool bAdd = (itFileEntry->EntryType != RPF_ENTRY_TYPE_FILE_HIDDEN && itFileEntry->EntryType != RPF_ENTRY_TYPE_SYSTEM);

		strEntryName = "";

		for (unsigned int i = 0; i < baseTokens.size(); ++i)
		{
			if (pathTokens[i] != baseTokens[i])
			{
				bAdd = false;
				break;
			}
			strEntryName += pathTokens[i] + "/";
		}

		if (!bAdd) continue;

		strEntryName += pathTokens[baseTokens.size()];
		char c = itFileEntry->FileName[strEntryName.size()];

		if (c == '/' || c == '\\') strEntryName += '/';

		bool bIsFolder = false;

		if (strEntryName[strEntryName.size() - 1] != '/')
		{ // this is a file
			strBuffer = strSlashPath + strEntryName + strOptions;
		}
		else
		{ // this is new folder. add if not already added
			bIsFolder = true;
			strBuffer = strSlashPath + strEntryName + strOptions;
			if (items.Contains(strBuffer)) // already added
				continue;
		}

		CFileItemPtr pFileItem(new CFileItem); // Laureon: This fileItem should receive the extra info from plexus album file...

		if (g_charsetConverter.isValidUtf8(pathTokens[baseTokens.size()]))
			g_charsetConverter.utf8ToStringCharset(pathTokens[baseTokens.size()]);

		pFileItem->SetLabel(pathTokens[baseTokens.size()]);

		if (bIsFolder)
			pFileItem->m_dwSize = 0;
		else
			pFileItem->m_dwSize = itFileEntry->UncryptedFileSize;

		pFileItem->SetPath(strBuffer);
		pFileItem->m_bIsFolder = bIsFolder;
		pFileItem->m_idepth = itFileEntry->Crypt;


		if (bIsFolder) {
			CStdString filepath = pFileItem->GetPath();
			URIUtils::AddSlashAtEnd(filepath);
			pFileItem->SetPath(filepath);
		}

		items.Add(pFileItem);
	}

	items.SetFastLookup(bWasFast);
	return true;
}

bool CPFCDirectory::ContainsFiles(const CStdString& strPath)
{
	VECFILEENTRY items;

	CFilePFC PFCFile;
  if ( !PFCFile.Open(strPath) ) return false;
  if (!PFCFile.GetEntriesList(items)) return false;

	//g_PFCManager.GetEntriesList(strPath, items);

	//return (items.size() > 1)? true:false;

	if (items.size())
	{
		if (items.size() > 1) return true;

		return false;
	}

	return false;
}

}
