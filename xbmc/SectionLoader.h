#pragma once


#include "utils/StdString.h"
#include "threads/CriticalSection.h"
#include "utils/GlobalsHandling.h"

//  forward
class LibraryLoader;

class CSectionLoader
{
public:
  class CSection
  {
  public:
    CStdString m_strSectionName;
    long m_lReferenceCount;
    unsigned int m_unloadDelayStartTick;
  };
  class CDll
  {
  public:
    CStdString m_strDllName;
    long m_lReferenceCount;
    LibraryLoader *m_pDll;
    unsigned int m_unloadDelayStartTick;
    bool m_bDelayUnload;
  };
  CSectionLoader(void);
  virtual ~CSectionLoader(void);

  static bool IsLoaded(const CStdString& strSection);
  static bool Load(const CStdString& strSection);
  static void Unload(const CStdString& strSection);
  static LibraryLoader* LoadDLL(const CStdString& strSection, bool bDelayUnload=true, bool bLoadSymbols=false);
  static void UnloadDLL(const CStdString& strSection);
  static void UnloadDelayed();
protected:
  std::vector<CSection> m_vecLoadedSections;
  typedef std::vector<CSection>::iterator ivecLoadedSections;
  std::vector<CDll> m_vecLoadedDLLs;
  CCriticalSection m_critSection;

private:
  void UnloadAll();
};

XBMC_GLOBAL_REF(CSectionLoader,g_sectionLoader);
#define g_sectionLoader XBMC_GLOBAL_USE(CSectionLoader)

