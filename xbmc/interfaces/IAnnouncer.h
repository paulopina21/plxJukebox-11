#pragma once


class CVariant;
namespace ANNOUNCEMENT
{
  enum EAnnouncementFlag
  {
    Player = 0x1,
    GUI = 0x2,
    System = 0x4,
    VideoLibrary = 0x8,
    AudioLibrary = 0x10,
    Other = 0x20
  };

  #define ANNOUNCE_ALL (Player | GUI | System | VideoLibrary | AudioLibrary | Other)

  class IAnnouncer
  {
  public:
    IAnnouncer() { };
    virtual ~IAnnouncer() { };
    virtual void Announce(EAnnouncementFlag flag, const char *sender, const char *message, const CVariant &data) = 0;
  };
}
