#pragma once



#include "ICodec.h"
#include "DllModplug.h"

class ModplugCodec : public ICodec
{
public:
  ModplugCodec();
  virtual ~ModplugCodec();

  virtual bool Init(const CStdString &strFile, unsigned int filecache);
  virtual void DeInit();
  virtual __int64 Seek(__int64 iSeekTime);
  virtual int ReadPCM(BYTE *pBuffer, int size, int *actualsize);
  virtual bool CanInit();
private:
  ModPlugFile *m_module;
  DllModplug m_dll;
};
