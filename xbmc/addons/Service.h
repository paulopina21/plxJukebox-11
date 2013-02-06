#pragma once

#include "Addon.h"

namespace ADDON
{

  class CService: public CAddon
  {
  public:

    enum TYPE
    {
      UNKNOWN,
      PYTHON
    };

    enum START_OPTION
    {
      STARTUP,
      LOGIN
    };

    CService(const cp_extension_t *ext);
    CService(const AddonProps &props);

    bool Start();
    bool Stop();
    TYPE GetServiceType() { return m_type; }
    START_OPTION GetStartOption() { return m_startOption; }

  protected:
    void BuildServiceType();

  private:
    TYPE m_type;
    START_OPTION m_startOption;
  };
}