/*!
\file GUIColorManager.h
\brief
*/

#ifndef GUILIB_COLORMANAGER_H
#define GUILIB_COLORMANAGER_H

#pragma once



/*!
 \ingroup textures
 \brief
 */

#include "utils/StdString.h"

#include <map>

class TiXmlDocument;

typedef uint32_t color_t;

class CGUIColorManager
{
public:
  CGUIColorManager(void);
  virtual ~CGUIColorManager(void);

  void Load(const CStdString &colorFile);

  color_t GetColor(const CStdString &color) const;

  void Clear();

protected:
  bool LoadXML(TiXmlDocument &xmlDoc);

  std::map<CStdString, color_t> m_colors;
  typedef std::map<CStdString, color_t>::iterator iColor;
  typedef std::map<CStdString, color_t>::const_iterator icColor;
};

/*!
 \ingroup textures
 \brief
 */
extern CGUIColorManager g_colorManager;
#endif
