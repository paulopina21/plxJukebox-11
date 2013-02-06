


#pragma once

#include "utils/StdString.h"

/* forward declarations */
class PLT_UPnP;
class PLT_SyncMediaBrowser;
class CDeviceHostReferenceHolder;
class CCtrlPointReferenceHolder;
class CRendererReferenceHolder;
class CUPnPRenderer;
class CUPnPServer;
class PLT_MediaObject;
class PLT_MediaItemResource;

namespace MUSIC_INFO {
class CMusicInfoTag;
}

class CVideoInfoTag;


class CUPnP
{
public:
    CUPnP();
    ~CUPnP();

    // server
    void StartServer();
    void StopServer();

    // client
    void StartClient();
    void StopClient();
    bool IsClientStarted() { return (m_MediaBrowser != NULL); }

    // renderer
    void StartRenderer();
    void StopRenderer();
    void UpdateState();

    // methods
    static int PopulateTagFromObject(MUSIC_INFO::CMusicInfoTag& tag,
                                     PLT_MediaObject&           object,
                                     PLT_MediaItemResource*     resource = NULL);
    static int PopulateTagFromObject(CVideoInfoTag&             tag,
                                     PLT_MediaObject&           object,
                                     PLT_MediaItemResource*     resource = NULL);

    // class methods
    static CUPnP* GetInstance();
    static void   ReleaseInstance(bool bWait);
    static bool   IsInstantiated() { return upnp != NULL; }

private:
    // methods
    CUPnPRenderer* CreateRenderer(int port = 0);
    CUPnPServer*   CreateServer(int port = 0);

public:
    PLT_SyncMediaBrowser*       m_MediaBrowser;

private:
    CStdString                  m_IP;
    PLT_UPnP*                   m_UPnP;
    CDeviceHostReferenceHolder* m_ServerHolder;
    CRendererReferenceHolder*   m_RendererHolder;
    CCtrlPointReferenceHolder*  m_CtrlPointHolder;


    static CUPnP* upnp;
    static bool   broadcast;
};
