#pragma once


#include "peripherals/bus/PeripheralBus.h"
#include "peripherals/devices/Peripheral.h"

#ifdef TARGET_DARWIN_OSX
#include <IOKit/IOKitLib.h>
#include <IOKit/IOMessage.h>
#endif

namespace PERIPHERALS
{
  class CPeripherals;

  class CPeripheralBusUSB : public CPeripheralBus
  {
  public:
    CPeripheralBusUSB(CPeripherals *manager);
    virtual ~CPeripheralBusUSB();

    /*!
     * @see PeripheralBus::PerformDeviceScan()
     */
    bool PerformDeviceScan(PeripheralScanResults &results);

  protected:
    PeripheralScanResults m_scan_results;
  #ifdef TARGET_DARWIN_OSX
    static const PeripheralType GetType(int iDeviceClass);
    static void  DeviceDetachCallback(void *refCon, io_service_t service, natural_t messageType, void *messageArgument);
    static void  DeviceAttachCallback(CPeripheralBusUSB* refCon, io_iterator_t iterator);

    IONotificationPortRef m_notify_port;
    io_iterator_t         m_attach_iterator;
  #endif
  };

}
