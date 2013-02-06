#pragma once


#include "ImusicInfoTagLoader.h"

namespace MUSIC_INFO
{

class CMusicInfoTagLoaderWMA: public IMusicInfoTagLoader
{
public:
  CMusicInfoTagLoaderWMA(void);
  virtual ~CMusicInfoTagLoaderWMA();

  virtual bool Load(const CStdString& strFileName, CMusicInfoTag& tag);

protected:
  void SetTagValueString(const CStdString& strFrameName, const CStdString& strValue, CMusicInfoTag& tag);
  void SetTagValueUnsigned(const CStdString& strFrameName, uint32_t value, CMusicInfoTag& tag);
  void SetTagValueBinary(const CStdString& strFrameName, const unsigned char *pValue, CMusicInfoTag& tag);
  void SetTagValueBool(const CStdString& strFrameName, bool bValue, CMusicInfoTag& tag);
};
}
