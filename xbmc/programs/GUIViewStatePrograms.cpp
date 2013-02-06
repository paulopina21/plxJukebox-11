

#include "GUIViewStatePrograms.h"
#include "FileItem.h"
#include "ViewState.h"
#include "settings/GUISettings.h"
#include "settings/Settings.h"
#include "filesystem/Directory.h"
#include "Util.h"
#include "guilib/LocalizeStrings.h"
#include "guilib/Key.h"

using namespace XFILE;
using namespace ADDON;

CGUIViewStateWindowPrograms::CGUIViewStateWindowPrograms(const CFileItemList& items) : CGUIViewState(items)
{
  if (g_guiSettings.GetBool("filelists.ignorethewhensorting"))
    AddSortMethod(SORT_METHOD_LABEL_IGNORE_THE, 551, LABEL_MASKS("%K", "%I", "%L", ""));  // Titel, Size | Foldername, empty
  else
    AddSortMethod(SORT_METHOD_LABEL, 551, LABEL_MASKS("%K", "%I", "%L", ""));  // Titel, Size | Foldername, empty

  SetSortMethod(g_settings.m_viewStatePrograms.m_sortMethod);
  SetViewAsControl(g_settings.m_viewStatePrograms.m_viewMode);
  SetSortOrder(g_settings.m_viewStatePrograms.m_sortOrder);

  LoadViewState(items.GetPath(), WINDOW_PROGRAMS);
}

void CGUIViewStateWindowPrograms::SaveViewState()
{
  SaveViewToDb(m_items.GetPath(), WINDOW_PROGRAMS, &g_settings.m_viewStatePrograms);
}

CStdString CGUIViewStateWindowPrograms::GetLockType()
{
  return "programs";
}

CStdString CGUIViewStateWindowPrograms::GetExtensions()
{
  return ".xbe|.cut";
}

VECSOURCES& CGUIViewStateWindowPrograms::GetSources()
{
  AddAddonsSource("executable", g_localizeStrings.Get(1043), "DefaultAddonProgram.png");
  AddOrReplace(g_settings.m_programSources,CGUIViewState::GetSources());
  return g_settings.m_programSources;
}

