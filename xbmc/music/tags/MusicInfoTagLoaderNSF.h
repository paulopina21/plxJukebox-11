#pragma once


#include "ImusicInfoTagLoader.h"
#include "DllNosefart.h"

namespace MUSIC_INFO
{
  class CMusicInfoTagLoaderNSF: public IMusicInfoTagLoader
  {
    public:
      CMusicInfoTagLoaderNSF(void);
      virtual ~CMusicInfoTagLoaderNSF();

      virtual bool Load(const CStdString& strFileName, CMusicInfoTag& tag);
      virtual int GetStreamCount(const CStdString& strFileName);
    private:
      void* m_nsf;
      DllNosefart m_dll;
  };
}

extern CStdString strNSFDLL;
