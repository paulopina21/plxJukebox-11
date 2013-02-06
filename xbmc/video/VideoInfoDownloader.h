#pragma once



#include "threads/Thread.h"
#include "VideoInfoTag.h"
#include "addons/Scraper.h"
#include "Episode.h"
#include "XBDateTime.h"
#include "filesystem/FileCurl.h"

// forward declarations
class TiXmlDocument;
class CGUIDialogProgress;

namespace ADDON
{
class CScraperError;
}

typedef std::vector<CScraperUrl> MOVIELIST;

class CVideoInfoDownloader : public CThread
{
public:
  CVideoInfoDownloader(const ADDON::ScraperPtr &scraper) : m_info(scraper) {}
  virtual ~CVideoInfoDownloader() {}

  // threaded lookup functions

  /*! \brief Do a search for matching media items (possibly asynchronously) with our scraper
   \param strMovie name of the media item to look for
   \param movielist [out] list of results to fill. May be empty on success.
   \param pProgress progress bar to update as we go. If NULL we run on thread, if non-NULL we run off thread.
   \return 1 on success, -1 on a scraper-specific error, 0 on some other error
   */
  int FindMovie(const CStdString& strMovie, MOVIELIST& movielist, CGUIDialogProgress *pProgress = NULL);
  bool GetDetails(const CScraperUrl& url, CVideoInfoTag &movieDetails, CGUIDialogProgress *pProgress = NULL);
  bool GetEpisodeDetails(const CScraperUrl& url, CVideoInfoTag &movieDetails, CGUIDialogProgress *pProgress = NULL);
  bool GetEpisodeList(const CScraperUrl& url, EPISODELIST& details, CGUIDialogProgress *pProgress = NULL);

  static void ShowErrorDialog(const ADDON::CScraperError &sce);

protected:
  enum LOOKUP_STATE { DO_NOTHING = 0,
                      FIND_MOVIE = 1,
                      GET_DETAILS = 2,
                      GET_EPISODE_LIST = 3,
                      GET_EPISODE_DETAILS = 4 };

  XFILE::CFileCurl m_http;
  CStdString        m_strMovie;
  MOVIELIST         m_movieList;
  CVideoInfoTag     m_movieDetails;
  CScraperUrl       m_url;
  EPISODELIST       m_episode;
  LOOKUP_STATE      m_state;
  int               m_found;
  ADDON::ScraperPtr m_info;

  // threaded stuff
  void Process();
  void CloseThread();

  int InternalFindMovie(const CStdString& strMovie, MOVIELIST& movielist, bool cleanChars = true);
};

