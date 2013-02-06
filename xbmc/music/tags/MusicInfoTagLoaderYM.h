#pragma once


#include "ImusicInfoTagLoader.h"
#include "DllStSound.h"

namespace MUSIC_INFO
{
  class CMusicInfoTagLoaderYM: public IMusicInfoTagLoader
  {
    public:
      CMusicInfoTagLoaderYM(void);
      virtual ~CMusicInfoTagLoaderYM();

      virtual bool Load(const CStdString& strFileName, CMusicInfoTag& tag);
    private:
      void* m_ym;
      DllStSound m_dll;
  };
}

