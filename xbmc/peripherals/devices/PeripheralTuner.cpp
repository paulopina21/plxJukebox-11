

#include "PeripheralTuner.h"
#include "utils/log.h"

using namespace PERIPHERALS;

CPeripheralTuner::CPeripheralTuner(const PeripheralType type, const PeripheralBusType busType, const CStdString &strLocation, const CStdString &strDeviceName, int iVendorId, int iProductId) :
  CPeripheral(type, busType, strLocation, strDeviceName, iVendorId, iProductId)
{
  m_features.push_back(FEATURE_TUNER);
}
