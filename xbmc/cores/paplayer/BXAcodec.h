

#pragma once

#include "ICodec.h"
#include "filesystem/File.h"
#include "CachingCodec.h"
#ifdef _WIN32
#define __attribute__(dummy_val)
#else
#include <config.h>
#endif

#ifdef _WIN32
#pragma pack(push)
#pragma pack(1)
#endif

typedef struct
{
  char fourcc[4];
  uint32_t type;
  uint32_t channels;
  uint32_t sampleRate;
  uint32_t bitsPerSample;
  uint64_t durationMs;
} __attribute__((__packed__)) BXA_FmtHeader;

typedef struct
{
  char fourcc[4];
  uint32_t type;
  uint32_t length;
} __attribute__((__packed__)) BXA_DataHeader;

#ifdef _WIN32
#pragma pack(pop)
#endif

#define BXA_PACKET_TYPE_FMT  1
#define BXA_PACKET_TYPE_DATA 2

class BXACodec : public CachingCodec
{
public:
  BXACodec();
  virtual ~BXACodec();

  virtual bool Init(const CStdString &strFile, unsigned int filecache);
  virtual void DeInit();
  virtual __int64 Seek(__int64 iSeekTime);
  virtual int ReadPCM(BYTE *pBuffer, int size, int *actualsize);
  virtual bool CanInit();
};

