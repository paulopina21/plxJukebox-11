#ifndef __XBMC_ADDON_TYPES_H__
#define __XBMC_ADDON_TYPES_H__



#ifdef __cplusplus
extern "C" {
#endif

enum ADDON_STATUS
{
  ADDON_STATUS_OK,
  ADDON_STATUS_LOST_CONNECTION,
  ADDON_STATUS_NEED_RESTART,
  ADDON_STATUS_NEED_SETTINGS,
  ADDON_STATUS_UNKNOWN,
  ADDON_STATUS_NEED_SAVEDSETTINGS
};

typedef struct
{
  int           type;
  char*         id;
  char*         label;
  int           current;
  char**        entry;
  unsigned int  entry_elements;
} ADDON_StructSetting;

#ifdef __cplusplus
};
#endif

#endif
