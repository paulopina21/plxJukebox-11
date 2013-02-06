#pragma once


#include "Peripheral.h"

namespace PERIPHERALS
{
  class CPeripheralDisk : public CPeripheral
  {
  public:
    CPeripheralDisk(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId);
    virtual ~CPeripheralDisk(void) {};
  };
}
