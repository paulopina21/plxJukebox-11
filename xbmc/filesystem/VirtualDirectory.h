#pragma once


#include "IDirectory.h"
#include "MediaSource.h"

namespace XFILE
{

  /*!
  \ingroup windows
  \brief Get access to shares and it's directories.
  */
  class CVirtualDirectory : public IDirectory
  {
  public:
    CVirtualDirectory(void);
    virtual ~CVirtualDirectory(void);
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items);
    virtual bool GetDirectory(const CStdString& strPath, CFileItemList &items, bool bUseFileDirectories);
    void SetSources(const VECSOURCES& vecSources);
    inline unsigned int GetNumberOfSources() 
    {
      return m_vecSources.size();
    }

    bool IsSource(const CStdString& strPath, VECSOURCES *sources = NULL, CStdString *name = NULL) const;
    bool IsInSource(const CStdString& strPath) const;

    inline const CMediaSource& operator [](const int index) const
    {
      return m_vecSources[index];
    }

    inline CMediaSource& operator[](const int index)
    {
      return m_vecSources[index];
    }

    void GetSources(VECSOURCES &sources) const;

    void AllowNonLocalSources(bool allow) { m_allowNonLocalSources = allow; };

    /*! \brief Set whether we allow threaded loading of directories.
     The default is to allow threading, so this can be used to disable it.
     \param allowThreads if true we allow threads, if false we don't.
     */
    void SetAllowThreads(bool allowThreads) { m_allowThreads = allowThreads; };
  protected:
    void CacheThumbs(CFileItemList &items);

    VECSOURCES m_vecSources;
    bool       m_allowNonLocalSources;
    bool       m_allowThreads;
  };
}
