/*
 * CoinsManager.h
 *
 *  Created on: Nov 7, 2012
 *      Author: laureon
 */

#ifndef COINSMANAGER_H_
#define COINSMANAGER_H_

#include "IModeManager.h"
#include "ProfessionalDatabase.h"
#include "dialogs/GUIDialogKaiToast.h"


class CoinsManager: public IModeManager {
private:
  CProfessionalDatabase m_dbProfessional;
  int64_t m_coins;
  int64_t m_iErasesAvaiable;

  CGUIDialogKaiToast *m_dialog;

public:
  CoinsManager();
  virtual ~CoinsManager();

  virtual bool Init();

  int64_t InsertCoin(int64_t Amount = 1);
  int64_t RemoveCoin(int64_t Amount = 1);
  int64_t EraseSong(int64_t Amount = 1);
  void RemoveLastSong();

  int64_t GetCoins();
  bool HasCoins();

  virtual bool CanQueue();
  virtual void RegisterQueue();
  virtual void ShowMessage();
  virtual CStdString GetModeInfo();
};

#endif /* COINSMANAGER_H_ */
