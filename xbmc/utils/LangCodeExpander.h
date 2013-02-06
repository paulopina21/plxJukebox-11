#pragma once


#include "utils/StdString.h"
#include <map>

class TiXmlElement;

class CLangCodeExpander
{
public:

  CLangCodeExpander(void);
  ~CLangCodeExpander(void);

  bool Lookup(CStdString& desc, const CStdString& code);
  bool Lookup(CStdString& desc, const int code);
#ifdef _WIN32
  bool ConvertTwoToThreeCharCode(CStdString& strThreeCharCode, const CStdString& strTwoCharCode, bool localeHack = false);
#else
  bool ConvertTwoToThreeCharCode(CStdString& strThreeCharCode, const CStdString& strTwoCharCode);
#endif
  bool ConvertLinuxToWindowsRegionCodes(const CStdString& strTwoCharCode, CStdString& strThreeCharCode);

  void LoadUserCodes(const TiXmlElement* pRootElement);
  void Clear();
protected:


  typedef std::map<CStdString, CStdString> STRINGLOOKUPTABLE;
  STRINGLOOKUPTABLE m_mapUser;

  bool LookupInDb(CStdString& desc, const CStdString& code);
  bool LookupInMap(CStdString& desc, const CStdString& code);
};

extern CLangCodeExpander g_LangCodeExpander;
