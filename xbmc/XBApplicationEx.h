

#ifndef XBAPPLICATIONEX_H
#define XBAPPLICATIONEX_H

#include "guilib/IWindowManagerCallback.h"

// Do not change the numbering, external scripts depend on them
enum {
  EXITCODE_QUIT      = 0,
  EXITCODE_POWERDOWN = 64,
  EXITCODE_RESTARTAPP= 65,
  EXITCODE_REBOOT    = 66,
};

class CXBApplicationEx : public IWindowManagerCallback
{
public:
  CXBApplicationEx();
  ~CXBApplicationEx();

  // Variables for timing
  bool m_bStop;
  int  m_ExitCode;
  bool m_AppActive;
  bool m_AppFocused;

  // Overridable functions for the 3D scene created by the app
  virtual bool Initialize() { return true; }
  virtual bool Cleanup() { return true; }

public:
  // Functions to create, run, and clean up the application
  virtual bool Create();
  INT Run();
  VOID Destroy();

private:
};

#endif /* XBAPPLICATIONEX_H */
