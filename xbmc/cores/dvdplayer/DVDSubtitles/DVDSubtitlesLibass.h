#pragma once



#include "DllLibass.h"
#include "DVDResource.h"
#include "threads/CriticalSection.h"

/** Wrapper for Libass **/

class CDVDSubtitlesLibass : public IDVDResourceCounted<CDVDSubtitlesLibass>
{
public:
  CDVDSubtitlesLibass();
  virtual ~CDVDSubtitlesLibass();

  ASS_Image* RenderImage(int imageWidth, int imageHeight, double pts);
  ASS_Event* GetEvents();

  int GetNrOfEvents();

  bool DecodeHeader(char* data, int size);
  bool DecodeDemuxPkt(char* data, int size, double start, double duration);
  bool CreateTrack(char* buf);

private:
  DllLibass m_dll;
  long m_references;
  ASS_Library* m_library;
  ASS_Track* m_track;
  ASS_Renderer* m_renderer;
  CCriticalSection m_section;
};

