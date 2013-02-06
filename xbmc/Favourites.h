#pragma once



#include "utils/StdString.h"

class CFileItemList;
class CFileItem;

class CFavourites
{
public:
  static bool Load(CFileItemList& items);
  static bool LoadFavourites(CStdString& strPath, CFileItemList& items);
  static bool AddOrRemove(CFileItem *item, int contextWindow);
  static bool Save(const CFileItemList& items);
  static bool IsFavourite(CFileItem *item, int contextWindow);

#ifdef UNIT_TESTING
  static bool TestParamify();
#endif

private:
  static CStdString GetExecutePath(const CFileItem *item, int contextWindow);
};
