#pragma once


#include "Peripheral.h"

namespace PERIPHERALS
{
  class CPeripheralTuner : public CPeripheral
  {
  public:
    CPeripheralTuner(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId);
    virtual ~CPeripheralTuner(void) {};
  };
}
