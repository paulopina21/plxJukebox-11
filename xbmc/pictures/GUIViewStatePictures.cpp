

#include "GUIViewStatePictures.h"
#include "FileItem.h"
#include "ViewState.h"
#include "settings/GUISettings.h"
#include "settings/AdvancedSettings.h"
#include "settings/Settings.h"
#include "filesystem/Directory.h"
#include "filesystem/PluginDirectory.h"
#include "Util.h"
#include "guilib/LocalizeStrings.h"
#include "guilib/Key.h"

using namespace XFILE;
using namespace ADDON;

CGUIViewStateWindowPictures::CGUIViewStateWindowPictures(const CFileItemList& items) : CGUIViewState(items)
{
  if (items.IsVirtualDirectoryRoot())
  {
    AddSortMethod(SORT_METHOD_LABEL, 551, LABEL_MASKS());
    AddSortMethod(SORT_METHOD_DRIVE_TYPE, 564, LABEL_MASKS());
    SetSortMethod(SORT_METHOD_LABEL);

    SetViewAsControl(DEFAULT_VIEW_LIST);

    SetSortOrder(SORT_ORDER_ASC);
  }
  else
  {
    AddSortMethod(SORT_METHOD_LABEL, 551, LABEL_MASKS("%L", "%I", "%L", ""));  // Filename, Size | Foldername, empty
    AddSortMethod(SORT_METHOD_SIZE, 553, LABEL_MASKS("%L", "%I", "%L", "%I"));  // Filename, Size | Foldername, Size
    AddSortMethod(SORT_METHOD_DATE, 552, LABEL_MASKS("%L", "%J", "%L", "%J"));  // Filename, Date | Foldername, Date
    AddSortMethod(SORT_METHOD_FILE, 561, LABEL_MASKS("%L", "%I", "%L", ""));  // Filename, Size | FolderName, empty

    SetSortMethod(g_settings.m_viewStatePictures.m_sortMethod);
    SetViewAsControl(g_settings.m_viewStatePictures.m_viewMode);
    SetSortOrder(g_settings.m_viewStatePictures.m_sortOrder);
  }
  LoadViewState(items.GetPath(), WINDOW_PICTURES);
}

void CGUIViewStateWindowPictures::SaveViewState()
{
  SaveViewToDb(m_items.GetPath(), WINDOW_PICTURES, &g_settings.m_viewStatePictures);
}

CStdString CGUIViewStateWindowPictures::GetLockType()
{
  return "pictures";
}

CStdString CGUIViewStateWindowPictures::GetExtensions()
{
  if (g_guiSettings.GetBool("pictures.showvideos"))
    return g_settings.m_pictureExtensions+"|"+g_settings.m_videoExtensions;

  return g_settings.m_pictureExtensions;
}

VECSOURCES& CGUIViewStateWindowPictures::GetSources()
{
  AddAddonsSource("image", g_localizeStrings.Get(1039), "DefaultAddonPicture.png");
  AddOrReplace(g_settings.m_pictureSources, CGUIViewState::GetSources());
  return g_settings.m_pictureSources;
}

