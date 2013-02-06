#pragma once



#include "cores/IPlayer.h"
#include "threads/Thread.h"

class CGUIDialogOK;

class CExternalPlayer : public IPlayer, public CThread
{
public:
  enum WARP_CURSOR { WARP_NONE = 0, WARP_TOP_LEFT, WARP_TOP_RIGHT, WARP_BOTTOM_RIGHT, WARP_BOTTOM_LEFT, WARP_CENTER };

  CExternalPlayer(IPlayerCallback& callback);
  virtual ~CExternalPlayer();
  virtual bool Initialize(TiXmlElement* pConfig);
  virtual void RegisterAudioCallback(IAudioCallback* pCallback) {}
  virtual void UnRegisterAudioCallback()                        {}
  virtual bool OpenFile(const CFileItem& file, const CPlayerOptions &options);
  virtual bool CloseFile();
  virtual bool IsPlaying() const;
  virtual void Pause();
  virtual bool IsPaused() const;
  virtual bool HasVideo() const;
  virtual bool HasAudio() const;
  virtual void ToggleOSD() { }; // empty
  virtual void SwitchToNextLanguage();
  virtual void ToggleSubtitles();
  virtual bool CanSeek();
  virtual void Seek(bool bPlus, bool bLargeStep);
  virtual void SeekPercentage(float iPercent);
  virtual float GetPercentage();
  virtual void SetVolume(long nVolume) {}
  virtual void SetDynamicRangeCompression(long drc) {}
  virtual void SetContrast(bool bPlus) {}
  virtual void SetBrightness(bool bPlus) {}
  virtual void SetHue(bool bPlus) {}
  virtual void SetSaturation(bool bPlus) {}
  virtual void GetAudioInfo(CStdString& strAudioInfo);
  virtual void GetVideoInfo(CStdString& strVideoInfo);
  virtual void GetGeneralInfo( CStdString& strVideoInfo);
  virtual void Update(bool bPauseDrawing)                       {}
  virtual void SwitchToNextAudioLanguage();
  virtual bool CanRecord() { return false; }
  virtual bool IsRecording() { return false; }
  virtual bool Record(bool bOnOff) { return false; }
  virtual void SetAVDelay(float fValue = 0.0f);
  virtual float GetAVDelay();

  virtual void SetSubTitleDelay(float fValue = 0.0f);
  virtual float GetSubTitleDelay();

  virtual void SeekTime(__int64 iTime);
  virtual __int64 GetTime();
  virtual int GetTotalTime();
  virtual void ToFFRW(int iSpeed);
  virtual void ShowOSD(bool bOnoff);
  virtual void DoAudioWork()                                    {}
  
  virtual CStdString GetPlayerState();
  virtual bool SetPlayerState(CStdString state);
  
#if defined(_WIN32)
  virtual BOOL ExecuteAppW32(const char* strPath, const char* strSwitches);
  //static void CALLBACK AppFinished(void* closure, BOOLEAN TimerOrWaitFired);
#elif defined(_LINUX)
  virtual BOOL ExecuteAppLinux(const char* strSwitches);
#endif

private:
  void GetCustomRegexpReplacers(TiXmlElement *pRootElement, CStdStringArray& settings);
  virtual void Process();

  bool m_bAbortRequest;
  bool m_bIsPlaying;
  bool m_paused;
  int64_t m_playbackStartTime;
  int m_speed;
  int m_totalTime;
  int m_time;
  CStdString m_launchFilename;
  HWND m_hwndXbmc; 
#if defined(_WIN32)
  POINT m_ptCursorpos;
  PROCESS_INFORMATION m_processInfo;
#endif 
  CGUIDialogOK* m_dialog;
  int m_xPos;
  int m_yPos;
  CStdString m_filename;
  CStdString m_args;
  bool m_hideconsole;
  bool m_hidexbmc;
  bool m_islauncher;
  bool m_playOneStackItem;
  WARP_CURSOR m_warpcursor;
  int m_playCountMinTime;
  CStdStringArray m_filenameReplacers;
};
