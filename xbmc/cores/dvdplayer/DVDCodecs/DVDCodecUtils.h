#pragma once



#include "Video/DVDVideoCodec.h"

struct YV12Image;

class CDVDCodecUtils
{
public:
  static DVDVideoPicture* AllocatePicture(int iWidth, int iHeight);
  static void FreePicture(DVDVideoPicture* pPicture);
  static bool CopyPicture(DVDVideoPicture* pDst, DVDVideoPicture* pSrc);
  static bool CopyPicture(YV12Image* pDst, DVDVideoPicture *pSrc);
  
  static DVDVideoPicture* ConvertToNV12Picture(DVDVideoPicture *pSrc);
  static DVDVideoPicture* ConvertToYUV422PackedPicture(DVDVideoPicture *pSrc, DVDVideoPicture::EFormat format);
  static bool CopyNV12Picture(YV12Image* pImage, DVDVideoPicture *pSrc);
  static bool CopyYUV422PackedPicture(YV12Image* pImage, DVDVideoPicture *pSrc);
  static bool CopyDXVA2Picture(YV12Image* pImage, DVDVideoPicture *pSrc);

  static bool IsVP3CompatibleWidth(int width);

  static double NormalizeFrameduration(double frameduration);
};

