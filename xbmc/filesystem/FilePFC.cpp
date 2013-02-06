#include "FilePFC.h"
#include "URL.h"
#include "Util.h"
#include "../utils/URIUtils.h"
//#include "Rijndael.h"

#include <sys/stat.h>

using namespace XFILE;
using namespace std;

CFilePFC::CFilePFC() {
	m_scBuffer.bytesAvailable = 0;
	m_scBuffer.TempBufferLoad = 0;
  m_bCached = false;
  m_iRead = -1;
	pDumpFile = NULL;
	m_iFilePos = 0;
//	key = (byte*)CRYPTOKEY;
//	aes_encrypt_key256(key, ctx);
}

CFilePFC::~CFilePFC()
{
	if (pDumpFile) fclose(pDumpFile);
  //Close();
}

__inline void coolcopy(byte* pcSource, byte* pcDest, int64_t posSource, int64_t posDest, int64_t len)
{
	for (register int c=0; c<len; c++)
		pcDest[posDest+c] = pcSource[posSource+c];
}

bool CFilePFC::LoadHeader() {
  m_file.Seek(0, SEEK_SET);
  if (m_file.Read(&m_sHeader, sizeof(sRPFHeader)) != sizeof(sRPFHeader))
  {
    CLog::Log(LOGERROR, "PFCFile: Unable to read header: %s", strPFCFileName.c_str());
    return false;
  }

  if (m_sHeader.Signature[0] == RPF_PACKFILE_SGN0 && m_sHeader.Signature[1] == RPF_PACKFILE_SGN1
      && m_sHeader.Signature[2] == RPF_PACKFILE_SGN2 && m_sHeader.Signature[3] == RPF_PACKFILE_SGN3)
  {
    CLog::Log(LOGDEBUG, "PFCFile: Signed! Files declared: %i", m_sHeader.FileEntries);
    return true;
  }

  return false;
}

bool CFilePFC::LoadFileTable() {
  uint32_t headerEntries = m_sHeader.FileEntries;
  uint32_t iFileTableSize = ENTRYSIZE* m_sHeader.FileEntries;

  if (headerEntries > 0)
  {
    int64_t seekpos = m_file.GetLength() - iFileTableSize;

    if (!m_file.Seek(seekpos, SEEK_SET))
    {
      CLog::Log(LOGERROR, "PFCFile: Can't seek: %s!", strPFCFileName.c_str());
      return false;
    }

    m_vecFileTable.clear();
    m_vecFileTable.resize(headerEntries);

    if (m_file.Read(m_vecFileTable.data(), iFileTableSize) != iFileTableSize)
    {
      CLog::Log(LOGERROR, "PFCFile: Corrupted file: %s!", strPFCFileName.c_str());
      return false;
    }
  }
  else
  {
    CLog::Log(LOGERROR, "PFCFile: Broken or empty file: %s!", strPFCFileName.c_str());
    return false;
  }
  if (m_vecFileTable.size() <= 0) return false;

  return true;
}

bool CFilePFC::GetFileEntry(const CStdString& strFileName, sFileEntry& item) {
  for (VECFILEENTRY::iterator it2 = m_vecFileTable.begin(); it2 != m_vecFileTable.end(); ++it2)
  {
    if (CStdString(it2->FileName) == strFileName)
    {
      memcpy(&item, &(*it2), sizeof(sFileEntry));
      return true;
    }
  }
  CLog::Log( LOGERROR, "PFCFile: unable to find: %s", strFileName.c_str() );
  return false;
}

bool CFilePFC::GetEntriesList(VECFILEENTRY& items) {
  if ( m_vecFileTable.size() == 0) return false;
  items.clear();
  for (VECFILEENTRY::iterator it = m_vecFileTable.begin(); it != m_vecFileTable.end(); ++it)
  {
    items.push_back(*it);
  }

  //memcpy(&items, &m_vecFileTable, sizeof(sFileEntry));
  return true;
}

bool CFilePFC::Open(const CURL&url) {
  CLog::Log(LOGDEBUG, "CFilePFC::%s(%s)", __FUNCTION__, url.Get().c_str());
  strPFCFileName = url.GetHostName();
  strCurrentFileItemName = url.GetFileName();

  if ( !m_file.Open(strPFCFileName) ) { // this is the pfs-file, always open binary
    CLog::Log(LOGERROR,"FilePFC: unable to open PFC file %s!", strPFCFileName.c_str());
    return false;
  }

  if ( !LoadHeader() ) return false;
  if ( !LoadFileTable() ) return false;

	//URIUtils::
  if (URIUtils::IsInPFC(url.Get())) {
    if ( !GetFileEntry(strCurrentFileItemName, m_sCurrentFileRecord) ) return false;

    //Seek to begin of the file data
    m_file.Seek(m_sCurrentFileRecord.Offset, SEEK_SET);
  }
	m_iRead = 1;
	m_iFilePos = 0;

	CLog::Log(LOGDEBUG, "CFilePFC::%s: Openned: %s", __FUNCTION__, strCurrentFileItemName.c_str());
	return true;

}

int64_t CFilePFC::GetLength()
{
  return m_sCurrentFileRecord.UncryptedFileSize;
}

int64_t CFilePFC::GetPosition()
{
  if (m_bCached)
    return m_file.GetPosition();

  return m_iFilePos;
}

__inline int64_t FixBlockPosition(int64_t CurrentBlock) {
	if (CurrentBlock % CRYPT_BUFFER_SIZE != 0){
		//nextblock = CurrentBlock / CRYPT_BUFFER_SIZE;
		//nextblock = nextblock * CRYPT_BUFFER_SIZE; // block found...
		//toDiscard = CurrentBlock - nextblock;

		//m_iFilePos = mFile.Seek(mPFSItem.Offset + nextblock, SEEK_SET) - mPFSItem.Offset;
	}


}

int64_t CFilePFC::Seek(int64_t iFilePosition, int iWhence)
{
  //if (m_bCached)
  //  return mFile.Seek(iFilePosition,iWhence) - mPFSItem.Offset;

  // With Crypt - Hard Part
	if (m_sCurrentFileRecord.Crypt) {
    char temp[SEEK_BLOCK];
		int64_t nextblock = 0;
		int64_t iResult  = 0;
		int64_t toDiscard = 0;

		switch (iWhence) {
			case SEEK_SET:
				if (iFilePosition > m_sCurrentFileRecord.UncryptedFileSize)
					return -1;

				//if (m_iFilePos % CRYPT_BUFFER_SIZE != 0){
				//	nextblock = m_iFilePos / CRYPT_BUFFER_SIZE;
				//	nextblock = nextblock * CRYPT_BUFFER_SIZE; // block found...
				//	toDiscard = m_iFilePos - nextblock;

				//	m_iFilePos = mFile.Seek(mPFSItem.Offset + nextblock, SEEK_SET) - mPFSItem.Offset;
				//	m_iFilePos = iFilePosition;
				//	return iResult;
				//}


				m_iFilePos = iFilePosition;
				iResult = m_file.Seek(m_sCurrentFileRecord.Offset + iFilePosition, SEEK_SET) - m_sCurrentFileRecord.Offset;
				return iResult;
			break;

			case SEEK_CUR:
				if (m_iFilePos+iFilePosition > m_sCurrentFileRecord.UncryptedFileSize)
					return -1;

				//if (m_iFilePos % CRYPT_BUFFER_SIZE != 0){
				//	nextblock = m_iFilePos / CRYPT_BUFFER_SIZE;
				//	nextblock = nextblock * CRYPT_BUFFER_SIZE; // block found...
				//	toDiscard = m_iFilePos - nextblock;

				//	m_iFilePos = mFile.Seek(m_sfilerecord.Offset + nextblock, SEEK_SET) - m_sCurrentFileRecord.Offset;
				//	m_iFilePos = iFilePosition;
				//	return iResult;
				//}

				m_iFilePos += iFilePosition;
				iResult = m_file.Seek(iFilePosition,SEEK_CUR) - m_sCurrentFileRecord.Offset;
				return iResult;
			break;

			case SEEK_END:
				if (iFilePosition > m_sCurrentFileRecord.UncryptedFileSize)
					return -1;
				m_iFilePos = m_sCurrentFileRecord.UncryptedFileSize+iFilePosition;
				iResult = m_file.Seek(m_sCurrentFileRecord.Offset+m_sCurrentFileRecord.UncryptedFileSize+iFilePosition,SEEK_SET) - m_sCurrentFileRecord.Offset;
				return iResult;
			break;
	    
			default:
				return -1;

    }
  } 
			 else 
 { // no crypt - this is easy
    int64_t iResult;

//		iFilePosition += m_sCurrentFileRecord.Offset;

		switch (iWhence) {
			case SEEK_SET:
				if (iFilePosition == m_iFilePos)
					return m_iFilePos; // mp3reader does this lots-of-times

				if (iFilePosition > m_sCurrentFileRecord.UncryptedFileSize)
					return -1;

				m_iFilePos = iFilePosition;
				iResult = m_file.Seek(m_sCurrentFileRecord.Offset+iFilePosition, SEEK_SET) - m_sCurrentFileRecord.Offset;

				return iResult;
			break;

			case SEEK_CUR:
				if (iFilePosition == m_iFilePos)
					return m_iFilePos;

				if (m_iFilePos+iFilePosition > m_sCurrentFileRecord.UncryptedFileSize)
					return -1;
				m_iFilePos += iFilePosition;
				iResult = m_file.Seek(iFilePosition,SEEK_CUR) - m_sCurrentFileRecord.Offset;
				return iResult;
			break;

			case SEEK_END:
				if (iFilePosition == m_iFilePos)
					return m_iFilePos;
				if (iFilePosition > m_sCurrentFileRecord.UncryptedFileSize)
					return -1;
				m_iFilePos = m_sCurrentFileRecord.UncryptedFileSize+iFilePosition;
				iResult = m_file.Seek((m_sCurrentFileRecord.Offset+m_sCurrentFileRecord.UncryptedFileSize)+iFilePosition,SEEK_SET) - m_sCurrentFileRecord.Offset;
				return iResult;
			break;
	    
			default:
				return -1;

    }
  }
  // with crypt - here goes the hard part..
  //if (false)//(mPFSItem.Crypt == 2)
  //{
  //  char temp[SEEK_BLOCK];
		//int64_t nextblock = 0;
		//int64_t iResult;
  //  
  //  switch (iWhence)
  //  {
		//	case SEEK_SET:
		//		if (iFilePosition == 0)
		//			return mFile.Seek(m_sCurrentFileRecord.Offset, SEEK_SET) - m_sCurrentFileRecord.Offset;

		//		if (iFilePosition == m_iFilePos)
		//			return m_iFilePos; // mp3reader does this lots-of-times

		//		// This is because he already passed the item...
		//		if (iFilePosition > m_sCurrentFileRecord.UncryptedFileSize || iFilePosition < 0)
		//			return -1;

		//		// read until position in 32 Bytes blocks.. only way to do it due to format.
		//		// can't start in the middle of data since then we'd have no clue where
		//		// we are in uncompressed data..

		//		// Seems like he's just rounding the seek
		//		// update: three weeks later: now we know (he�s really rounding it)...

		//		if (iFilePosition < m_iFilePos)
		//		{
		//			nextblock = iFilePosition / SEEK_BLOCK;
		//			m_iFilePos = (nextblock * SEEK_BLOCK);
		//			m_iFilePos = mFile.Seek(m_sfilerecord.Offset + m_iFilePos, SEEK_SET) - m_sfilerecord.Offset;
		//			
		//			while (m_iFilePos < iFilePosition)
		//			{
		//				unsigned int iToRead = (iFilePosition-m_iFilePos)>SEEK_BLOCK?SEEK_BLOCK:(int)(iFilePosition-m_iFilePos);
		//				if (Read(temp,iToRead) != iToRead)
		//					return -1;
		//			}
		//			return m_iFilePos;
		//		}
		//		else{ // seek forward
		//			return Seek(iFilePosition-m_iFilePos,SEEK_CUR);
		//		}
		//		break;

		//	case SEEK_CUR:
		//		if (iFilePosition == 0)
		//			return m_iFilePos;
		//			//return mFile.Seek(mPFSItem.Offset + m_iFilePos, SEEK_SET) - mPFSItem.Offset;

		//		// can't rewind stream. Read until requested position, drop data
		//		if (iFilePosition < 0)
		//			return Seek(m_iFilePos+iFilePosition,SEEK_SET) - m_sfilerecord.Offset;
		//		
		//		// This is because he already past the item...
		//		if (m_iFilePos+iFilePosition > m_sfilerecord.UncryptedFileSize)
		//			return -1;

		//		int64_t targetPos;
		//		targetPos = m_iFilePos + iFilePosition;

		//		//nextblock = iFilePosition / SEEK_BLOCK;
		//		nextblock = targetPos / SEEK_BLOCK;
		//		iFilePosition = (nextblock * SEEK_BLOCK);
		//		
		//		//Ajusta para o inicio do proximo bloco
		//		m_iFilePos = mFile.Seek(m_sfilerecord.Offset + iFilePosition, SEEK_SET) - m_sfilerecord.Offset;
		//		
		//		//// If next block is before actual position, can't rewind stream. Read until requested position, drop data.
		//		//if (iFilePosition >= m_iFilePos)
		//		//	m_iFilePos = mFile.Seek((iFilePosition - m_iFilePos), SEEK_CUR) - mPFSItem.Offset;
		//		//else
		//		//	m_iFilePos = mFile.Seek(mPFSItem.Offset + iFilePosition, SEEK_SET) - mPFSItem.Offset;
		//		
		//		//Anda at� a targetPos
		//		while (m_iFilePos < targetPos)
		//		{
		//			unsigned int iToRead = (targetPos-m_iFilePos)>SEEK_BLOCK?SEEK_BLOCK:(int)(targetPos-m_iFilePos);
		//			if (Read(temp,iToRead) != iToRead)
		//				return -1;
		//		}
		//		return m_iFilePos;
		//		break;

		//	case SEEK_END:
		//		// now this is a nasty bastard, possibly takes lotsoftime
		//		nextblock = (m_sCurrentFileRecord.UncryptedFileSize+iFilePosition) / SEEK_BLOCK;
		//		m_iFilePos = (nextblock -1) * SEEK_BLOCK;
		//		m_iFilePos = mFile.Seek(m_sfilerecord.Offset + m_iFilePos, SEEK_SET) - m_sfilerecord.Offset;

		//		while( m_iFilePos < m_sCurrentFileRecord.UncryptedFileSize+iFilePosition)
		//		{
		//			unsigned int iToRead = ((m_sfilerecord.UncryptedFileSize+iFilePosition-m_iFilePos) > SEEK_BLOCK)?SEEK_BLOCK:(int)((m_sCurrentFileRecord.UncryptedFileSize+iFilePosition)-m_iFilePos);
		//			if (Read(temp,iToRead) != iToRead)
		//				return -1;
		//		}
		//		return m_iFilePos;
		//		break;
		//	default:
		//		return -1;
  //  }
  //}
  return -1;
}

bool CFilePFC::Exists(const CURL& url)
{
  return Open(url);
  //sFileEntry item;
  //if ( !Open(url) ) return false;
  //return GetFileEntry(url.GetFileNameWithoutPath(), item);
}

int CFilePFC::UpdateTempBuffer(int64_t amount) {
	if (amount >= m_scBuffer.bytesAvailable) {
		coolcopy(m_scBuffer.buffer,m_scBuffer.TempBuffer,(CRYPT_BUFFER_SIZE - m_scBuffer.bytesAvailable),m_scBuffer.TempBufferLoad , m_scBuffer.bytesAvailable);
		m_scBuffer.TempBufferLoad += m_scBuffer.bytesAvailable;
		return m_scBuffer.bytesAvailable;
	} else {
		coolcopy(m_scBuffer.buffer,m_scBuffer.TempBuffer,(CRYPT_BUFFER_SIZE - m_scBuffer.bytesAvailable),m_scBuffer.TempBufferLoad , amount);
		m_scBuffer.TempBufferLoad += amount;
		return amount;
	}
}

void CFilePFC::DumpThis(char * pFileName, byte* what, int64_t uiBufSize) {
	if (!pDumpFile) {
		pDumpFile = fopen(pFileName, "wb");
		fseek(pDumpFile, 0, SEEK_SET);
	}

	if (uiBufSize > 0)
		fwrite(what, uiBufSize , 1, pDumpFile);

	fclose(pDumpFile);
	pDumpFile = NULL;
}

unsigned int CFilePFC::Read(void* lpBuf, int64_t uiBufSize) {
	int delivered = 0;
	int64_t toDiscard = 0;
	int64_t nextblock = 0;

  if (m_bCached)
    return m_file.Read(lpBuf,uiBufSize);

	if (uiBufSize+m_iFilePos > m_sCurrentFileRecord.UncryptedFileSize)
		uiBufSize = m_sCurrentFileRecord.UncryptedFileSize-m_iFilePos;

	if (uiBufSize < 0)
		return 0; // we are past eof, this shouldn't happen but test anyway
  
	//if (mPFSItem.method == 0) // 0 for crypto
 // {
	//	// Wrong position to decrypt! We need to correct. Add 32 Bytes to read and just copy the necessary after.
	//	if (m_iFilePos % CRYPT_BUFFER_SIZE != 0){
	//		nextblock = m_iFilePos / CRYPT_BUFFER_SIZE;
	//		nextblock = nextblock * CRYPT_BUFFER_SIZE; // block found...
	//		toDiscard = m_iFilePos - nextblock;

	//		m_iFilePos = mFile.Seek(mPFSItem.Offset + nextblock, SEEK_SET) - mPFSItem.Offset;
	//		uiBufSize += CRYPT_BUFFER_SIZE;
	//	}

	//	while(uiBufSize > m_scBuffer.TempBufferLoad) {

	//		if (m_scBuffer.bytesAvailable <= 0)
	//			if (!FillCryptoBuffer()) 
	//				return 0;

	//		if (uiBufSize > m_scBuffer.bytesAvailable) {
	//			delivered += UpdateTempBuffer(m_scBuffer.bytesAvailable);
	//			m_scBuffer.bytesAvailable -= delivered;
	//		} else {
	//			m_scBuffer.bytesAvailable -= UpdateTempBuffer(uiBufSize-delivered);
	//		}
	//	}
	//	
	//	if (toDiscard != 0){
	//		uiBufSize -= CRYPT_BUFFER_SIZE;
	//		m_scBuffer.TempBufferLoad -= CRYPT_BUFFER_SIZE;
	//		m_iFilePos += toDiscard - CRYPT_BUFFER_SIZE;
	//	}

	//	coolcopy(m_scBuffer.TempBuffer,(byte*)lpBuf,toDiscard,0,uiBufSize);
	////	DumpThis("C:\\lpbuf.txt", (byte*)lpBuf, uiBufSize);
	////	DumpThis("C:\\TempBuffer.txt", m_scBuffer.TempBuffer, uiBufSize + toDiscard);

	//	int64_t iResult = m_scBuffer.TempBufferLoad;

	//	m_scBuffer.TempBufferLoad = 0;
	//	m_scBuffer.bytesAvailable = 0;

 //   //m_iFilePos += iResult;
 //   return iResult;
 // } else 
	{

		unsigned int iResult = m_file.Read(lpBuf, uiBufSize);

		//unsigned char* buff = NULL;

		//byte TempBuffer = '\0';

		//aes_ofb_crypt((const byte*)lpBuf, (byte*)lpBuf, iResult, m_sfilerecord.InitData, ctx);
		
		//coolcopy(&TempBuffer,(byte*)lpBuf,0,0,uiBufSize);

		//		DumpThis("C:\\lpbuf.txt", (byte*)lpBuf, uiBufSize);
		m_iFilePos += iResult;
		return iResult;
	}
    return false; // shouldn't happen. compression method checked in open
}

void CFilePFC::Close()
{
  m_file.Close();
}

inline bool CFilePFC::FillCryptoBuffer() { // AND DECRYPT
	int64_t nextblock = 0;
//	int64_t toDiscard = 0;	

	if (m_iFilePos + CRYPT_BUFFER_SIZE > m_sCurrentFileRecord.CryptedFileSize)
		return false; // eof!

	// Wrong position to decrypt! We need to correct
	//if (m_iFilePos % CRYPT_BUFFER_SIZE != 0){
	//	nextblock = m_iFilePos / CRYPT_BUFFER_SIZE;
	//	nextblock = nextblock * CRYPT_BUFFER_SIZE;
	//	toDiscard = m_iFilePos - nextblock;

	//	mFile.Seek(mPFSItem.Offset + nextblock, SEEK_SET) - mPFSItem.Offset;
	//	m_scBuffer.bytesAvailable = mFile.Read(m_scBuffer.buffer,CRYPT_BUFFER_SIZE) - toDiscard;
	//}
	//else{//Position OK. Just read

	m_scBuffer.bytesAvailable = m_file.Read(m_scBuffer.buffer,CRYPT_BUFFER_SIZE);
	if (m_scBuffer.bytesAvailable != CRYPT_BUFFER_SIZE) {
		m_iFilePos += m_scBuffer.bytesAvailable;
		return false;
	}

	byte buff[CRYPT_BUFFER_SIZE];


//	CRijndael oRijndael;
	//oRijndael.MakeKey(BUTTERFLY, CRijndael::sm_chain0, 32, 32);
//	oRijndael.Decrypt((char*)m_scBuffer.buffer,(char*)m_scBuffer.buffer, CRYPT_BUFFER_SIZE, CRijndael::ECB);
	m_iFilePos += m_scBuffer.bytesAvailable;

	return true;
}
