

#include "GUIColorManager.h"
#include "filesystem/SpecialProtocol.h"
#include "addons/Skin.h"
#include "utils/log.h"
#include "utils/URIUtils.h"
#include "tinyXML/tinyxml.h"

CGUIColorManager g_colorManager;

CGUIColorManager::CGUIColorManager(void)
{
}

CGUIColorManager::~CGUIColorManager(void)
{
  Clear();
}

void CGUIColorManager::Clear()
{
  m_colors.clear();
}

// load the color file in
void CGUIColorManager::Load(const CStdString &colorFile)
{
  Clear();

  // load the global color map if it exists
  TiXmlDocument xmlDoc;
  if (xmlDoc.LoadFile(PTH_IC("special://root/system/colors.xml")))
    LoadXML(xmlDoc);

  // first load the default color map if it exists
  CStdString path, basePath;
  URIUtils::AddFileToFolder(g_SkinInfo->Path(), "colors", basePath);
  URIUtils::AddFileToFolder(basePath, "defaults.xml", path);

  if (xmlDoc.LoadFile(PTH_IC(path)))
    LoadXML(xmlDoc);

  // now the color map requested
  if (colorFile.CompareNoCase("SKINDEFAULT") == 0)
    return; // nothing to do

  URIUtils::AddFileToFolder(basePath, colorFile, path);
  CLog::Log(LOGINFO, "Loading colors from %s", path.c_str());

  if (xmlDoc.LoadFile(path))
    LoadXML(xmlDoc);
}

bool CGUIColorManager::LoadXML(TiXmlDocument &xmlDoc)
{
  TiXmlElement* pRootElement = xmlDoc.RootElement();

  CStdString strValue = pRootElement->Value();
  if (strValue != CStdString("colors"))
  {
    CLog::Log(LOGERROR, "color file doesnt start with <colors>");
    return false;
  }

  const TiXmlElement *color = pRootElement->FirstChildElement("color");

  while (color)
  {
    if (color->FirstChild() && color->Attribute("name"))
    {
      color_t value = 0xffffffff;
      sscanf(color->FirstChild()->Value(), "%x", (unsigned int*) &value);
      CStdString name = color->Attribute("name");
      iColor it = m_colors.find(name);
      if (it != m_colors.end())
        (*it).second = value;
      else
        m_colors.insert(make_pair(name, value));
    }
    color = color->NextSiblingElement("color");
  }
  return true;
}

// lookup a color and return it's hex value
color_t CGUIColorManager::GetColor(const CStdString &color) const
{
  // look in our color map
  CStdString trimmed(color);
  trimmed.TrimLeft("= ");
  icColor it = m_colors.find(trimmed);
  if (it != m_colors.end())
    return (*it).second;

  // try converting hex directly
  color_t value = 0;
  sscanf(trimmed.c_str(), "%x", &value);
  return value;
}

