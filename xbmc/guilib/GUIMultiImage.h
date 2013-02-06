/*!
\file GUIMultiImage.h
\brief
*/

#ifndef GUILIB_GUIMULTIIMAGECONTROL_H
#define GUILIB_GUIMULTIIMAGECONTROL_H

#pragma once



#include "GUIImage.h"
#include "utils/Stopwatch.h"

/*!
 \ingroup controls
 \brief
 */
class CGUIMultiImage : public CGUIControl
{
public:
  CGUIMultiImage(int parentID, int controlID, float posX, float posY, float width, float height, const CTextureInfo& texture, unsigned int timePerImage, unsigned int fadeTime, bool randomized, bool loop, unsigned int timeToPauseAtEnd);
  CGUIMultiImage(const CGUIMultiImage &from);
  virtual ~CGUIMultiImage(void);
  virtual CGUIMultiImage *Clone() const { return new CGUIMultiImage(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual void UpdateVisibility(const CGUIListItem *item = NULL);
  virtual void UpdateInfo(const CGUIListItem *item = NULL);
  virtual bool OnAction(const CAction &action);
  virtual bool OnMessage(CGUIMessage &message);
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual bool IsDynamicallyAllocated() { return m_bDynamicResourceAlloc; };
  virtual void SetInvalid();
  virtual bool CanFocus() const;
  virtual CStdString GetDescription() const;

  void SetInfo(const CGUIInfoLabel &info);
  void SetAspectRatio(const CAspectRatio &ratio);

protected:
  void LoadDirectory();

  CGUIInfoLabel m_texturePath;
  CStdString m_currentPath;
  unsigned int m_currentImage;
  CStopWatch m_imageTimer;
  unsigned int m_timePerImage;
  unsigned int m_timeToPauseAtEnd;
  bool m_randomized;
  bool m_loop;

  bool m_bDynamicResourceAlloc;
  bool m_directoryLoaded;
  std::vector<CStdString> m_files;

  CGUIImage m_image;
};
#endif
