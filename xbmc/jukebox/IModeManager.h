/*
 * IModeManager.h
 *
 *  Created on: Nov 13, 2012
 *      Author: laureon
 */

#ifndef IMODEMANAGER_H_
#define IMODEMANAGER_H_

#include "utils/StdString.h"

class IModeManager
{
public:
  IModeManager() { };
  virtual ~IModeManager() { };
  virtual bool Init() = 0;

  virtual bool CanQueue() = 0;
  virtual void RegisterQueue() = 0;

  virtual void ShowMessage() = 0;
  virtual CStdString GetModeInfo() = 0;
};


#endif /* IMODEMANAGER_H_ */
