#pragma once



#include "DVDDemux.h"
#include "DllAvFormat.h"
#include "DllAvCodec.h"
#include "DllAvUtil.h"

#include "threads/CriticalSection.h"
#include "threads/SystemClock.h"

class CDVDDemuxFFmpeg;

class CDemuxStreamVideoFFmpeg
  : public CDemuxStreamVideo
{
  CDVDDemuxFFmpeg *m_parent;
  AVStream*        m_stream;
public:
  CDemuxStreamVideoFFmpeg(CDVDDemuxFFmpeg *parent, AVStream* stream)
    : m_parent(parent)
    , m_stream(stream)
  {}
  virtual void GetStreamInfo(std::string& strInfo);
};


class CDemuxStreamAudioFFmpeg
  : public CDemuxStreamAudio
{
  CDVDDemuxFFmpeg *m_parent;
  AVStream*        m_stream;
public:
  CDemuxStreamAudioFFmpeg(CDVDDemuxFFmpeg *parent, AVStream* stream)
    : m_parent(parent)
    , m_stream(stream)
  {}
  std::string m_description;

  virtual void GetStreamInfo(std::string& strInfo);
  virtual void GetStreamName(std::string& strInfo);
};

class CDemuxStreamSubtitleFFmpeg
  : public CDemuxStreamSubtitle
{
  CDVDDemuxFFmpeg *m_parent;
  AVStream*        m_stream;
public:
  CDemuxStreamSubtitleFFmpeg(CDVDDemuxFFmpeg *parent, AVStream* stream)
    : m_parent(parent)
    , m_stream(stream)
  {}
  std::string m_description;

  virtual void GetStreamInfo(std::string& strInfo);
  virtual void GetStreamName(std::string& strInfo);

};

#define FFMPEG_FILE_BUFFER_SIZE   32768 // default reading size for ffmpeg
#define FFMPEG_DVDNAV_BUFFER_SIZE 2048  // for dvd's

class CDVDDemuxFFmpeg : public CDVDDemux
{
public:
  CDVDDemuxFFmpeg();
  virtual ~CDVDDemuxFFmpeg();

  bool Open(CDVDInputStream* pInput);
  void Dispose();
  void Reset();
  void Flush();
  void Abort();
  void SetSpeed(int iSpeed);
  virtual std::string GetFileName();

  DemuxPacket* Read();

  bool SeekTime(int time, bool backwords = false, double* startpts = NULL);
  bool SeekByte(__int64 pos);
  int GetStreamLength();
  CDemuxStream* GetStream(int iStreamId);
  int GetNrOfStreams();

  bool SeekChapter(int chapter, double* startpts = NULL);
  int GetChapterCount();
  int GetChapter();
  void GetChapterName(std::string& strChapterName);
  virtual void GetStreamCodecName(int iStreamId, CStdString &strName);

  bool Aborted();

  AVFormatContext* m_pFormatContext;

protected:
  friend class CDemuxStreamAudioFFmpeg;
  friend class CDemuxStreamVideoFFmpeg;
  friend class CDemuxStreamSubtitleFFmpeg;

  int ReadFrame(AVPacket *packet);
  void AddStream(int iId);

  double ConvertTimestamp(int64_t pts, int den, int num);
  void UpdateCurrentPTS();

  CCriticalSection m_critSection;
  #define MAX_STREAMS 100
  CDemuxStream* m_streams[MAX_STREAMS]; // maximum number of streams that ffmpeg can handle

  ByteIOContext* m_ioContext;

  DllAvFormat m_dllAvFormat;
  DllAvCodec  m_dllAvCodec;
  DllAvUtil   m_dllAvUtil;

  double   m_iCurrentPts; // used for stream length estimation
  bool     m_bMatroska;
  bool     m_bAVI;
  int      m_speed;
  unsigned m_program;
  XbmcThreads::EndTime  m_timeout;

  CDVDInputStream* m_pInput;
};

