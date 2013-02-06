#pragma once


#include "utils/StdString.h"
#include "ThumbLoader.h"

class CPictureThumbLoader : public CThumbLoader, public CJobQueue
{
public:
  CPictureThumbLoader();
  virtual ~CPictureThumbLoader();
  virtual bool LoadItem(CFileItem* pItem);
  void SetRegenerateThumbs(bool regenerate) { m_regenerateThumbs = regenerate; };
  static void ProcessFoldersAndArchives(CFileItem *pItem);

  /*!
   \brief Callback from CThumbExtractor on completion of a generated image

   Performs the callbacks and updates the GUI.

   \sa CImageLoader, IJobCallback
   */
  virtual void OnJobComplete(unsigned int jobID, bool success, CJob *job);
protected:
  virtual void OnLoaderFinish();
private:
  bool m_regenerateThumbs;
};
