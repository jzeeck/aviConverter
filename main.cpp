#include "main.h"

using namespace std;

LIST * header = new LIST[sizeof(LIST)];
LIST * firstListHeader = new LIST[sizeof(LIST)];
AVIMAINHEADER * aviHeader = new AVIMAINHEADER[sizeof(AVIMAINHEADER)];


void readAviHeader (ifstream & infile) {
	printf("Reading AVI header.\n");
	infile.read ((char *)aviHeader, sizeof(AVIMAINHEADER));

	aviHeader->print();

	printf("\n");
}

bool readFileHeader(ifstream & infile) {
	printf("Started reading file.\n");
	infile.seekg (0, infile.beg);
	infile.read ((char *)header, sizeof(LIST));
	if (!validateHeader(header)) {
			printf("Invalid AVI header. Corrupt file.\n");
			return false;
	}
	#if DEBUG > 0
			printHeader(header);
	#endif
	printf("\n");

	return true;

}

int main(int argc, char const *argv[])
{

	if (argc < 2) {
		printf("No input file was given. Please specify an input file.\n");
		return 0;
	}

	ifstream infile(argv[1], ifstream::binary);

	if (infile) {

		if(!readFileHeader(infile))
			return 0;
		//So here we should start reading the avi file.
		//read the first list
		infile.read ((char *)firstListHeader, sizeof(LIST));
		#if DEBUG > 0
			printList(firstListHeader);
			printf("\n");
		#endif
		readAviHeader(infile);
			


		infile.close();
		delete[] header;
	} else {
		printf("Could not open file %s!\n", argv[1]);
	}


	return 0;
}