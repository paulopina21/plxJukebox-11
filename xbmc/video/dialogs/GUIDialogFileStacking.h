#pragma once



#include "guilib/GUIDialog.h"

class CFileItemList;

class CGUIDialogFileStacking :
      public CGUIDialog
{
public:
  CGUIDialogFileStacking(void);
  virtual ~CGUIDialogFileStacking(void);
  virtual bool OnMessage(CGUIMessage& message);

  int GetSelectedFile() const;
  void SetNumberOfFiles(int iFiles);
protected:
  int m_iSelectedFile;
  int m_iNumberOfFiles;
  CFileItemList* m_stackItems;
};
