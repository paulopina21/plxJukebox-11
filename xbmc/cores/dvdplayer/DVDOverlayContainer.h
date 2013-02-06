#pragma once



#include "DVDCodecs/Overlay/DVDOverlay.h"
#include "threads/CriticalSection.h"

class CDVDInputStreamNavigator;
class CDVDDemuxSPU;

class CDVDOverlayContainer : public CCriticalSection
{
public:
  CDVDOverlayContainer();
  virtual ~CDVDOverlayContainer();

  void Add(CDVDOverlay* pPicture); // add a overlay to the fifo

  VecOverlays* GetOverlays(); // get the first overlay in this fifo
  bool ContainsOverlayType(DVDOverlayType type);

  void Remove(); // remove the first overlay in this fifo

  void Clear(); // clear the fifo and delete all overlays
  void CleanUp(double pts); // validates all overlays against current pts
  int GetSize();

  void UpdateOverlayInfo(CDVDInputStreamNavigator* pStream, CDVDDemuxSPU *pSpu, int iAction);
private:
  VecOverlaysIter Remove(VecOverlaysIter itOverlay); // removes a specific overlay

  VecOverlays m_overlays;
};
