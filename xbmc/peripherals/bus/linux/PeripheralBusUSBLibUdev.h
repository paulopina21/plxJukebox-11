#pragma once


#include "peripherals/bus/PeripheralBus.h"
#include "peripherals/devices/Peripheral.h"

struct udev;
struct udev_monitor;

namespace PERIPHERALS
{
  class CPeripherals;

  class CPeripheralBusUSB : public CPeripheralBus
  {
  public:
    CPeripheralBusUSB(CPeripherals *manager);
    virtual ~CPeripheralBusUSB(void);

    virtual void Clear(void);

    /*!
     * @see PeripheralBus::PerformDeviceScan()
     */
    bool PerformDeviceScan(PeripheralScanResults &results);

  protected:
    static const PeripheralType GetType(int iDeviceClass);

    virtual void Process(void);
    bool WaitForUpdate(void);

    struct udev *        m_udev;
    struct udev_monitor *m_udevMon;
    int                  m_udevFd;
  };
}
