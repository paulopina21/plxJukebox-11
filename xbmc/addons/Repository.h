#pragma once


#include "Addon.h"
#include "AddonManager.h"
#include "XBDateTime.h"
#include "URL.h"
#include "utils/Job.h"
#include "threads/CriticalSection.h"
#include "threads/SingleLock.h"

namespace ADDON
{
  class CRepository;
  typedef boost::shared_ptr<CRepository> RepositoryPtr;
  class CRepository : public CAddon
  {
  public:
    AddonPtr Clone(const AddonPtr &self) const;
    CRepository(const AddonProps& props);
    CRepository(const cp_extension_t *props);
    virtual ~CRepository();

    CStdString Checksum();

    /*! \brief Get the md5 hash for an addon.
     \param the addon in question.
     \return the md5 hash for the given addon, empty if non exists.
     */
    CStdString GetAddonHash(const AddonPtr& addon);
    VECADDONS Parse();
  private:
    CStdString FetchChecksum(const CStdString& url);
    CRepository(const CRepository&, const AddonPtr&);
    CStdString m_info;
    CStdString m_checksum;
    CStdString m_datadir;
    bool m_compressed; // gzipped info xml
    bool m_zipped;     // zipped addons
    bool m_hashes;     // repo supports hashes. e.g. plugin.i.rule-1.0.5.zip.md5
    CCriticalSection m_critSection;
  };

  class CRepositoryUpdateJob : public CJob
  {
  public:
    CRepositoryUpdateJob(const VECADDONS& repos);
    virtual ~CRepositoryUpdateJob() {}

    virtual const char *GetType() const { return "repoupdate"; };
    virtual bool DoWork();
  private:
    VECADDONS GrabAddons(RepositoryPtr& repo);

    VECADDONS m_repos;
  };
}

