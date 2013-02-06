
#pragma once

#include "Addon.h"

namespace ADDON
{

class CPluginSource : public CAddon
{
public:

  enum Content { UNKNOWN, AUDIO, IMAGE, EXECUTABLE, VIDEO };

  CPluginSource(const cp_extension_t *ext);
  CPluginSource(const AddonProps &props);
  virtual ~CPluginSource() {}
  virtual bool IsType(TYPE type) const;
  bool Provides(const Content& content) const {
    return content == UNKNOWN ? false : m_providedContent.count(content) > 0; }

  static Content Translate(const CStdString &content);
private:
  /*! \brief Set the provided content for this plugin
   If no valid content types are passed in, we set the EXECUTABLE type
   \param content a space-separated list of content types
   */
  void SetProvides(const CStdString &content);
  std::set<Content> m_providedContent;
};

} /*namespace ADDON*/
