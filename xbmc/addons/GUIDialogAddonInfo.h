#pragma once



#include "guilib/GUIDialog.h"
#include "addons/IAddon.h"
#include "utils/Job.h"

class CGUIDialogAddonInfo :
      public CGUIDialog,
      public IJobCallback
{
public:
  CGUIDialogAddonInfo(void);
  virtual ~CGUIDialogAddonInfo(void);
  bool OnMessage(CGUIMessage& message);
  
  virtual CFileItemPtr GetCurrentListItem(int offset = 0) { return m_item; }
  virtual bool HasListItems() const { return true; }

  static bool ShowForItem(const CFileItemPtr& item);

  // job callback
  void OnJobComplete(unsigned int jobID, bool success, CJob* job);
protected:
  void OnInitWindow();

  /*! \brief Set the item to display addon info on.
   \param item to display
   \return true if we can display information, false otherwise
   */
  bool SetItem(const CFileItemPtr &item);
  void UpdateControls();

  void OnUpdate();
  void OnInstall();
  void OnUninstall();
  void OnEnable(bool enable);
  void OnSettings();
  void OnChangeLog();
  void OnRollback();

  CFileItemPtr m_item;
  ADDON::AddonPtr m_addon;
  ADDON::AddonPtr m_localAddon;
  unsigned int m_jobid;
  bool m_changelog;

  // rollback data
  void GrabRollbackVersions();
  std::vector<CStdString> m_rollbackVersions;
};

