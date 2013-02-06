#ifndef FILE_PFC_H
#define FILE_PFC_H

#include "IFile.h"
#include "utils/log.h"
#include "File.h"
#include "../jukebox/PFCHeaders.h"
//#include "PFCManager.h"

//#include <aes.h>

#ifdef _WIN32
#pragma comment(lib, "aes.lib")
#endif

#define CRYPT_BUFFER_SIZE 32
#define SEEK_BLOCK 32

struct sCryptBuffer {
	BYTE buffer[CRYPT_BUFFER_SIZE];
	BYTE* TempBuffer;
	int64_t TempBufferLoad;
	int64_t bytesAvailable;
	int64_t bufferPointer;
};

namespace XFILE {

class CFilePFC: public IFile {
public:
	CFilePFC();
	virtual ~CFilePFC();

	virtual int64_t GetPosition();
	virtual int64_t GetLength();
	virtual bool Open(const CURL& url);
	virtual bool Exists(const CURL& url);
	virtual int Stat(struct __stat64* buffer)
	{
	  //return m_file.Stat(buffer);
		return 0;
	}
	virtual int Stat(const CURL& url, struct __stat64* buffer)
	{
	  //return m_file.Stat(url.Get(), buffer);
		return 0;
	}
	virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
	virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
	virtual void Close();

	int UpdateTempBuffer(int64_t amount);
  bool GetEntriesList(VECFILEENTRY& items);

private:
	CFile m_file;
	CStdString strPFCFileName;
	CStdString strCurrentFileItemName;

  sRPFHeader        m_sHeader;
  sFileEntry            m_sCurrentFileRecord;
  VECFILEENTRY    m_vecFileTable;

  bool LoadHeader();
  bool LoadFileTable();
  bool GetFileEntry(const CStdString& strFileName, sFileEntry& item);

	FILE * pDumpFile;
	int m_iRead;
	bool m_bCached;

	int64_t m_iFilePos; // position in _uncompressed_ data read

	sCryptBuffer m_scBuffer;
	unsigned char *key;
//	aes_encrypt_ctx ctx[1];

	int64_t FixBlockPosition(int64_t CurrentBlock);
	void DumpThis(char * pFileName, byte* what, int64_t uiBufSize);
	bool FillCryptoBuffer();

};

}

#endif
