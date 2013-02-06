#pragma once



#include "settings/GUIWindowTestPattern.h"

class CGUIWindowTestPatternGL : public CGUIWindowTestPattern
{
public:
  CGUIWindowTestPatternGL(void);
  virtual ~CGUIWindowTestPatternGL(void);

private:
  virtual void DrawVerticalLines(int top, int left, int bottom, int right);
  virtual void DrawHorizontalLines(int top, int left, int bottom, int right);
  virtual void DrawCheckers(int top, int left, int bottom, int right);
  virtual void DrawBouncingRectangle(int top, int left, int bottom, int right);
  virtual void DrawContrastBrightnessPattern(int top, int left, int bottom, int right);
  virtual void DrawCircle(int originX, int originY, int radius);
  virtual void BeginRender();
  virtual void EndRender();  
};

