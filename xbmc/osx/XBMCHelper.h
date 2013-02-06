#ifndef __XBMCHELPER_H__
#define __XBMCHELPER_H__



#if !defined(__arm__)
class XBMCHelper
{
 public:

  static XBMCHelper& GetInstance();

  void Start();
  void Stop();

  void Configure();

  bool IsRunning();

  bool IsAlwaysOn() const { return m_alwaysOn; }
  int  GetMode() const { return m_mode; }

  bool ErrorStarting() { return m_errorStarting; }

  //global helpers
  static void CaptureAllInput();
  static void ReleaseAllInput();

private:
  XBMCHelper();
  XBMCHelper(XBMCHelper const& );
  XBMCHelper& operator=(XBMCHelper const&);

  void Install();
  void Uninstall();

  bool IsRemoteBuddyInstalled();
  bool IsSofaControlRunning();

  int GetProcessPid(const char* processName);

  std::string ReadFile(const char* fileName);
  void WriteFile(const char* fileName, const std::string& data);

  bool m_alwaysOn;
  int  m_mode;
  int  m_sequenceDelay;
  int  m_port;
  bool m_errorStarting;

  std::string m_configFile;
  std::string m_launchAgentLocalFile;
  std::string m_launchAgentInstallFile;
  std::string m_homepath;
  std::string m_helperFile;

  static XBMCHelper* smp_instance;
};

#endif
#endif
