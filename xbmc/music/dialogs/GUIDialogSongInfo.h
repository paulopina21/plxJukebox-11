#pragma once



#include "guilib/GUIDialog.h"

class CFileItem;

class CGUIDialogSongInfo :
      public CGUIDialog
{
public:
  CGUIDialogSongInfo(void);
  virtual ~CGUIDialogSongInfo(void);
  virtual bool OnMessage(CGUIMessage& message);
  void SetSong(CFileItem *item);
  virtual bool OnAction(const CAction &action);
  virtual bool OnBack(int actionID);
  bool NeedsUpdate() const { return m_needsUpdate; };

  virtual bool HasListItems() const { return true; };
  virtual CFileItemPtr GetCurrentListItem(int offset = 0);
protected:
  virtual void OnInitWindow();
  bool DownloadThumbnail(const CStdString &thumbFile);
  void OnGetThumb();
  void SetRating(char rating);

  CFileItemPtr m_song;
  char m_startRating;
  bool m_cancelled;
  bool m_needsUpdate;
  long m_albumId;
};
