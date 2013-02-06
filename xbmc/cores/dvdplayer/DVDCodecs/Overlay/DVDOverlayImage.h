#pragma once



#include "DVDOverlay.h"

class CDVDOverlayImage : public CDVDOverlay
{
public:
  CDVDOverlayImage() : CDVDOverlay(DVDOVERLAY_TYPE_IMAGE)
  {
    data = NULL;
    palette = NULL;
    palette_colors = 0;
    linesize = 0;
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    source_width  = 0;
    source_height = 0;
  }

  ~CDVDOverlayImage()
  {
    if(data) free(data);
    if(palette) free(palette);
  }

  BYTE*  data;
  int    linesize;

  uint32_t* palette;
  int    palette_colors;

  int    x;
  int    y;
  int    width;
  int    height;
  int    source_width;
  int    source_height;
};
