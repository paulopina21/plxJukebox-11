#pragma once


#include "threads/Thread.h"
#include "IAddon.h"
#include "include/xbmc_addon_types.h"
#include "threads/CriticalSection.h"

namespace ADDON
{
  /**
  * Class - CAddonStatusHandler
  * Used to informate the user about occurred errors and
  * changes inside Add-on's, and ask him what to do.
  * It can executed in the same thread as the calling
  * function or in a seperate thread.
  */
  class CAddonStatusHandler : private CThread
  {
    public:
      CAddonStatusHandler(const CStdString &addonID, ADDON_STATUS status, CStdString message, bool sameThread = true);
      ~CAddonStatusHandler();

      /* Thread handling */
      virtual void Process();
      virtual void OnStartup();
      virtual void OnExit();

    private:
      static CCriticalSection   m_critSection;
      AddonPtr                  m_addon;
      ADDON_STATUS              m_status;
      CStdString                m_message;
  };


}
