

#ifndef XBTFREADER_H_
#define XBTFREADER_H_

#include <vector>
#include <map>
#include "utils/StdString.h"
#include "XBTF.h"

class CXBTFReader
{
public:
  CXBTFReader();
  bool IsOpen() const;
  bool Open(const CStdString& fileName);
  void Close();
  time_t GetLastModificationTimestamp();
  bool Exists(const CStdString& name);
  CXBTFFile* Find(const CStdString& name);
  bool Load(const CXBTFFrame& frame, unsigned char* buffer);
  std::vector<CXBTFFile>&  GetFiles();

private:
  CXBTF      m_xbtf;
  CStdString m_fileName;
  FILE*      m_file;
  std::map<CStdString, CXBTFFile> m_filesMap;
};

#endif
