

#ifndef WINDOWING_FACTORY_H
#define WINDOWING_FACTORY_H

#include "system.h"

#if   defined(TARGET_WINDOWS) && defined(HAS_GL)
#include "windows/WinSystemWin32GL.h"

#elif defined(TARGET_WINDOWS) && defined(HAS_DX)
#include "windows/WinSystemWin32DX.h"

#elif defined(TARGET_LINUX)   && defined(HAS_GL)   && defined(HAVE_X11)
#include "X11/WinSystemX11GL.h"

#elif defined(TARGET_LINUX)   && defined(HAS_GLES) && defined(HAVE_X11)
#include "X11/WinSystemX11GLES.h"

#elif defined(TARGET_LINUX) && defined(HAS_GLES) && defined(HAS_EGL)
#include "egl/WinSystemGLES.h"

#elif defined(TARGET_DARWIN_OSX)
#include "osx/WinSystemOSXGL.h"

#elif defined(TARGET_DARWIN_IOS)
#include "osx/WinSystemIOS.h"

#endif

#endif // WINDOWING_FACTORY_H

