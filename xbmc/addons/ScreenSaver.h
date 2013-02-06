
#pragma once

#include "AddonDll.h"
#include "include/xbmc_scr_types.h"

typedef DllAddon<ScreenSaver, SCR_PROPS> DllScreenSaver;

namespace ADDON
{

class CScreenSaver : public ADDON::CAddonDll<DllScreenSaver, ScreenSaver, SCR_PROPS>
{
public:
  CScreenSaver(const AddonProps &props) : ADDON::CAddonDll<DllScreenSaver, ScreenSaver, SCR_PROPS>(props) {};
  CScreenSaver(const cp_extension_t *ext) : ADDON::CAddonDll<DllScreenSaver, ScreenSaver, SCR_PROPS>(ext) {};
  CScreenSaver(const char *addonID);
  virtual ~CScreenSaver() {}

  // Things that MUST be supplied by the child classes
  bool CreateScreenSaver();
  void Start();
  void Render();
  void GetInfo(SCR_INFO *info);
  void Destroy();
};

} /*namespace ADDON*/
