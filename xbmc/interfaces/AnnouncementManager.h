#pragma once


#include "IAnnouncer.h"
#include "FileItem.h"
#include "threads/CriticalSection.h"
#include <vector>

namespace ANNOUNCEMENT
{
  class CAnnouncementManager
  {
  public:
    static void AddAnnouncer(IAnnouncer *listener);
    static void RemoveAnnouncer(IAnnouncer *listener);
    static void Announce(EAnnouncementFlag flag, const char *sender, const char *message);
    static void Announce(EAnnouncementFlag flag, const char *sender, const char *message, CVariant &data);
    static void Announce(EAnnouncementFlag flag, const char *sender, const char *message, CFileItemPtr item);
    static void Announce(EAnnouncementFlag flag, const char *sender, const char *message, CFileItemPtr item, CVariant &data);
  private:
    static std::vector<IAnnouncer *> m_announcers;
    static CCriticalSection m_critSection;
  };
}
