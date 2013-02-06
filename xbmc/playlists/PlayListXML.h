#pragma once

#include "PlayList.h"

namespace PLAYLIST
{
class CPlayListXML :
      public CPlayList
{
public:
  CPlayListXML(void);
  virtual ~CPlayListXML(void);
  virtual bool Load(const CStdString& strFileName);
  virtual void Save(const CStdString& strFileName) const;
};
}
