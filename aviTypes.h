
#ifndef AVI__HEADER
#define AVI__HEADER
#include <iostream>
#include <string>

using namespace std;

typedef unsigned char BYTE;  // 1byte
typedef uint16_t  WORD;  // 2bytes
typedef uint32_t  DWORD; // 4bytes
typedef uint32_t 	FOURCC;// 4bytes

static const DWORD VALID_AVI_START_HEADER = 0x46464952;//"RIFF";
static const DWORD VALID_LIST_HEADER	  = 0x5453494c;//"LIST";
//static const BYTE VALID_AVI_LIST_HEADER [4] = {'L', 'I', 'S', 'T'};

unsigned long parse_size(char *buf) {
	unsigned long *long_buf = (unsigned long *)buf;
	return long_buf[0];
}

class LIST {
private:
	void printFourCC(string s, FOURCC fourCC) {
		char c1 = (char)fourCC;
		char c2 = (char)(fourCC>>8);
		char c3 = (char)(fourCC>>16);
		char c4 = (char)(fourCC>>24);
		printf("%s: %c%c%c%c\n", s.c_str(),c1,c2,c3,c4);
	}
	void printSize(string s, FOURCC fourCC) {
		//unsigned int num;
		//num = (fourCC >> 24) | (fourCC >> 8 & 0x0000FF00) | (fourCC << 8 & 0x00FF0000) | (fourCC << 24);
		//printf("%s: %u\n", s.c_str(),num);
		printf("%s: %u\n", s.c_str(),fourCC);
	}
public:
	FOURCC dwList;
	DWORD dwSize;
	FOURCC dwFourCC;
	// print List info
	void print(){
		printFourCC("dwList",dwList);
		printSize("dwSize",dwSize);
		printFourCC("dwFourCC",dwFourCC);
	}

	//after this point we have the data. the size of the data is specefied by (dwSize - 4) bytes
};

class CHUNK {
public:
	FOURCC dwFourCC;
	DWORD dwSize;
	//after this point we have the data. the size of the data is specefied by dwSize
};

class AVIMAINHEADER {
public:
	FOURCC fcc;		// 'avih'
	DWORD  cb;		// size minus 8 bytes
	DWORD  dwMicroSecPerFrame;
	DWORD  dwPaddingGranularity;	// pad to multiples of this size; normally 2K for cd-rom
	DWORD  dwMaxBytesPerSec;
	DWORD  dwFlags;
	DWORD  dwTotalFrames;
	DWORD  dwInitialFrames;
	// There is one strl - List for each stream. If the number of strl - Lists inside the hdrl - List
	// is different from MainAVIHeader::dwStreams, a fatal error should be reported.
	DWORD  dwStreams;
	DWORD  dwSuggestedBufferSize;
	DWORD  dwWidth;
	DWORD  dwHeight;
	DWORD  dwReserved[4];
}; 

#endif