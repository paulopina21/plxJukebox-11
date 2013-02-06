#ifndef KARAOKELYRICSTEXTLRC_H
#define KARAOKELYRICSTEXTLRC_H



// C++ Interface: karaokelyricstextlrc

#include "karaokelyricstext.h"


//! This class loads LRC format lyrics
class CKaraokeLyricsTextLRC : public CKaraokeLyricsText
{
  public:
    CKaraokeLyricsTextLRC( const CStdString & lyricsFile );
    ~CKaraokeLyricsTextLRC();

    //! Parses the lyrics or song file, and loads the lyrics into memory. Returns true if the
    //! lyrics are successfully loaded, false otherwise.
    bool Load();

  private:
    bool checkMultiTime(char *lyricData, unsigned int lyricSize);
    bool ParserNormal(char *lyricData, unsigned int lyricSize, int timing_correction);
    bool ParserMultiTime(char *lyricData, unsigned int lyricSize, int timing_correction);

    CStdString     m_lyricsFile;
};

#endif
