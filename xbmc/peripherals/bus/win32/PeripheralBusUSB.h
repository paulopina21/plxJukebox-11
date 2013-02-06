#pragma once


#include "peripherals/bus/PeripheralBus.h"
#include "peripherals/devices/Peripheral.h"
#include <setupapi.h> //needed for GUID

namespace PERIPHERALS
{
  class CPeripherals;

  class CPeripheralBusUSB : public CPeripheralBus
  {
  public:
    CPeripheralBusUSB(CPeripherals *manager);

    /*!
     * @see PeripheralBus::PerformDeviceScan()
     */
    bool PerformDeviceScan(PeripheralScanResults &results);

  private:
    bool PerformDeviceScan(const GUID *guid, const PeripheralType type, PeripheralScanResults &results);
    bool GetProductAndVendorId(const PeripheralType type, const CStdString &strDeviceLocation, int *iVendorId, int *iProductId);
  };
}
