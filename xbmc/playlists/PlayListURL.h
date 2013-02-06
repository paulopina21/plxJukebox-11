#pragma once

#include "PlayList.h"

namespace PLAYLIST
{
class CPlayListURL :
      public CPlayList
{
public:
  CPlayListURL(void);
  virtual ~CPlayListURL(void);
  virtual bool Load(const CStdString& strFileName);
};
}
