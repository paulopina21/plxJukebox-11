#pragma once


#include <stdio.h>

#define FLAG_BOLD   0
#define FLAG_ITALIC 1
#define FLAG_COLOR  2

#define TAG_ONE_LINE 1
#define TAG_ALL_LINE 2

class CDVDOverlayText;

class CDVDSubtitleTagMicroDVD
{
public:
  void ConvertLine(CDVDOverlayText* pOverlay, const char* line, int len);

private:
  int m_flag[3];
};

