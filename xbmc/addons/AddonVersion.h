

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <boost/operators.hpp>
#include "utils/StdString.h"

namespace ADDON
{
  class AddonVersion : public boost::totally_ordered<AddonVersion> {
  public:
    AddonVersion(const AddonVersion& other) : mUpstream(NULL), mRevision(NULL) { *this = other; }
    explicit AddonVersion(const CStdString& version);
    ~AddonVersion();

    int Epoch() const { return mEpoch; }
    const char *Upstream() const { return mUpstream; }
    const char *Revision() const { return mRevision; }

    AddonVersion& operator=(const AddonVersion& other);
    bool operator<(const AddonVersion& other) const;
    bool operator==(const AddonVersion& other) const;
    CStdString Print() const;
    const char *c_str() const { return m_originalVersion.c_str(); };

    static bool SplitFileName(CStdString& ID, CStdString& version,
                              const CStdString& filename);
  protected:
    CStdString m_originalVersion;
    int mEpoch;
    char *mUpstream;
    char *mRevision;

    static int CompareComponent(const char *a, const char *b);
  };

  inline AddonVersion::~AddonVersion()
  {
    free(mUpstream);
    free(mRevision);
  }

  inline bool AddonVersion::operator==(const AddonVersion& other) const
  {
    return Epoch() == other.Epoch()
      && strcmp(Upstream(), other.Upstream()) == 0
      && strcmp(Revision(), other.Revision()) == 0;
  }

  inline AddonVersion& AddonVersion::operator=(const AddonVersion& other)
  {
    free(mUpstream);
    free(mRevision);
    mEpoch = other.Epoch();
    mUpstream = strdup(other.Upstream());
    mRevision = strdup(other.Revision());
    m_originalVersion = other.m_originalVersion;
    return *this;
  }
}
