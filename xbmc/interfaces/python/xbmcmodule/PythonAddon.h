#pragma once



#include <Python.h>

#include "addons/IAddon.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace PYXBMC
{
  typedef struct {
    PyObject_HEAD
    ADDON::AddonPtr pAddon;
  } Addon;

  extern PyTypeObject Addon_Type;
  void initAddon_Type();
}

#ifdef __cplusplus
}
#endif
