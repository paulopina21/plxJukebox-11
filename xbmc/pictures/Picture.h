#pragma once

#include "utils/StdString.h"
#include "utils/Job.h"

class CPicture
{
public:
  static bool CreateThumbnailFromMemory(const unsigned char* buffer, int bufSize, const CStdString& extension, const CStdString& thumbFile);
  static bool CreateThumbnailFromSurface(const unsigned char* buffer, int width, int height, int stride, const CStdString &thumbFile);
  static int ConvertFile(const CStdString& srcFile, const CStdString& destFile, float rotateDegrees, int width, int height, unsigned int quality, bool mirror=false);

  static void CreateFolderThumb(const CStdString *thumbs, const CStdString &folderThumb);
  static bool CreateThumbnail(const CStdString& file, const CStdString& thumbFile, bool checkExistence = false);
  static bool CacheThumb(const CStdString& sourceUrl, const CStdString& destFile);
  static bool CacheFanart(const CStdString& SourceUrl, const CStdString& destFile);

private:
  static bool CacheImage(const CStdString& sourceUrl, const CStdString& destFile, int width, int height);
};

//this class calls CreateThumbnailFromSurface in a CJob, so a png file can be written without halting the render thread
class CThumbnailWriter : public CJob
{
  public:
    //WARNING: buffer is deleted from DoWork()
    CThumbnailWriter(unsigned char* buffer, int width, int height, int stride, const CStdString& thumbFile);
    bool DoWork();

  private:
    unsigned char* m_buffer;
    int            m_width;
    int            m_height;
    int            m_stride;
    CStdString     m_thumbFile;
};

