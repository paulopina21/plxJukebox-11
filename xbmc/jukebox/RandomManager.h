/*
 * RandomManager.h
 *
 *  Created on: Nov 5, 2012
 *      Author: laureon
 */

#ifndef RANDOMMANAGER_H_
#define RANDOMMANAGER_H_

#include "utils/Stopwatch.h"
#include "threads/Thread.h"
#include "utils/StdString.h"
#include <vector>

class RandomManager: CThread
{
private:
  CStopWatch    m_StopWatch;
  unsigned int   m_StopWatchMaxTime;
  std::vector <int> m_history;
  bool bActive;

  void AddToHistory(int songID);
  CStdString GetWhereClauseWithHistory() const;

  bool ItsTime();
protected:
  virtual void Process();
  //void UpdateConfig();

public:
  RandomManager();
  virtual ~RandomManager();

  void SetActionTime(int iTime);
  void DoWork();
  void Reset();
  void Stop();
  void Start();
};

#endif /* RANDOMMANAGER_H_ */
