/*
 * PartyModeManager.h
 *
 *  Created on: Nov 13, 2012
 *      Author: laureon
 */

#ifndef PARTYMODEMANAGER_H_
#define PARTYMODEMANAGER_H_

#include "IModeManager.h"
#include "dialogs/GUIDialogKaiToast.h"

namespace plxJukebox {
class PartyModeManager: public IModeManager {
private:
  int m_iPlaylistSize;
  int m_iPlaylistMaxSize;
  int m_iCurrentPlaylist;
  int m_iQueuesAllowed;
  int m_iQueueWait;

  CGUIDialogKaiToast *m_dialog;
public:
  PartyModeManager();
  virtual ~PartyModeManager();
  void UpdateParams();

  virtual bool Init();

  virtual bool CanQueue();
  virtual void RegisterQueue();
  virtual void ShowMessage();
  virtual CStdString GetModeInfo();
};

} /* namespace plxJukebox */
#endif /* PARTYMODEMANAGER_H_ */
