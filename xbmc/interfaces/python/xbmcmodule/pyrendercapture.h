

#pragma once

#include <Python.h>
#include "cores/VideoRenderers/RenderCapture.h"

//PyByteArray_FromStringAndSize is only available in python 2.6 and up
#if PY_VERSION_HEX >= 0x02060000 

#define HAS_PYRENDERCAPTURE

#ifdef __cplusplus
extern "C" {
#endif

namespace PYXBMC
{
  typedef struct {
    PyObject_HEAD
    CRenderCapture* capture;
  } RenderCapture;

  extern PyTypeObject RenderCapture_Type;
  void initRenderCapture_Type();
}

#ifdef __cplusplus
}
#endif

#endif //PY_VERSION_HEX >= 0x02060000

