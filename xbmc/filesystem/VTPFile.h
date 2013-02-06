#pragma once


#include "IFile.h"
#include "ILiveTV.h"

#include <sys/socket.h>

class CVTPSession;

namespace XFILE {

class CVTPFile
  : public  IFile
  ,         ILiveTVInterface
{
public:
  CVTPFile();
  virtual ~CVTPFile();
  virtual bool          Open(const CURL& url);
  virtual int64_t       Seek(int64_t pos, int whence=SEEK_SET);
  virtual int64_t       GetPosition()                                  { return -1; }
  virtual int64_t       GetLength()                                    { return -1; }
  virtual int           Stat(const CURL& url, struct __stat64* buffer) { return -1; }
  virtual void          Close();
  virtual unsigned int  Read(void* buffer, int64_t size);
  virtual CStdString    GetContent()                                   { return ""; }
  virtual bool          SkipNext()                                     { return m_socket ? true : false; }

  virtual bool          Delete(const CURL& url)                        { return false; }
  virtual bool          Exists(const CURL& url)                        { return false; }

  virtual ILiveTVInterface* GetLiveTV() {return (ILiveTVInterface*)this;}

  virtual bool           NextChannel();
  virtual bool           PrevChannel();
  virtual bool           SelectChannel(unsigned int channel);

  virtual int            GetTotalTime()              { return 0; }
  virtual int            GetStartTime()              { return 0; }
  virtual bool           UpdateItem(CFileItem& item) { return false; }

  virtual int            IoControl(EIoControl request, void* param);
protected:
  CVTPSession* m_session;
  SOCKET       m_socket;
  int          m_channel;
};

}


