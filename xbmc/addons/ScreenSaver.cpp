
#include "ScreenSaver.h"
#include "settings/Settings.h"
#include "windowing/WindowingFactory.h"

namespace ADDON
{

  CScreenSaver::CScreenSaver(const char *addonID)
   : ADDON::CAddonDll<DllScreenSaver, ScreenSaver, SCR_PROPS>(AddonProps(addonID, ADDON_UNKNOWN, "", ""))
  {
  }

bool CScreenSaver::CreateScreenSaver()
{
 // pass it the screen width,height
 // and the name of the screensaver
  int iWidth = g_graphicsContext.GetWidth();
  int iHeight = g_graphicsContext.GetHeight();

  m_pInfo = new SCR_PROPS;
#ifdef HAS_DX
  m_pInfo->device     = g_Windowing.Get3DDevice();
#else
  m_pInfo->device     = NULL;
#endif
  m_pInfo->x          = 0;
  m_pInfo->y          = 0;
  m_pInfo->width      = iWidth;
  m_pInfo->height     = iHeight;
  m_pInfo->pixelRatio = g_settings.m_ResInfo[g_graphicsContext.GetVideoResolution()].fPixelRatio;
  m_pInfo->name       = strdup(Name().c_str());
  m_pInfo->presets    = strdup(_P(Path()).c_str());
  m_pInfo->profile    = strdup(_P(Profile()).c_str());

  if (CAddonDll<DllScreenSaver, ScreenSaver, SCR_PROPS>::Create())
    return true;

  return false;
}

void CScreenSaver::Start()
{
  // notify screen saver that they should start
  if (Initialized()) m_pStruct->Start();
}

void CScreenSaver::Render()
{
  // ask screensaver to render itself
  if (Initialized()) m_pStruct->Render();
}

void CScreenSaver::GetInfo(SCR_INFO *info)
{
  // get info from screensaver
  if (Initialized()) m_pStruct->GetInfo(info);
}

void CScreenSaver::Destroy()
{
  // Release what was allocated in method CScreenSaver::CreateScreenSaver.
  if (m_pInfo)
  {
    free((void *) m_pInfo->name);
    free((void *) m_pInfo->presets);
    free((void *) m_pInfo->profile);

    delete m_pInfo;
    m_pInfo = NULL;
  }

  CAddonDll<DllScreenSaver, ScreenSaver, SCR_PROPS>::Destroy();
}

} /*namespace ADDON*/

