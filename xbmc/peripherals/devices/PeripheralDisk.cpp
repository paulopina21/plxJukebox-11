

#include "PeripheralDisk.h"
#include "guilib/LocalizeStrings.h"

using namespace PERIPHERALS;

CPeripheralDisk::CPeripheralDisk(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId) :
  CPeripheral(type, busType, strLocation, strDeviceName.IsEmpty() ? g_localizeStrings.Get(35003) : strDeviceName, iVendorId, iProductId)
{
  m_features.push_back(FEATURE_DISK);
}
