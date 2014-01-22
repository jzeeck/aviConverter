
#ifndef AVI__HEADER
#define AVI__HEADER
#include <iostream>
#include <string>

using namespace std;

//Raw Data Types
typedef uint8_t   BYTE;  // 1byte
typedef uint16_t  WORD;  // 2bytes
typedef uint32_t  DWORD; // 4bytes
typedef uint8_t   SIZE[4];
typedef uint32_t 	FOURCC;// 4bytes


//Static values
static const DWORD VALID_AVI_START_HEADER = 0x46464952;//"RIFF";
static const DWORD VALID_LIST_HEADER	  = 0x5453494c;//"LIST";

/* The Flags in AVI File header */
#define AVIF_HASINDEX           0x00000010      /* Index at end of file */
#define AVIF_MUSTUSEINDEX       0x00000020
#define AVIF_ISINTERLEAVED      0x00000100
#define AVIF_TRUSTCKTYPE        0x00000800      /* Use CKType to find key frames */
#define AVIF_WASCAPTUREFILE     0x00010000
#define AVIF_COPYRIGHTED        0x00020000


//Helper functions
namespace auxiliary
{
	void printFlags(DWORD flags) {
		if (flags & AVIF_HASINDEX)
		{
			printf("%s\n", "This file has an index.");
		}
		if (flags & AVIF_MUSTUSEINDEX)
		{
			printf("%s\n", "This file must use index.");
		}
		//TODO more flags figure out what they do.
	}

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
	void printDW(string s, FOURCC fourCC) {
		//unsigned int num;
		//num = (fourCC >> 24) | (fourCC >> 8 & 0x0000FF00) | (fourCC << 8 & 0x00FF0000) | (fourCC << 24);
		//printf("%s: %u\n", s.c_str(),num);
		printf("%s: %u\n", s.c_str(),fourCC);
	}
	void printDW(FOURCC fourCC) {
		//unsigned int num;
		//num = (fourCC >> 24) | (fourCC >> 8 & 0x0000FF00) | (fourCC << 8 & 0x00FF0000) | (fourCC << 24);
		//printf("%s: %u\n", s.c_str(),num);
		printf("%u\n",fourCC);
	}
	uint32_t getSizeAsInt(SIZE dwSize) {
		uint32_t size = 0;
		//size = size | (dwSize>>24);
		//size = size | ((dwSize<<8)>>24)<<8;
		//size = size | ((dwSize<<16)>>24)<<16;
		size = dwSize[0] | (dwSize[1]<<8) | (dwSize[2]<<16) | (dwSize[3]<<24);
		return size;
	}
}


//AVI datatypes
class LIST {
public:
	FOURCC dwList;
	SIZE dwSize;
	FOURCC dwFourCC;
	// print List info
	void print(){
		auxiliary::printFourCC("dwList",dwList);
		auxiliary::printSize("dwSize",auxiliary::getSizeAsInt(dwSize));
		auxiliary::printFourCC("dwFourCC",dwFourCC);
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
	SIZE  cb;		// size minus 8 bytes
	DWORD  dwMicroSecPerFrame;
	DWORD  dwMaxBytesPerSec;
	DWORD  dwPaddingGranularity;	// pad to multiples of this size; normally 2K for cd-rom
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
	void print(){
		auxiliary::printFourCC("FOURCC",fcc);
		auxiliary::printSize("Size minus 8 bytes",auxiliary::getSizeAsInt(cb));
		auxiliary::printDW("MicroSecPerFrame",dwMicroSecPerFrame);
		auxiliary::printDW("MaxBytesPerSec",dwMaxBytesPerSec);
		auxiliary::printDW("PaddingGranularity",dwPaddingGranularity);
		auxiliary::printFlags(dwFlags);
		auxiliary::printDW("Total frames",dwTotalFrames);
		auxiliary::printDW("Initial frames",dwInitialFrames);

		auxiliary::printDW("Number of streams",dwStreams);
		auxiliary::printDW("Suggested Buffer Size",dwSuggestedBufferSize);
		auxiliary::printDW("Width",dwWidth);
		auxiliary::printDW("Height",dwHeight);

		float temp = dwMicroSecPerFrame * dwTotalFrames / 1000000;
		uint32_t min = temp / 60;
		//uint8_t sec = math::ciel(temp - (min * 60))m;
		uint8_t sec = (temp - (min * 60));

		printf("Running time %d min and %d sec.\n", min, sec);	
	}
}; 

#endif