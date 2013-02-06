#pragma once


#if   defined(TARGET_WINDOWS)
#define HAVE_PERIPHERAL_BUS_USB 1
#include "win32/PeripheralBusUSB.h"
#elif defined(TARGET_LINUX) && defined(HAVE_LIBUDEV)
#define HAVE_PERIPHERAL_BUS_USB 1
#include "linux/PeripheralBusUSBLibUdev.h"
#elif defined(TARGET_LINUX) && defined(HAVE_LIBUSB)
#define HAVE_PERIPHERAL_BUS_USB 1
#include "linux/PeripheralBusUSBLibUSB.h"
#elif defined(TARGET_DARWIN)
#define HAVE_PERIPHERAL_BUS_USB 1
#include "osx/PeripheralBusUSB.h"
#endif
