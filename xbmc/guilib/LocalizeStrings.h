/*!
\file LocalizeStrings.h
\brief
*/

#ifndef GUILIB_LOCALIZESTRINGS_H
#define GUILIB_LOCALIZESTRINGS_H

#pragma once



#include "utils/StdString.h"

#include <map>

/*!
 \ingroup strings
 \brief
 */
class CLocalizeStrings
{
public:
  CLocalizeStrings(void);
  virtual ~CLocalizeStrings(void);
  bool Load(const CStdString& strFileName, const CStdString& strFallbackFileName="special://root/language/english/strings.xml");
  bool LoadSkinStrings(const CStdString& path, const CStdString& fallbackPath);
  void ClearSkinStrings();
  const CStdString& Get(uint32_t code) const;
  void Clear();
  uint32_t LoadBlock(const CStdString &id, const CStdString &path, const CStdString &fallbackPath);
  void ClearBlock(const CStdString &id);
protected:
  void Clear(uint32_t start, uint32_t end);
  bool LoadXML(const CStdString &filename, CStdString &encoding, uint32_t offset = 0);
  CStdString ToUTF8(const CStdString &encoding, const CStdString &str);
  std::map<uint32_t, CStdString> m_strings;
  typedef std::map<uint32_t, CStdString>::const_iterator ciStrings;
  typedef std::map<uint32_t, CStdString>::iterator       iStrings;

  static const uint32_t block_start = 0xf000000;
  static const uint32_t block_size = 4096;
  std::map<CStdString, uint32_t> m_blocks;
  typedef std::map<CStdString, uint32_t>::iterator iBlocks;
};

/*!
 \ingroup strings
 \brief
 */
extern CLocalizeStrings g_localizeStrings;
extern CLocalizeStrings g_localizeStringsTemp;
#endif
