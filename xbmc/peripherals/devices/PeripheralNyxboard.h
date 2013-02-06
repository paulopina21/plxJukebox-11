#pragma once


#include "PeripheralHID.h"

namespace PERIPHERALS
{
  class CPeripheralNyxboard : public CPeripheralHID
  {
  public:
    CPeripheralNyxboard(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId);
    virtual ~CPeripheralNyxboard(void) {};
    virtual bool LookupSymAndUnicode(XBMC_keysym &keysym, uint8_t *key, char *unicode);
  };
}
