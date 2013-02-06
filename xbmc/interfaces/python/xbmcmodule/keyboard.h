

#include <Python.h>

#include <string>
#pragma once

class CGUIDialogKeyboard;

#ifdef __cplusplus
extern "C" {
#endif

namespace PYXBMC
{
  typedef struct {
    PyObject_HEAD
    std::string strDefault;
    std::string strHeading;
    bool bHidden;
    CGUIDialogKeyboard* dlg;
  } Keyboard;

  extern PyTypeObject Keyboard_Type;
  void initKeyboard_Type();
}

#ifdef __cplusplus
}
#endif
