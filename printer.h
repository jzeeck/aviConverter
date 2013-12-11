#include "aviTypes.h"
#include <iostream>


bool validateHeader(LIST*);
bool printHeader(LIST*);


bool printHeader(LIST * header) {
	if (validateHeader(header))
	{
		printf("Header is valid AVI header.\n");
		LIST object = *header;
		object.print();
		return false;
	}

	return true;
}

bool validateHeader(LIST * header) {
	LIST object = *header;
	if(object.dwList != VALID_AVI_START_HEADER) {
		return false;
	}

	return true;
}
