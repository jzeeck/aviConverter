#include "main.h"

using namespace std;

int main(int argc, char const *argv[])
{

	if (argc < 2) {
		printf("No input file was given. Please specify an input file.\n");
		return 0;
	}

	ifstream infile(argv[1], ifstream::binary);

	if (infile) {
		printf("Started reading file.\n");
		LIST * header = new LIST[sizeof(LIST)];

		infile.seekg (0, infile.beg);
		infile.read ((char *)header, sizeof(LIST));
		if (!validateHeader(header)) {
			printf("Invalid AVI header. Corrupt file.\n");
		}
		#if DEBUG > 0
			printHeader(header);
		#endif

		infile.close();
		delete[] header;
	} else {
		printf("Could not open file %s!\n", argv[1]);
	}


	return 0;
}