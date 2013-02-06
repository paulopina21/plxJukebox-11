#pragma once



#include "guilib/GUIWindow.h"

#define TEST_PATTERNS_COUNT 5
#define TEST_PATTERNS_BOUNCE_SQUARE_SIZE 100
#define TEST_PATTERNS_BLINK_CYCLE 100

class CGUIWindowTestPattern : public CGUIWindow
{
public:
  CGUIWindowTestPattern(void);
  virtual ~CGUIWindowTestPattern(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void Render();
  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);

protected:
  virtual void DrawVerticalLines(int top, int left, int bottom, int right) = 0;
  virtual void DrawHorizontalLines(int top, int left, int bottom, int right) = 0;
  virtual void DrawCheckers(int top, int left, int bottom, int right) = 0;
  virtual void DrawBouncingRectangle(int top, int left, int bottom, int right) = 0;
  virtual void DrawContrastBrightnessPattern(int top, int left, int bottom, int right) = 0;
  virtual void DrawCircle(int originX, int originY, int radius) = 0;
  virtual void BeginRender() = 0;
  virtual void EndRender() = 0;

  int m_pattern;
  int m_bounceX;
  int m_bounceY;
  int m_bounceDirectionX;
  int m_bounceDirectionY;
  int m_blinkFrame;
};


