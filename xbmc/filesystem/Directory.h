#pragma once


#include "IDirectory.h"

namespace XFILE
{
/*!
 \ingroup filesystem
 \brief Wrappers for \e IDirectory
 */
class CDirectory
{
public:
  CDirectory(void);
  virtual ~CDirectory(void);

  static bool GetDirectory(const CStdString& strPath
                         , CFileItemList &items
                         , CStdString strMask=""
                         , bool bUseFileDirectories=true
                         , bool allowPrompting=false
                         , DIR_CACHE_TYPE cacheDirectory=DIR_CACHE_ONCE
                         , bool extFileInfo=true
                         , bool allowThreads=false
                         , bool getHidden=false);

  static bool Create(const CStdString& strPath);
  static bool Exists(const CStdString& strPath);
  static bool Remove(const CStdString& strPath);

  /*! \brief Filter files that act like directories from the list, replacing them with their directory counterparts
   \param items The item list to filter
   \param mask  The mask to apply when filtering files */
  static void FilterFileDirectories(CFileItemList &items, const CStdString &mask);
};
}
