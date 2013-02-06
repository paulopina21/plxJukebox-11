#pragma once



#include "guilib/GUIDialog.h"

namespace ADDON
{
  class CVisualisation;
}
class CFileItemList;

class CGUIDialogVisualisationPresetList :
      public CGUIDialog
{
public:
  CGUIDialogVisualisationPresetList(void);
  virtual ~CGUIDialogVisualisationPresetList(void);
  virtual bool OnMessage(CGUIMessage &message);
  virtual void FrameMove();

protected:
  void SetVisualisation(ADDON::CVisualisation *addon);
  void Update();
  ADDON::CVisualisation* m_viz; //TODO get rid
  CFileItemList* m_vecPresets;
  unsigned m_currentPreset;
};
