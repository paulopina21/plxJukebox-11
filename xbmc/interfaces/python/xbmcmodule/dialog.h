

#include <Python.h>

#include "window.h"
#pragma once


class CGUIDialogProgress;

#ifdef __cplusplus
extern "C" {
#endif

namespace PYXBMC
{
  typedef struct {
    PyObject_HEAD
  } Dialog;

  typedef struct {
    PyObject_HEAD_XBMC_WINDOW
  } WindowDialog;

  struct DialogProgress {
    PyObject_HEAD
    CGUIDialogProgress* dlg;

    DialogProgress()
    {
      dlg = 0;
    }
  };

  extern PyTypeObject WindowDialog_Type;
  extern PyTypeObject DialogProgress_Type;
  extern PyTypeObject Dialog_Type;

  void initWindowDialog_Type();
  void initDialogProgress_Type();
  void initDialog_Type();
}

#ifdef __cplusplus
}
#endif
