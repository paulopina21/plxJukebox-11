

#include "LCDFactory.h"
#include "../linux/XLCDproc.h"

ILCD* g_lcd = NULL;
CLCDFactory::CLCDFactory(void)
{}

CLCDFactory::~CLCDFactory(void)
{}

ILCD* CLCDFactory::Create()
{
#ifdef _LINUX
  return new XLCDproc();
#endif
}
