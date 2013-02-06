
#ifndef LINUXINPUTDEVICES_H_
#define LINUXINPUTDEVICES_H_

#include <vector>
#include <string>
#include "windowing/XBMC_events.h"
#include "input/XBMC_keyboard.h"
#include "threads/SingleLock.h"

struct KeymapEntry
{
  int code;
  unsigned short base;
  unsigned short shift;
  unsigned short alt;
  unsigned short altShift;
};

class CLinuxInputDevice
{
public:
  CLinuxInputDevice(const std::string fileName, int index);
  ~CLinuxInputDevice();
  XBMC_Event ReadEvent();
 
private:
  XBMCKey TranslateKey(unsigned short code);
  bool KeyEvent(const struct input_event& levt, XBMC_Event& devt);
  bool RelEvent(const struct input_event& levt, XBMC_Event& devt);
  bool AbsEvent(const struct input_event& levt, XBMC_Event& devt);
  bool TranslateEvent(const struct input_event& levt, XBMC_Event& devt);
  void SetLed(int led, int state);
  void GetInfo(int fd);
  bool Open();
  void Close();
  unsigned short KeyboardReadValue(unsigned char table, unsigned char index);
  XBMCMod UpdateModifiers(XBMC_Event& devt);
  bool GetKeymapEntry(KeymapEntry& entry);
  int KeyboardGetSymbol(unsigned short value);

  int m_fd;
  int m_vt_fd;
  bool m_hasLeds;
  std::string m_fileName;
  bool m_ledState[3];
  int m_mouseX;
  int m_mouseY;
  int m_deviceIndex;
  int m_keyMods;
  int m_lastKeyMods;
  char m_deviceName[256];
  int m_deviceType;
  int m_devicePreferredId;
  int m_deviceCaps;
  int m_deviceMinKeyCode;
  int m_deviceMaxKeyCode;
  int m_deviceMaxAxis;
  bool m_bSkipNonKeyEvents;
};

class CLinuxInputDevices
{
public:
  void InitAvailable();
  XBMC_Event ReadEvent();
  bool IsRemoteLowBattery();
  bool IsRemoteNotPaired();
private:
  CCriticalSection m_devicesListLock;
  bool CheckDevice(const char *device);
  std::vector<CLinuxInputDevice*> m_devices;
};

#endif /* LINUXINPUTDEVICES_H_ */
