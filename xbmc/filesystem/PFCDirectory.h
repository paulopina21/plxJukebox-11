#ifndef PFC_DIRECTORY_H
#define PFC_DIRECTORY_H

#include "IFileDirectory.h"

namespace XFILE {

class CPFCDirectory: public IFileDirectory {
public:
	CPFCDirectory();
	~CPFCDirectory();

	virtual bool GetDirectory(const CStdString& strPath, CFileItemList& items);
	virtual bool ContainsFiles(const CStdString& strPath);

	virtual DIR_CACHE_TYPE GetCacheType(const CStdString& strPath) const
	{
		return DIR_CACHE_ALWAYS;
	}
};

}

#endif
