
#include "Service.h"
#include "AddonManager.h"
#include "utils/log.h"
#ifdef HAS_PYTHON
#include "interfaces/python/XBPython.h"
#endif

using namespace std;

namespace ADDON
{

CService::CService(const cp_extension_t *ext)
  : CAddon(ext), m_type(UNKNOWN), m_startOption(LOGIN)
{
  BuildServiceType();

  CStdString start = CAddonMgr::Get().GetExtValue(ext->configuration, "@start");
  if (start.Equals("startup"))
    m_startOption = STARTUP;
}


CService::CService(const AddonProps &props)
  : CAddon(props), m_type(UNKNOWN), m_startOption(LOGIN)
{
  BuildServiceType();
}

bool CService::Start()
{
  bool ret = true;
  switch (m_type)
  {
#ifdef HAS_PYTHON
  case PYTHON:
    ret = (g_pythonParser.evalFile(LibPath(), this->shared_from_this()) != -1);
    break;
#endif

  case UNKNOWN:
  default:
    ret = false;
    break;
  }

  return ret;
}

bool CService::Stop()
{
  bool ret = true;

  switch (m_type)
  {
#ifdef HAS_PYTHON
  case PYTHON:
    ret = g_pythonParser.StopScript(LibPath());
    break;
#endif

  case UNKNOWN:
  default:
    ret = false;
    break;
  }

  return ret;
}

void CService::BuildServiceType()
{
  CStdString str = LibPath();
  CStdString ext;

  size_t p = str.find_last_of('.');
  if (p != string::npos)
    ext = str.substr(p + 1);

#ifdef HAS_PYTHON
  CStdString pythonExt = ADDON_PYTHON_EXT;
  pythonExt.erase(0, 2);
  if ( ext.Equals(pythonExt) )
    m_type = PYTHON;
  else
#endif
  {
    m_type = UNKNOWN;
    CLog::Log(LOGERROR, "ADDON: extension '%s' is not currently supported for service addon", ext.c_str());
  }
}

}
