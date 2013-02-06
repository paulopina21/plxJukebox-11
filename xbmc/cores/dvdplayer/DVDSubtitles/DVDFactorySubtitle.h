#pragma once



#include <string>
#include <vector>

class CDVDSubtitleParser;
class CDVDSubtitleStream;

typedef std::vector<std::string> VecSubtitleFiles;
typedef std::vector<std::string>::iterator VecSubtitleFilesIter;

class CDVDFactorySubtitle
{
public:
  static CDVDSubtitleParser* CreateParser(std::string& strFile);
};

