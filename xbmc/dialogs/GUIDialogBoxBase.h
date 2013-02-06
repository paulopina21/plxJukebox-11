#pragma once



#include "guilib/GUIDialog.h"
#include "utils/Variant.h"

class CGUIDialogBoxBase :
      public CGUIDialog
{
public:
  CGUIDialogBoxBase(int id, const CStdString &xmlFile);
  virtual ~CGUIDialogBoxBase(void);
  virtual bool OnMessage(CGUIMessage& message);
  bool IsConfirmed() const;
  void SetLine(int iLine, const CVariant &line);
  void SetHeading(const CVariant &heading);
  void SetChoice(int iButton, const CVariant &choice);
protected:
  /*! \brief Get a localized string from a variant
   If the varaint is already a string we return directly, else if it's an integer we return the corresponding
   localized string.
   \param var the variant to localize.
   */
  CStdString GetLocalized(const CVariant &var) const;

  virtual void OnInitWindow();
  bool m_bConfirmed;
};
