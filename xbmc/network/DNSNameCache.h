#pragma once



#include "utils/StdString.h"

#include <vector>

class CCriticalSection;

class CDNSNameCache
{
public:
  class CDNSName
  {
  public:
    CStdString m_strHostName;
    CStdString m_strIpAddress;
  };
  CDNSNameCache(void);
  virtual ~CDNSNameCache(void);
  static bool Lookup(const CStdString& strHostName, CStdString& strIpAddress);
  static void Add(const CStdString& strHostName, const CStdString& strIpAddress);

protected:
  static bool GetCached(const CStdString& strHostName, CStdString& strIpAddress);
  static CCriticalSection m_critical;
  std::vector<CDNSName> m_vecDNSNames;
};
