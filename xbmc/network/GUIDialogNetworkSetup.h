#pragma once



#include "guilib/GUIDialog.h"

class CGUIDialogNetworkSetup :
      public CGUIDialog
{
public:
  enum NET_PROTOCOL { NET_PROTOCOL_SMB = 0,
                      NET_PROTOCOL_XBMSP,
                      NET_PROTOCOL_FTP,
                      NET_PROTOCOL_HTTP,
                      NET_PROTOCOL_HTTPS,
                      NET_PROTOCOL_DAV,
                      NET_PROTOCOL_DAVS,
                      NET_PROTOCOL_DAAP,
                      NET_PROTOCOL_UPNP,
                      NET_PROTOCOL_RSS,
                      NET_PROTOCOL_HTSP,
                      NET_PROTOCOL_VTP,
                      NET_PROTOCOL_MYTH,
                      NET_PROTOCOL_TUXBOX,
                      NET_PROTOCOL_SFTP,
                      NET_PROTOCOL_NFS, 
                      NET_PROTOCOL_AFP};
  CGUIDialogNetworkSetup(void);
  virtual ~CGUIDialogNetworkSetup(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnBack(int actionID);
  virtual void OnInitWindow();

  static bool ShowAndGetNetworkAddress(CStdString &path);

  CStdString ConstructPath() const;
  void SetPath(const CStdString &path);
  bool IsConfirmed() const { return m_confirmed; };

protected:
  void OnProtocolChange();
  void OnServerBrowse();
  void OnOK();
  void OnCancel();
  void UpdateButtons();

  NET_PROTOCOL m_protocol;
  CStdString m_server;
  CStdString m_path;
  CStdString m_username;
  CStdString m_password;
  CStdString m_port;

  bool m_confirmed;
};
