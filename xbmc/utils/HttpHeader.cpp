

#include "HttpHeader.h"

CHttpHeader::CHttpHeader()
{
  m_params.clear();
}

CHttpHeader::~CHttpHeader()
{
}

void CHttpHeader::Parse(CStdString strData)
{
  unsigned int iIter = 0;
  int iValueStart = 0;
  int iValueEnd = 0;

  CStdString strParam;
  CStdString strValue;

  while (iIter < strData.size())
  {
    iValueStart = strData.Find(":", iIter);
    iValueEnd = strData.Find("\r\n", iIter);

    if (iValueEnd < 0) break;

    if (iValueStart > 0)
    {
      strParam = strData.substr(iIter, iValueStart);
      strValue = strData.substr(iValueStart + 1, iValueEnd - iValueStart - 1);

      /*
      CUtil::Lower(strParam.c_str()
      // trim left and right
      {
        string::size_type pos = strValue.find_last_not_of(' ');
        if(pos != string::npos)
        {
          strValue.erase(pos + 1);
          pos = strValue.find_first_not_of(' ');
          if(pos != string::npos) strValue.erase(0, pos);
        }
        else strValue.erase(strValue.begin(), strValue.end());
      }*/
      strParam.Trim();
      strParam.ToLower();

      strValue.Trim();


      m_params[strParam] = strValue;
    }
    else if (m_protoLine.IsEmpty())
      m_protoLine = strData;


    iIter = iValueEnd + 2;
  }
}

CStdString CHttpHeader::GetValue(CStdString strParam) const
{
  strParam.ToLower();

  std::map<CStdString,CStdString>::const_iterator pIter = m_params.find(strParam);
  if (pIter != m_params.end()) return pIter->second;

  return "";
}

void CHttpHeader::GetHeader(CStdString& strHeader) const
{
  strHeader.clear();

  std::map<CStdString,CStdString>::const_iterator iter = m_params.begin();
  while (iter != m_params.end())
  {
    strHeader += ((*iter).first + ": " + (*iter).second + "\n");
    iter++;
  }

  strHeader += "\n";
}

void CHttpHeader::Clear()
{
  m_params.clear();
}
