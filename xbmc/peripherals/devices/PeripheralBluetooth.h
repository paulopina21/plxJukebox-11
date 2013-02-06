#pragma once


#include "Peripheral.h"

namespace PERIPHERALS
{
  class CPeripheralBluetooth : public CPeripheral
  {
  public:
    CPeripheralBluetooth(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId);
    virtual ~CPeripheralBluetooth(void) {};
  };
}
