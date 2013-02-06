#pragma once


#ifndef __SCREENSAVER_TYPES_H__
#define __SCREENSAVER_TYPES_H__

extern "C"
{
  struct SCR_INFO
  {
    int dummy;
  };

  struct SCR_PROPS
  {
    void *device;
    int x;
    int y;
    int width;
    int height;
    float pixelRatio;
    const char *name;
    const char *presets;
    const char *profile;
  };

  struct ScreenSaver
  {
    void (__cdecl* Start) ();
    void (__cdecl* Render) ();
    void (__cdecl* GetInfo)(SCR_INFO *info);
  };
}

#endif // __SCREENSAVER_TYPES_H__
