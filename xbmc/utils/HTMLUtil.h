#pragma once



namespace HTML
{
class CHTMLUtil
{
public:
  CHTMLUtil(void);
  virtual ~CHTMLUtil(void);
  int FindTag(const CStdString& strHTML, const CStdString& strTag, CStdString& strtagFound, int iPos = 0) const;
  int FindClosingTag(const CStdString& strHTML, const CStdString& strTag, CStdString& strtagFound, int iPos) const;
  void getValueOfTag(const CStdString& strTagAndValue, CStdString& strValue);
  void getAttributeOfTag(const CStdString& strTagAndValue, const CStdString& strTag, CStdString& strValue);
  static void RemoveTags(CStdString& strHTML);
  static void ConvertHTMLToW(const CStdStringW& strHTML, CStdStringW& strStripped);
};
}
