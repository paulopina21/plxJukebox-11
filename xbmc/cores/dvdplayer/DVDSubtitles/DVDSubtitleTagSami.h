#pragma once


#include <stdio.h>
#include "utils/StdString.h"

#define FLAG_BOLD   0
#define FLAG_ITALIC 1
#define FLAG_COLOR  2
#define FLAG_LANGUAGE   3

class CDVDOverlayText;
class CDVDSubtitleStream;
class CRegExp;

class CDVDSubtitleTagSami
{
public:
  CDVDSubtitleTagSami()
  {
    m_tags = NULL;
    m_tagOptions = NULL;
    m_flag[FLAG_BOLD] = false;
    m_flag[FLAG_ITALIC] = false;
    m_flag[FLAG_COLOR] = false;
    m_flag[FLAG_LANGUAGE] = false; //set to true when classID != lang
  }
  virtual ~CDVDSubtitleTagSami();
  bool Init();
  void ConvertLine(CDVDOverlayText* pOverlay, const char* line, int len, const char* lang = NULL);
  void CloseTag(CDVDOverlayText* pOverlay);
  void LoadHead(CDVDSubtitleStream* samiStream);

  typedef struct
  {
    CStdString ID;
    CStdString Name;
    CStdString Lang;
    CStdString SAMIType;
  } SLangclass;

  std::vector<SLangclass> m_Langclass;

private:
  CRegExp *m_tags;
  CRegExp *m_tagOptions;
  bool m_flag[4];
};

