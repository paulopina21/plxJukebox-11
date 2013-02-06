#pragma once




#include <vector>
#include <stdint.h>
#include "utils/StdString.h"
#include "URL.h"

class CEdl
{
public:
  CEdl();
  virtual ~CEdl(void);

  typedef enum
  {
    CUT = 0,
    MUTE = 1,
    // SCENE = 2,
    COMM_BREAK = 3
  } Action;

  struct Cut
  {
    int64_t start; // ms
    int64_t end;   // ms
    Action action;
  };

  bool ReadEditDecisionLists(const CStdString& strMovie, const float fFramesPerSecond, const int iHeight);
  void Clear();

  bool HasCut();
  bool HasSceneMarker();
  CStdString GetInfo();
  int64_t GetTotalCutTime();
  int64_t RemoveCutTime(int64_t iSeek);
  int64_t RestoreCutTime(int64_t iClock);

  bool InCut(int64_t iSeek, Cut *pCut = NULL);

  bool GetNextSceneMarker(bool bPlus, const int64_t iClock, int64_t *iSceneMarker);

  static CStdString GetMPlayerEdl();

  static CStdString MillisecondsToTimeString(const int64_t iMilliseconds);

protected:
private:
  int64_t m_iTotalCutTime; // ms
  std::vector<Cut> m_vecCuts;
  std::vector<int64_t> m_vecSceneMarkers;

  bool ReadEdl(const CStdString& strMovie, const float fFramesPerSecond);
  bool ReadComskip(const CStdString& strMovie, const float fFramesPerSecond);
  bool ReadVideoReDo(const CStdString& strMovie);
  bool ReadBeyondTV(const CStdString& strMovie);
  bool ReadMythCommBreakList(const CStdString& strMovie, const float fFramesPerSecond);
  bool ReadMythCutList(const CStdString& strMovie, const float fFramesPerSecond);

  bool AddCut(Cut& NewCut);
  bool AddSceneMarker(const int64_t sceneMarker);

  bool WriteMPlayerEdl();

  void MergeShortCommBreaks();
};
