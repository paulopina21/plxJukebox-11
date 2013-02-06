

#include "GUIViewStateAddonBrowser.h"
#include "FileItem.h"
#include "guilib/Key.h"
#include "ViewState.h"
#include "settings/Settings.h"
#include "addons/Addon.h"
#include "addons/AddonManager.h"
#include "AddonDatabase.h"

using namespace XFILE;
using namespace ADDON;

CGUIViewStateAddonBrowser::CGUIViewStateAddonBrowser(const CFileItemList& items) : CGUIViewState(items)
{
  AddSortMethod(SORT_METHOD_LABEL_IGNORE_FOLDERS, 551, LABEL_MASKS("%L", "%I", "%L", ""));  // Filename, Size | Foldername, empty
  AddSortMethod(SORT_METHOD_DATE, 552, LABEL_MASKS("%L", "%J", "%L", "%J"));  // Filename, Date | Foldername, Date
  SetSortMethod(SORT_METHOD_LABEL_IGNORE_FOLDERS);

  SetViewAsControl(DEFAULT_VIEW_AUTO);

  SetSortOrder(SORT_ORDER_ASC);
  LoadViewState(items.GetPath(), WINDOW_ADDON_BROWSER);
}

void CGUIViewStateAddonBrowser::SaveViewState()
{
  SaveViewToDb(m_items.GetPath(), WINDOW_ADDON_BROWSER);
}

CStdString CGUIViewStateAddonBrowser::GetExtensions()
{
  return "";
}

VECSOURCES& CGUIViewStateAddonBrowser::GetSources()
{
  m_sources.clear();

  // we always have some enabled addons
  {
    CMediaSource share;
    share.strPath = "addons://enabled/";
    share.m_iDriveType = CMediaSource::SOURCE_TYPE_LOCAL;
    share.strName = g_localizeStrings.Get(24062);
    m_sources.push_back(share);
  }
  CAddonDatabase db;
  if (db.Open() && db.HasDisabledAddons())
  {
    CMediaSource share;
    share.strPath = "addons://disabled/";
    share.m_iDriveType = CMediaSource::SOURCE_TYPE_LOCAL;
    share.strName = g_localizeStrings.Get(24039);
    m_sources.push_back(share);
  }
  if (CAddonMgr::Get().HasOutdatedAddons())
  {
    CMediaSource share;
    share.strPath = "addons://outdated/";
    share.m_iDriveType = CMediaSource::SOURCE_TYPE_LOCAL;
    share.strName = g_localizeStrings.Get(24043);
    m_sources.push_back(share);
  }
  if (CAddonMgr::Get().HasAddons(ADDON_REPOSITORY,true))
  {
    CMediaSource share;
    share.strPath = "addons://repos/";
    share.m_iDriveType = CMediaSource::SOURCE_TYPE_LOCAL;
    share.strName = g_localizeStrings.Get(24033);
    m_sources.push_back(share);
  }
  // add "install from zip"
  {
    CMediaSource share;
    share.strPath = "addons://install/";
    share.m_iDriveType = CMediaSource::SOURCE_TYPE_LOCAL;
    share.strName = g_localizeStrings.Get(24041);
    m_sources.push_back(share);
  }
  // add "search"
  {
    CMediaSource share;
    share.strPath = "addons://search/";
    share.m_iDriveType = CMediaSource::SOURCE_TYPE_LOCAL;
    share.strName = g_localizeStrings.Get(137);
    m_sources.push_back(share);
  }

  return CGUIViewState::GetSources();
}

