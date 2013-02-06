

#include "DNSNameCache.h"
#include "Application.h"
#include "threads/SingleLock.h"
#include "utils/log.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

CDNSNameCache g_DNSCache;

CCriticalSection CDNSNameCache::m_critical;

CDNSNameCache::CDNSNameCache(void)
{}

CDNSNameCache::~CDNSNameCache(void)
{}

bool CDNSNameCache::Lookup(const CStdString& strHostName, CStdString& strIpAddress)
{
  // first see if this is already an ip address
  unsigned long address = inet_addr(strHostName.c_str());
  if (address != INADDR_NONE)
  {
    strIpAddress.Format("%d.%d.%d.%d", (address & 0xFF), (address & 0xFF00) >> 8, (address & 0xFF0000) >> 16, (address & 0xFF000000) >> 24 );
    return true;
  }

  // check if there's a custom entry or if it's already cached
  if(g_DNSCache.GetCached(strHostName, strIpAddress))
    return true;

#ifndef _WIN32
  // perform netbios lookup (win32 is handling this via gethostbyname)
  char nmb_ip[100];
  char line[200];

  CStdString cmd = "nmblookup " + strHostName;
  FILE* fp = popen(cmd, "r");
  if (fp)
  {
    while (fgets(line, sizeof line, fp))
    {
      if (sscanf(line, "%99s *<00>\n", nmb_ip))
      {
        if (inet_addr(nmb_ip) != INADDR_NONE)
          strIpAddress = nmb_ip;
      }
    }
  }
  pclose(fp);

  if (!strIpAddress.IsEmpty())
  {
    g_DNSCache.Add(strHostName, strIpAddress);
    return true;
  }
#endif

  // perform dns lookup
  struct hostent *host = gethostbyname(strHostName.c_str());
  if (host && host->h_addr_list[0])
  {
    strIpAddress.Format("%d.%d.%d.%d", (unsigned char)host->h_addr_list[0][0], (unsigned char)host->h_addr_list[0][1], (unsigned char)host->h_addr_list[0][2], (unsigned char)host->h_addr_list[0][3]);
    g_DNSCache.Add(strHostName, strIpAddress);
    return true;
  }

  CLog::Log(LOGERROR, "Unable to lookup host: '%s'", strHostName.c_str());
  return false;
}

bool CDNSNameCache::GetCached(const CStdString& strHostName, CStdString& strIpAddress)
{
  CSingleLock lock(m_critical);

  // loop through all DNSname entries and see if strHostName is cached
  for (int i = 0; i < (int)g_DNSCache.m_vecDNSNames.size(); ++i)
  {
    CDNSName& DNSname = g_DNSCache.m_vecDNSNames[i];
    if ( DNSname.m_strHostName == strHostName )
    {
      strIpAddress = DNSname.m_strIpAddress;
      return true;
    }
  }

  // not cached
  return false;
}

void CDNSNameCache::Add(const CStdString &strHostName, const CStdString &strIpAddress)
{
  CDNSName dnsName;

  dnsName.m_strHostName = strHostName;
  dnsName.m_strIpAddress  = strIpAddress;

  CSingleLock lock(m_critical);
  g_DNSCache.m_vecDNSNames.push_back(dnsName);
}

