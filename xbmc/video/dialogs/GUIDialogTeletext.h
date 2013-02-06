#pragma once


#include "guilib/GUIDialog.h"
#include "video/Teletext.h"

class CBaseTexture;

class CGUIDialogTeletext : public CGUIDialog
{
public:
  CGUIDialogTeletext(void);
  virtual ~CGUIDialogTeletext(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction& action);
  virtual bool OnBack(int actionID);
  virtual void Render();
  virtual void OnInitWindow();
  virtual void OnDeinitWindow(int nextWindowID);

protected:
  bool                m_bClose;           /* Close sendet, needed for fade out */
  CBaseTexture*       m_pTxtTexture;      /* Texture info class to render to screen */
  CRect               m_vertCoords;       /* Coordinates of teletext field on screen */
  CTeletextDecoder    m_TextDecoder;      /* Decoding class for teletext code */
};
