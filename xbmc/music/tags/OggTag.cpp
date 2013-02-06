

#include "OggTag.h"
#include "cores/paplayer/OggCallback.h"
#include "filesystem/File.h"
#include "utils/URIUtils.h"

using namespace MUSIC_INFO;
using namespace XFILE;

COggTag::COggTag()
{

}

COggTag::~COggTag()
{
}

bool COggTag::Read(const CStdString& strFile1)
{
  if (!m_dll.Load())
    return false;

  CVorbisTag::Read(strFile1);

  CStdString strFile=strFile1;
  int currentStream=0;

  m_musicInfoTag.SetURL(strFile);

  CStdString strExtension;
  URIUtils::GetExtension(strFile, strExtension);
  if (strExtension==".oggstream")
  {
    CStdString strFileName=URIUtils::GetFileName(strFile);
    int iStart=strFileName.ReverseFind("-")+1;
    currentStream = atoi(strFileName.substr(iStart, strFileName.size()-iStart-10).c_str())-1;
    CStdString strPath=strFile;
    URIUtils::GetDirectory(strPath, strFile);
    URIUtils::RemoveSlashAtEnd(strFile);   // we want the filename
  }

  CFile file;
  if (!file.Open(strFile))
    return false;

  COggCallback callback(file);
  ov_callbacks oggIOCallbacks = callback.Get(strFile);

  OggVorbis_File vf;
  //  open ogg file with decoder
  if (m_dll.ov_open_callbacks(&callback, &vf, NULL, 0, oggIOCallbacks)!=0)
    return false;

  int iStreams=m_dll.ov_streams(&vf);
  if (iStreams>1)
  {
    if (currentStream > iStreams)
    {
      m_dll.ov_clear(&vf);
      return false;
    }
  }

  m_musicInfoTag.SetDuration((int)m_dll.ov_time_total(&vf, currentStream));

  vorbis_comment* pComments=m_dll.ov_comment(&vf, currentStream);
  if (pComments)
  {
    for (int i=0; i<pComments->comments; ++i)
    {
      CStdString strEntry=pComments->user_comments[i];
      ParseTagEntry(strEntry);
    }
  }
  m_dll.ov_clear(&vf);
  return true;
}

int COggTag::GetStreamCount(const CStdString& strFile)
{
  if (!m_dll.Load())
    return 0;

  CFile file;
  if (!file.Open(strFile))
    return false;

  COggCallback callback(file);
  ov_callbacks oggIOCallbacks = callback.Get(strFile);
  OggVorbis_File vf;
  //  open ogg file with decoder
  if (m_dll.ov_open_callbacks(&callback, &vf, NULL, 0, oggIOCallbacks)!=0)
    return 0;

  int iStreams=m_dll.ov_streams(&vf);

  m_dll.ov_clear(&vf);

  return iStreams;
}

