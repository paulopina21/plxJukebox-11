#pragma once



#include "threads/Thread.h"
#include "filesystem/File.h"

class CAsyncFileCopy : public CThread, public XFILE::IFileCallback
{
public:
  CAsyncFileCopy();
  virtual ~CAsyncFileCopy();

  /// \brief  Main routine to copy files from one source to another.
  /// \return true if successful, and false if it failed or was cancelled.
  bool Copy(const CStdString &from, const CStdString &to, const CStdString &heading);

  /// \brief callback from CFile::Cache()
  virtual bool OnFileCallback(void *pContext, int ipercent, float avgSpeed);

protected:
  virtual void Process();

private:
  /// volatile variables as we access these from both threads
  volatile int m_percent;      ///< current percentage (0..100)
  volatile float m_speed;      ///< current speed (in bytes per second)
  volatile bool m_cancelled;   ///< whether or not we cancelled the operation
  volatile bool m_running;     ///< whether or not the copy operation is still in progress
  
  bool m_succeeded;  ///< whether or not the copy operation was successful
  CStdString m_from; ///< source URL to copy from
  CStdString m_to;   ///< destination URL to copy to
  CEvent m_event;    ///< event to set to force an update
};
