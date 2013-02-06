#pragma once


#include "utils/StdString.h"
#include "JSONRPC.h"
#include "FileItemHandler.h"

class CVideoDatabase;

namespace JSONRPC
{
  class CVideoLibrary : public CFileItemHandler
  {
  public:
    static JSON_STATUS GetMovies(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetMovieDetails(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetMovieSets(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetMovieSetDetails(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSON_STATUS GetTVShows(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetTVShowDetails(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetSeasons(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetEpisodes(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetEpisodeDetails(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSON_STATUS GetMusicVideos(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetMusicVideoDetails(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSON_STATUS GetRecentlyAddedMovies(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetRecentlyAddedEpisodes(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS GetRecentlyAddedMusicVideos(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    
    static JSON_STATUS GetGenres(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSON_STATUS Scan(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Export(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSON_STATUS Clean(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static bool FillFileItem(const CStdString &strFilename, CFileItem &item);
    static bool FillFileItemList(const CVariant &parameterObject, CFileItemList &list);

  private:
    static JSON_STATUS GetAdditionalMovieDetails(const CVariant &parameterObject, CFileItemList &items, CVariant &result, CVideoDatabase &videodatabase);
    static JSON_STATUS GetAdditionalEpisodeDetails(const CVariant &parameterObject, CFileItemList &items, CVariant &result, CVideoDatabase &videodatabase);
    static JSON_STATUS GetAdditionalMusicVideoDetails(const CVariant &parameterObject, CFileItemList &items, CVariant &result, CVideoDatabase &videodatabase);
  };
}
