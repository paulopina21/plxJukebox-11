


#ifndef __EMU_FILE_WRAPPER_H__
#define __EMU_FILE_WRAPPER_H__

#include <stdio.h>

#include "system.h"
#include "threads/CriticalSection.h"

#if defined(_LINUX) && !defined(__APPLE__) && !defined(__FreeBSD__)
#define _file _fileno
#endif

#define MAX_EMULATED_FILES    50
#define FILE_WRAPPER_OFFSET   0x00000100

namespace XFILE
{
  class CFile;
}

typedef struct stEmuFileObject
{
  bool    used;
  FILE    file_emu;
  XFILE::CFile*  file_xbmc;
  CCriticalSection *file_lock;
  int mode;
} EmuFileObject;

class CEmuFileWrapper
{
public:
  CEmuFileWrapper();
  ~CEmuFileWrapper();
  
  /**
   * Only to be called when shutting down xbmc
   */
  void CleanUp();
  
  EmuFileObject* RegisterFileObject(XFILE::CFile* pFile);
  void UnRegisterFileObjectByDescriptor(int fd);
  void UnRegisterFileObjectByStream(FILE* stream);
  void LockFileObjectByDescriptor(int fd);
  bool TryLockFileObjectByDescriptor(int fd);
  void UnlockFileObjectByDescriptor(int fd);
  EmuFileObject* GetFileObjectByDescriptor(int fd);  
  EmuFileObject* GetFileObjectByStream(FILE* stream);  
  XFILE::CFile* GetFileXbmcByDescriptor(int fd);
  XFILE::CFile* GetFileXbmcByStream(FILE* stream);
  int GetDescriptorByStream(FILE* stream);
  FILE* GetStreamByDescriptor(int fd);
  bool DescriptorIsEmulatedFile(int fd);
  bool StreamIsEmulatedFile(FILE* stream);
private:
  EmuFileObject m_files[MAX_EMULATED_FILES];
  CCriticalSection m_criticalSection;
  bool m_initialized;
};

extern CEmuFileWrapper g_emuFileWrapper;

#endif

