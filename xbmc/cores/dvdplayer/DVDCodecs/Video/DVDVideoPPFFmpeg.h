#pragma once



#include "DVDVideoCodec.h"
#include "DllPostProc.h"

class CDVDVideoPPFFmpeg
{
public:

  CDVDVideoPPFFmpeg(const CStdString& mType);
  ~CDVDVideoPPFFmpeg();


  void SetType(const CStdString& mType, bool deinterlace);
  void SetTarget(DVDVideoPicture *pPicture){ m_pTarget = pPicture; };
  bool Process   (DVDVideoPicture *pPicture);
  bool GetPicture(DVDVideoPicture *pPicture);

protected:
  CStdString m_sType;

  void *m_pContext;
  void *m_pMode;
  bool m_deinterlace;

  DVDVideoPicture m_FrameBuffer;
  DVDVideoPicture *m_pSource;
  DVDVideoPicture *m_pTarget;

  void Dispose();

  int m_iInitWidth, m_iInitHeight;
  bool CheckInit(int iWidth, int iHeight);
  bool CheckFrameBuffer(const DVDVideoPicture* pSource);

  DllPostProc m_dll;
};


