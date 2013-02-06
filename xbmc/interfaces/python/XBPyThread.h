

#ifndef XBPYTHREAD_H_
#define XBPYTHREAD_H_

#include "threads/Thread.h"
#include "threads/Event.h"
#include "addons/IAddon.h"

class XBPython;

class XBPyThread : public CThread
{
public:
  XBPyThread(XBPython *pExecuter, int id);
  virtual ~XBPyThread();
  int evalFile(const CStdString &src);
  int evalString(const CStdString &src);
  int setArgv(const std::vector<CStdString> &argv);
  bool isStopping();
  void stop();

  void setAddon(ADDON::AddonPtr _addon) { addon = _addon; }

protected:
  XBPython *m_pExecuter;
  CEvent stoppedEvent;
  void *m_threadState;

  char m_type;
  char *m_source;
  char **m_argv;
  unsigned int  m_argc;
  bool m_stopping;
  int  m_id;
  ADDON::AddonPtr addon;

  void setSource(const CStdString &src);

  virtual void Process();
  virtual void OnExit();
  virtual void OnException();
};

#endif // XBPYTHREAD_H_
