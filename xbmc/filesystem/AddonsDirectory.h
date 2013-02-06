#pragma once


#include "IDirectory.h"
#include "addons/AddonManager.h"

class CURL;
typedef boost::shared_ptr<CFileItem> CFileItemPtr;

namespace XFILE 
{

  /*!
  \ingroup windows
  \brief Get access to shares and it's directories.
  */
  class CAddonsDirectory : public IDirectory
  {
  public:
    CAddonsDirectory(void);
    virtual ~CAddonsDirectory(void);
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
    virtual bool Create(const char* strPath) { return true; }
    virtual bool Exists(const char* strPath) { return true; }
    virtual bool IsAllowed(const CStdString& strFile) const { return true; }

    /*! \brief Fetch script and plugin addons of a given content type
     \param content the content type to fetch
     \param addons the list of addons to fill with scripts and plugin content
     \return true if content is valid, false if it's invalid.
     */
    static bool GetScriptsAndPlugins(const CStdString &content, ADDON::VECADDONS &addons);

    /*! \brief Fetch scripts and plugins of a given content type
     \param content the content type to fetch
     \param items the list to fill with scripts and content
     \return true if more than one item is found, false otherwise.
     */
    static bool GetScriptsAndPlugins(const CStdString &content, CFileItemList &items);

    /*! \brief return the "Get More..." link item for the current content type
     \param content the content type for the link item
     \return a CFileItemPtr to a new item for the link.
     */
    static CFileItemPtr GetMoreItem(const CStdString &content);

    static void GenerateListing(CURL &path, ADDON::VECADDONS& addons, CFileItemList &items, bool reposAsFolders = true);
    static CFileItemPtr FileItemFromAddon(ADDON::AddonPtr &addon, const CStdString &basePath, bool folder = false);
  };
}
