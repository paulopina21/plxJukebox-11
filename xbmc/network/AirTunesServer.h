#pragma once

#include "system.h"

#ifdef HAS_AIRTUNES

#include "DllLibShairport.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include "threads/Thread.h"
#include "threads/CriticalSection.h"
#include "utils/HttpParser.h"
#include "utils/StdString.h"
#include "filesystem/FilePipe.h"

class DllLibShairport;

class CAirTunesServer : public CThread
{
public:
  static bool StartServer(int port, bool nonlocal, bool usePassword, const CStdString &password="");
  static void StopServer(bool bWait);

protected:
  void Process();

private:
  CAirTunesServer(int port, bool nonlocal);
  ~CAirTunesServer();
  bool Initialize(const CStdString &password);
  void Deinitialize();

  int m_port;
  static DllLibShairport *m_pLibShairport;//the lib
  static CAirTunesServer *ServerInstance;
  static CStdString m_macAddress;

  class AudioOutputFunctions
  {
    public:
      static void ao_initialize(void);
      static int ao_play(ao_device *device, char *output_samples, uint32_t num_bytes);
      static int ao_default_driver_id(void);
      static ao_device* ao_open_live( int driver_id, ao_sample_format *format,
                                      ao_option *option);
      static int ao_close(ao_device *device);
      /* -- Device Setup/Playback/Teardown -- */
      static int ao_append_option(ao_option **options, const char *key, const char *value);
      static void ao_free_options(ao_option *options);
      static char* ao_get_option(ao_option *options, const char* key);
    };
};

#endif
