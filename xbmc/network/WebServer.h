#pragma once


#include "system.h"
#ifdef HAS_WEB_SERVER
#include "utils/StdString.h"
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#ifdef __APPLE__
#include "lib/libmicrohttpd/src/include/microhttpd.h"
#else
#include <microhttpd.h>
#endif
#include "interfaces/json-rpc/ITransportLayer.h"
#include "threads/CriticalSection.h"

class CWebServer : public JSONRPC::ITransportLayer
{
public:
  CWebServer();

  bool Start(int port, const CStdString &username, const CStdString &password);
  bool Stop();
  bool IsStarted();
  void SetCredentials(const CStdString &username, const CStdString &password);

  virtual bool PrepareDownload(const char *path, CVariant &details, std::string &protocol);
  virtual bool Download(const char *path, CVariant &result);
  virtual int GetCapabilities();
private:
  enum HTTPMethod
  {
    UNKNOWN,
    POST,
    GET,
    HEAD
  };
  struct MHD_Daemon* StartMHD(unsigned int flags, int port);
  static int AskForAuthentication (struct MHD_Connection *connection);
  static bool IsAuthenticated (CWebServer *server, struct MHD_Connection *connection);

#if (MHD_VERSION >= 0x00090200)
  static ssize_t ContentReaderCallback (void *cls, uint64_t pos, char *buf, size_t max);
#elif (MHD_VERSION >= 0x00040001)
  static int ContentReaderCallback (void *cls, uint64_t pos, char *buf, int max);
#else
  static int ContentReaderCallback (void *cls, size_t pos, char *buf, int max);
#endif

#if (MHD_VERSION >= 0x00040001)
  static int JSONRPC(CWebServer *server, void **con_cls, struct MHD_Connection *connection, const char *upload_data, size_t *upload_data_size);
  static int AnswerToConnection (void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls);
#else   //libmicrohttpd < 0.4.0
  static int JSONRPC(CWebServer *server, void **con_cls, struct MHD_Connection *connection, const char *upload_data, unsigned int *upload_data_size);
  static int AnswerToConnection (void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        unsigned int *upload_data_size, void **con_cls);
#endif
  static void ContentReaderFreeCallback (void *cls);
  static int HttpApi(struct MHD_Connection *connection);
  static HTTPMethod GetMethod(const char *method);
  static int CreateRedirect(struct MHD_Connection *connection, const CStdString &strURL);
  static int CreateFileDownloadResponse(struct MHD_Connection *connection, const CStdString &strURL, HTTPMethod methodType);
  static int CreateErrorResponse(struct MHD_Connection *connection, int responseType, HTTPMethod method);
  static int CreateMemoryDownloadResponse(struct MHD_Connection *connection, void *data, size_t size);
  static int CreateAddonsListResponse(struct MHD_Connection *connection);

  static int FillArgumentMap(void *cls, enum MHD_ValueKind kind, const char *key, const char *value);
  static void StringToBase64(const char *input, CStdString &output);

  static const char *CreateMimeTypeFromExtension(const char *ext);

  struct MHD_Daemon *m_daemon;
  bool m_running, m_needcredentials;
  CStdString m_Credentials64Encoded;
  CCriticalSection m_critSection;

  class CHTTPClient : public JSONRPC::IClient
  {
  public:
    virtual int  GetPermissionFlags();
    virtual int  GetAnnouncementFlags();
    virtual bool SetAnnouncementFlags(int flags);
  };
};
#endif
