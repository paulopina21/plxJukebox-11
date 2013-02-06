#pragma once

#include "system.h"
#include "interfaces/json-rpc/ITransportLayer.h"
#include "interfaces/json-rpc/JSONRPC.h"

#ifdef HAS_JSONRPC
class CPythonTransport : public JSONRPC::ITransportLayer
{
public:
  virtual bool PrepareDownload(const char *path, CVariant &details, std::string &protocol) { return false; }
  virtual bool Download(const char *path, CVariant &result) { return false; }
  virtual int GetCapabilities() { return JSONRPC::Response; }

  class CPythonClient : public JSONRPC::IClient
  {
  public:
    virtual int  GetPermissionFlags() { return JSONRPC::OPERATION_PERMISSION_ALL; }
    virtual int  GetAnnouncementFlags() { return 0; }
    virtual bool SetAnnouncementFlags(int flags) { return true; }
  };
};
#endif
