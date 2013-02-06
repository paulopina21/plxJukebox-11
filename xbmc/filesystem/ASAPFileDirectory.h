

#pragma once

#include "MusicFileDirectory.h"
#include "DllASAP.h"

namespace XFILE
{
  class CASAPFileDirectory : public CMusicFileDirectory
  {
  public:
    CASAPFileDirectory(void);
    virtual ~CASAPFileDirectory(void);
  private:
    DllASAP m_dll;
    virtual int GetTrackCount(const CStdString& strPath);
  };
}
