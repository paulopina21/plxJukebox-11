#ifndef _ENCODERFLAC_H
#define _ENCODERFLAC_H



#include "Encoder.h"
#include "DllFlacEnc.h"

class CEncoderFlac : public CEncoder
{
public:
  CEncoderFlac();
  virtual ~CEncoderFlac();
  bool Init(const char* strFile, int iInChannels, int iInRate, int iInBits);
  int Encode(int nNumBytesRead, uint8_t* pbtStream);
  bool Close();

private:
  DllFlacEnc m_dll;
  FLAC__StreamEncoder *m_encoder;
  FLAC__StreamMetadata *m_metadata[2];

  static const int SAMPLES_BUF_SIZE = 1024 * 2;
  FLAC__int32 *m_samplesBuf;

  static FLAC__StreamEncoderWriteStatus write_callback(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t bytes, unsigned samples, unsigned current_frame, void *client_data);
};

#endif // _ENCODERFLAC_H
