#pragma once


#include "GUIRenderingControl.h"

class CGUIVisualisationControl : public CGUIRenderingControl
{
public:
  CGUIVisualisationControl(int parentID, int controlID, float posX, float posY, float width, float height);
  CGUIVisualisationControl(const CGUIVisualisationControl &from);
  virtual CGUIVisualisationControl *Clone() const { return new CGUIVisualisationControl(*this); }; //TODO check for naughties
  virtual void FreeResources(bool immediately = false);
  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual bool OnAction(const CAction &action);
  virtual bool OnMessage(CGUIMessage &message);
private:
  bool m_bAttemptedLoad;
};
