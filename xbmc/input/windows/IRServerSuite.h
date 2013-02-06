#pragma once


#include <winsock2.h>
#include "utils/StdString.h"
#include "IrssMessage.h"
#include "threads/Thread.h"

class CRemoteControl : CThread
{
public:
  CRemoteControl();
  ~CRemoteControl();
  void Initialize();
  void Disconnect();
  void Reset();
  void Update();
  WORD GetButton();
  unsigned int GetHoldTime() const;
  bool IsInitialized() {return m_bInitialized;}

  //lirc stuff, not implemented
  bool IsInUse() {return false;}
  void setUsed(bool value);
  void AddSendCommand(const CStdString& command) {}

protected:
  virtual void Process();

private:
  WORD  m_button;
  bool  m_bInitialized;
  SOCKET m_socket;
  bool m_isConnecting;
  int  m_iAttempt;
  CStdString m_deviceName;
  CStdString m_keyCode;

  bool SendPacket(CIrssMessage& message);
  bool ReadPacket(CIrssMessage& message);
  int  ReadN(char *buffer, int n);
  bool WriteN(const char *buffer, int n);
  bool Connect();
  void Close();

  bool HandleRemoteEvent(CIrssMessage& message);
};

extern CRemoteControl g_RemoteControl;
