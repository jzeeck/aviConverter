#ifndef PRINTER__HEADER
#define PRINTER__HEADER

#include "aviTypes.h"
#include <iostream>


bool validateHeader(LIST*);
void printHeader(LIST*);
bool validateList(LIST*);
void printList(LIST*);


void printHeader(LIST * header) {
	if (validateHeader(header))
	{
		printf("Header is valid AVI header.\n");
		LIST object = *header;
		object.print();
		return;
	}
	printf("Header is not a valid AVI header.\n");
}

void printList(LIST * header) {
	if (validateList(header))
	{
		printf("Header is valid LIST header.\n");
		LIST object = *header;
		object.print();
		return;
	}
	printf("Header is not a valid LIST header.\n");
}
bool validateList(LIST * header) {
	LIST object = *header;
	if(object.dwList != VALID_LIST_HEADER) {
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

#endif