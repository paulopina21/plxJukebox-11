
#pragma once

#include "utils/StdString.h"

class CFileItem;
class CDVDDemux;
class CStreamDetails;
class CDVDInputStream;

class CDVDFileInfo
{
public:
  // Extract a thumbnail immage from the media at strPath an image file in strTarget, optionally populating a streamdetails class with the data
  static bool ExtractThumb(const CStdString &strPath, const CStdString &strTarget, CStreamDetails *pStreamDetails);

  // Probe the files streams and store the info in the VideoInfoTag
  static bool GetFileStreamDetails(CFileItem *pItem);
  static bool DemuxerToStreamDetails(CDVDInputStream* pInputStream, CDVDDemux *pDemux, CStreamDetails &details, const CStdString &path = "");

  static bool GetFileDuration(const CStdString &path, int &duration);
};
