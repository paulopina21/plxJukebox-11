#pragma once



#include "DVDInputStream.h"
#include "boost/shared_ptr.hpp"

class CDVDInputStreamStack : public CDVDInputStream
{
public:
  CDVDInputStreamStack();
  virtual ~CDVDInputStreamStack();

  virtual bool    Open(const char* path, const std::string &content);
  virtual void    Close();
  virtual int     Read(BYTE* buf, int buf_size);
  virtual __int64 Seek(__int64 offset, int whence);
  virtual bool Pause(double dTime) { return false; };
  virtual bool    IsEOF();
  virtual __int64 GetLength();

protected:

  typedef boost::shared_ptr<XFILE::CFile> TFile;

  struct TSeg
  {
    TFile   file;
    __int64 length;
  };

  typedef std::vector<TSeg> TSegVec;

  TSegVec m_files;  ///< collection of open ptr's to all files in stack
  TFile   m_file;   ///< currently active file
  bool    m_eof;
  __int64 m_pos;
  __int64 m_length;
};
