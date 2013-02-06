#ifndef _ENCODERWAV_H
#define _ENCODERWAV_H



#include "Encoder.h"
#include <stdio.h>

typedef struct
{
  uint8_t riff[4];         /* must be "RIFF"    */
  uint32_t len;             /* #bytes + 44 - 8   */
  uint8_t cWavFmt[8];      /* must be "WAVEfmt " */
  uint32_t dwHdrLen;
  uint16_t wFormat;
  uint16_t wNumChannels;
  uint32_t dwSampleRate;
  uint32_t dwBytesPerSec;
  uint16_t wBlockAlign;
  uint16_t wBitsPerSample;
  uint8_t cData[4];        /* must be "data"   */
  uint32_t dwDataLen;       /* #bytes           */
}
WAVHDR, *PWAVHDR, *LPWAVHDR;

class CEncoderWav : public CEncoder
{
public:
  CEncoderWav();
  virtual ~CEncoderWav() {}
  bool Init(const char* strFile, int iInChannels, int iInRate, int iInBits);
  int Encode(int nNumBytesRead, uint8_t* pbtStream);
  bool Close();
  void AddTag(int key, const char* value);

private:
  bool WriteWavHeader();

  int m_iBytesWritten;
};

#endif // _ENCODERWAV_H
