#pragma once



#include "threads/CriticalSection.h"
#include "utils/StdString.h"

struct DSDeviceInfo
{
  LPGUID lpGuid;
  CStdString strDescription;
  CStdString strModule;
};

class CWDSound
{
public:
  CWDSound(void);
  virtual ~CWDSound(void);

  std::vector<DSDeviceInfo> GetSoundDevices();
  

private:

  CCriticalSection m_critSection;
  std::vector<DSDeviceInfo> vDSDeviceInfo;

  BOOL direct_sound_enumerator_member_callback(
   LPGUID lpGuid,
   LPCTSTR lpcstrDescription,
   LPCTSTR lpcstrModule
  );

  friend BOOL CALLBACK direct_sound_enumerator_callback(
   LPGUID lpGuid,
   LPCTSTR lpcstrDescription,
   LPCTSTR lpcstrModule,
   LPVOID lpContext
  );

  
};

