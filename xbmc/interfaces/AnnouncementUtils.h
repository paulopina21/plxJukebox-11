#pragma once


#include "IAnnouncer.h"

namespace ANNOUNCEMENT
{
  class CAnnouncementUtils
  {
  public:
    /*!
     \brief Returns a string representation for the 
     given EAnnouncementFlag
     \param notification Specific EAnnouncementFlag
     \return String representation of the given EAnnouncementFlag
     */
    static inline const char *AnnouncementFlagToString(const EAnnouncementFlag &notification)
    {
      switch (notification)
      {
      case Player:
        return "Player";
      case GUI:
        return "GUI";
      case System:
        return "System";
      case VideoLibrary:
        return "VideoLibrary";
      case AudioLibrary:
        return "AudioLibrary";
      case Other:
        return "Other";
      default:
        return "Unknown";
      }
    }
  };
}
