

#include "PeripheralNyxboard.h"
#include "PeripheralHID.h"
#include "guilib/Key.h"
#include "utils/log.h"
#include "Application.h"

using namespace PERIPHERALS;
using namespace std;

CPeripheralNyxboard::CPeripheralNyxboard(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId) :
  CPeripheralHID(type, busType, strLocation, strDeviceName, iVendorId, iProductId)
{
  m_features.push_back(FEATURE_NYXBOARD);
}

bool CPeripheralNyxboard::LookupSymAndUnicode(XBMC_keysym &keysym, uint8_t *key, char *unicode)
{
  CStdString strCommand;
  if (keysym.sym == XBMCK_F7 && keysym.mod == XBMCKMOD_NONE && GetSettingBool("enable_flip_commands"))
  {
    /* switched to keyboard side */
    CLog::Log(LOGDEBUG, "%s - switched to keyboard side", __FUNCTION__);
    strCommand = GetSettingString("flip_keyboard");
  }
  else if (keysym.sym == XBMCK_F7 && keysym.mod == XBMCKMOD_LCTRL && GetSettingBool("enable_flip_commands"))
  {
    /* switched to remote side */
    CLog::Log(LOGDEBUG, "%s - switched to remote side", __FUNCTION__);
    strCommand = GetSettingString("flip_remote");
  }
  else if (keysym.sym == XBMCK_F4 && keysym.mod == XBMCKMOD_NONE)
  {
    /* 'user' key pressed */
    CLog::Log(LOGDEBUG, "%s - 'user' key pressed", __FUNCTION__);
    strCommand = GetSettingString("key_user");
  }

  if (!strCommand.IsEmpty())
  {
    CLog::Log(LOGDEBUG, "%s - executing command '%s'", __FUNCTION__, strCommand.c_str());
    if (g_application.ExecuteXBMCAction(strCommand))
    {
      *key = 0;
      *unicode = (char) 0;
      return true;
    }
  }

  return false;
}
