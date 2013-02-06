#pragma once


#include "Peripheral.h"
#include "input/XBMC_keyboard.h"

namespace PERIPHERALS
{
  class CPeripheralHID : public CPeripheral
  {
  public:
    CPeripheralHID(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId);
    virtual ~CPeripheralHID(void);
    virtual bool InitialiseFeature(const PeripheralFeature feature);
    virtual bool LookupSymAndUnicode(XBMC_keysym &keysym, uint8_t *key, char *unicode) { return false; }
    virtual void OnSettingChanged(const CStdString &strChangedSetting);

  protected:
    bool       m_bInitialised;
    CStdString m_strKeymap;
  };
}
