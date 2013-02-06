#ifndef PFC_HEADER_H
#define PFC_HEADER_H

#include <string.h>
#include <stdint.h>
#include <vector>

typedef unsigned char BYTE;

#define RPF_BUFFERSIZE 128
#define RPF_VERSION 2.0f

#define RPF_PACKFILE_SGN0 'R'
#define RPF_PACKFILE_SGN1 'P'
#define RPF_PACKFILE_SGN2 'F'
#define RPF_PACKFILE_SGN3 'S'
//0x52504653

#define NAMESIZE 150

//#define CRYPTOKEY "��K��K�Xe����e����}��o������~H����xd{^��E�������<բ,u*]<�m[A�dݞ{ۇ����,���Vw��<�-L���,�p�YyI��W���x�	@��s}99�#3;�|���ہ��<�.�'hOg<�����G�*�sx����TEy�!i�R��p�����Lz���L�"

#define HEADERSIZE sizeof(sRPFHeader)
#define ENTRYSIZE sizeof(sFileEntry)

#define DEFSFILE ".defs.nfo"
//#define IS_ALBUMFILE

//typedef unsigned __int32 uint32_t;

enum ePACKTYPE {
	RPF_PACK_TYPE_NONE = 0,
	RPF_PACK_TYPE_PACKAGE = 1,
	RPF_PACK_TYPE_MUSIC = 2,
	RPF_PACK_TYPE_ALBUM = 3,
	RPF_PACK_TYPE_ALBUM_SINGLE = 4,
	RPF_PACK_TYPE_ALBUM_COMPILATION = 5,
	RPF_PACK_TYPE_MOVIE = 6,
	RPF_PACK_TYPE_TVSHOW = 7,
	RPF_PACK_TYPE_TVSHOW_SEASON = 8,
	RPF_PACK_TYPE_TVSHOW_EPISODE = 9,
	RPF_PACK_TYPE_ECLASS = 10
};
enum eENTRYTYPE {
	RPF_ENTRY_TYPE_NONE = 0,
	RPF_ENTRY_TYPE_FILE = 1,
	RPF_ENTRY_TYPE_FILE_HIDDEN = 2,
	RPF_ENTRY_TYPE_SYSTEM = 3,
	RPF_ENTRY_TYPE_DEFINED = 4 // Files with this flag requires a ".nfo" file with the same name
};

struct sRPFHeader { // 4.096 bytes default header
	BYTE Signature[4];
	BYTE Digest[16];
	ePACKTYPE PackType;
	float Version;
	uint32_t FileEntries;

	sRPFHeader()
	{
		Signature[0] = RPF_PACKFILE_SGN0;
		Signature[1] = RPF_PACKFILE_SGN1;
		Signature[2] = RPF_PACKFILE_SGN2;
		Signature[3] = RPF_PACKFILE_SGN3;
		Digest[0] = '\0';

		PackType = RPF_PACK_TYPE_NONE;
		Version = 0.0f;
		FileEntries = 0;
	}
};

struct sFileEntry {
	eENTRYTYPE EntryType;
	bool Crypt;

	uint32_t FileIndex;
	uint32_t Offset;
	uint32_t Crc;

	uint32_t CryptedFileSize; // compressed size
	uint32_t UncryptedFileSize; // uncompressed size

	char FileName[255];

	BYTE InitData[16];

	sFileEntry()
	{
		EntryType = RPF_ENTRY_TYPE_NONE;
		Crypt = false;

		FileIndex = 0;
		Offset = 0;
		Crc = 0;

		CryptedFileSize = 0;
		UncryptedFileSize = 0;

		FileName[0] = '\0';
		InitData[0] = '\0';
	}

	sFileEntry(const sFileEntry& SNewItem)
	{
		memcpy(&EntryType, &SNewItem.EntryType, sizeof(EntryType));
		memcpy(&Crc, &SNewItem.Crc, sizeof(uint32_t));
		memcpy(&Crypt, &SNewItem.Crypt, sizeof(bool));
		memcpy(&Offset, &SNewItem.Offset, sizeof(uint32_t));
		memcpy(InitData, SNewItem.InitData, 16 * sizeof(BYTE));
		memcpy(FileName, SNewItem.FileName, 255 * sizeof(char));
		memcpy(&FileIndex, &SNewItem.FileIndex, sizeof(uint32_t));
		memcpy(&CryptedFileSize, &SNewItem.CryptedFileSize, sizeof(uint32_t));
		memcpy(&UncryptedFileSize, &SNewItem.UncryptedFileSize, sizeof(uint32_t));
	}
};

typedef std::vector<sFileEntry> VECFILEENTRY;

#endif
