

#include "system.h"
#include "WINDirectSound.h"
#include "threads/SingleLock.h"
#include "utils/log.h"
#include "utils/CharsetConverter.h"


BOOL CALLBACK direct_sound_enumerator_callback( LPGUID lpGuid, LPCTSTR lpcstrDescription, LPCTSTR lpcstrModule, LPVOID lpContext)
{
  CWDSound& enumerator = *static_cast<CWDSound*>(lpContext);
  return enumerator.direct_sound_enumerator_member_callback(lpGuid,lpcstrDescription, lpcstrModule);
}

CWDSound::CWDSound(void)
{
}

CWDSound::~CWDSound(void)
{
  vDSDeviceInfo.clear();
}

std::vector<DSDeviceInfo> CWDSound::GetSoundDevices()
{
  CSingleLock lock (m_critSection);
  vDSDeviceInfo.clear();
  if (FAILED(DirectSoundEnumerate(direct_sound_enumerator_callback, this)))
    CLog::Log(LOGERROR, "%s - failed to enumerate output devices", __FUNCTION__);

  return vDSDeviceInfo;
}

BOOL CWDSound::direct_sound_enumerator_member_callback( LPGUID lpGuid, LPCTSTR lpcstrDescription, LPCTSTR lpcstrModule) 
{
  struct DSDeviceInfo dInfo;
  dInfo.lpGuid = lpGuid;
  dInfo.strDescription = lpcstrDescription;
  dInfo.strModule = lpcstrModule ;
  g_charsetConverter.unknownToUTF8(dInfo.strDescription);
  g_charsetConverter.unknownToUTF8(dInfo.strModule);
  CWDSound::vDSDeviceInfo.push_back(dInfo);
  CLog::Log(LOGDEBUG, "%s - found Device: %s", __FUNCTION__,lpcstrDescription);
  return TRUE;
}