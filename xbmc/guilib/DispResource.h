

#pragma once

#if defined(HAS_GLX) || defined(TARGET_DARWIN_OSX)
class IDispResource
{
public:
  virtual ~IDispResource() {};
  virtual void OnLostDevice() {};
  virtual void OnResetDevice() {};
};

#endif
