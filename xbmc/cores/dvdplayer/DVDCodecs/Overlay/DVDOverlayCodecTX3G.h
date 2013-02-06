#pragma once



#include "DVDOverlayCodec.h"

class CDVDOverlayText;

class CDVDOverlayCodecTX3G : public CDVDOverlayCodec
{
public:
  CDVDOverlayCodecTX3G();
  virtual ~CDVDOverlayCodecTX3G();
  virtual bool Open(CDVDStreamInfo &hints, CDVDCodecOptions &options);
  virtual void Dispose();
  virtual int Decode(BYTE* data, int size, double pts, double duration);
  virtual void Reset();
  virtual void Flush();
  virtual CDVDOverlay* GetOverlay();

private:
  CDVDOverlayText* m_pOverlay;
  uint32_t         m_textColor;
};
