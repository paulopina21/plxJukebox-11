#pragma once


#include "peripherals/bus/PeripheralBus.h"
#include "peripherals/devices/Peripheral.h"

struct usb_bus;

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

  protected:
    static const PeripheralType GetType(int iDeviceClass);
    struct usb_bus *m_busses;
  };
}
