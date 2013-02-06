#pragma once



#include "windows/GUIMediaWindow.h"
#include "ProgramDatabase.h"
#include "dialogs/GUIDialogProgress.h"
#include "ThumbLoader.h"

class CGUIWindowPrograms :
      public CGUIMediaWindow, public IBackgroundLoaderObserver
{
public:
  CGUIWindowPrograms(void);
  virtual ~CGUIWindowPrograms(void);
  virtual bool OnMessage(CGUIMessage& message);
protected:
  virtual void OnItemLoaded(CFileItem* pItem) {};
  virtual bool Update(const CStdString& strDirectory);
  virtual bool OnPlayMedia(int iItem);
  virtual bool GetDirectory(const CStdString &strDirectory, CFileItemList &items);
  virtual void GetContextButtons(int itemNumber, CContextButtons &buttons);
  virtual bool OnContextButton(int itemNumber, CONTEXT_BUTTON button);
  virtual CStdString GetStartFolder(const CStdString &dir);

  int GetRegion(int iItem, bool bReload=false);

  CGUIDialogProgress* m_dlgProgress;

  CProgramDatabase m_database;

  int m_iRegionSet; // for cd stuff

  CProgramThumbLoader m_thumbLoader;
};
