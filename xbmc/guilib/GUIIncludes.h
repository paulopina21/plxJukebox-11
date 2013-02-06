#pragma once



#include "utils/StdString.h"

#include <map>
#include <set>

// forward definitions
class TiXmlElement;
namespace INFO
{
  class CSkinVariableString;
}

class CGUIIncludes
{
public:
  CGUIIncludes();
  ~CGUIIncludes();

  void ClearIncludes();
  bool LoadIncludes(const CStdString &includeFile);
  bool LoadIncludesFromXML(const TiXmlElement *root);

  /*! \brief Resolve <include>name</include> tags recursively for the given XML element
   Replaces any instances of <include file="foo">bar</include> with the value of the include
   "bar" from the include file "foo".
   \param node an XML Element - all child elements are traversed.
   */
  void ResolveIncludes(TiXmlElement *node);
  const INFO::CSkinVariableString* CreateSkinVariable(const CStdString& name, int context);

private:
  void ResolveIncludesForNode(TiXmlElement *node);
  CStdString ResolveConstant(const CStdString &constant) const;
  bool HasIncludeFile(const CStdString &includeFile) const;
  std::map<CStdString, TiXmlElement> m_includes;
  std::map<CStdString, TiXmlElement> m_defaults;
  std::map<CStdString, TiXmlElement> m_skinvariables;
  std::map<CStdString, CStdString> m_constants;
  std::vector<CStdString> m_files;
  typedef std::vector<CStdString>::const_iterator iFiles;

  std::set<std::string> m_constantAttributes;
  std::set<std::string> m_constantNodes;
};

