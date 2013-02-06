#pragma once


#include "Peripheral.h"

namespace PERIPHERALS
{
  class CPeripheralNIC : public CPeripheral
  {
  public:
    CPeripheralNIC(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId);
    virtual ~CPeripheralNIC(void) {};
  };
}
