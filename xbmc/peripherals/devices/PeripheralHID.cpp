

#include "PeripheralHID.h"
#include "utils/log.h"
#include "settings/Settings.h"
#include "guilib/LocalizeStrings.h"
#include "input/ButtonTranslator.h"

using namespace PERIPHERALS;
using namespace std;

CPeripheralHID::CPeripheralHID(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId) :
  CPeripheral(type, busType, strLocation, strDeviceName.IsEmpty() ? g_localizeStrings.Get(35001) : strDeviceName, iVendorId, iProductId),
  m_bInitialised(false)
{
  m_features.push_back(FEATURE_HID);
}

CPeripheralHID::~CPeripheralHID(void)
{
  if (!m_strKeymap.IsEmpty() && GetSettingBool("keymap_enabled"))
  {
    CLog::Log(LOGDEBUG, "%s - switching active keymapping to: default", __FUNCTION__);
    CButtonTranslator::GetInstance().RemoveDevice(m_strKeymap);
  }
}

bool CPeripheralHID::InitialiseFeature(const PeripheralFeature feature)
{
  if (feature == FEATURE_HID && !m_bInitialised)
  {
    m_bInitialised = true;

    if (HasSetting("keymap"))
      m_strKeymap = GetSettingString("keymap");

    if (m_strKeymap.IsEmpty())
    {
      m_strKeymap.Format("v%sp%s", VendorIdAsString(), ProductIdAsString());
      SetSetting("keymap", m_strKeymap);
    }

    if (!m_strKeymap.IsEmpty())
    {
      bool bKeymapEnabled(GetSettingBool("keymap_enabled"));
      if (bKeymapEnabled)
      {
        CLog::Log(LOGDEBUG, "%s - adding keymapping for: %s", __FUNCTION__, m_strKeymap.c_str());
        CButtonTranslator::GetInstance().AddDevice(m_strKeymap);
      }
      else if (!bKeymapEnabled)
      {
        CLog::Log(LOGDEBUG, "%s - removing keymapping for: %s", __FUNCTION__, m_strKeymap.c_str());
        CButtonTranslator::GetInstance().RemoveDevice(m_strKeymap);
      }
    }

    CLog::Log(LOGDEBUG, "%s - initialised HID device (%s:%s)", __FUNCTION__, m_strVendorId.c_str(), m_strProductId.c_str());
  }

  return CPeripheral::InitialiseFeature(feature);
}

void CPeripheralHID::OnSettingChanged(const CStdString &strChangedSetting)
{
  if (m_bInitialised && ((strChangedSetting.Equals("keymap") && GetSettingBool("keymap_enabled")) || strChangedSetting.Equals("keymap_enabled")))
  {
    m_bInitialised = false;
    InitialiseFeature(FEATURE_HID);
  }
}

