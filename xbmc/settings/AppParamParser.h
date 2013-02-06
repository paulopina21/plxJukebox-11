

#include "utils/StdString.h"
#include "FileItem.h"

class CAppParamParser
{
  public:
    CAppParamParser();
    void Parse(const char* argv[], int nArgs);

  private:
    bool m_testmode;
    CFileItemList m_playlist;
    void ParseArg(const CStdString &arg);
    void DisplayHelp();
    void DisplayVersion();
    void EnableDebugMode();
    void PlayPlaylist();
};
