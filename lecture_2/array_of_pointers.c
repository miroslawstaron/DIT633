/*
* This file demonstrates array of pointers for the lecture
* Please note that we use function declaration here, but we do not use a header file
*/
#include <stdio.h>

#define MAX_ELEMENTS 4

// function declaration
void printlist(char* templist[]);

// and another one, we'll get back to it later
void printlist2(char* const templist[]);

/*
* Function demonstrating the printlist
*/
void demo_printlist(void) {

	// since we initialize the variable here, we could just skip "MAX_ELEMENTS" here
	// just to keep track and make sure we reserve the right amount of memory 
	// in all other references to the list
	char* list[MAX_ELEMENTS] = {"Peter", 
								"Kalle", 
								"Oskar", 
								"Sven"};		// declaration of the list of pointers, here pointers to strings

	// Call of function printlist())
	printlist2(list);

	// and one more
	printlist(list);

	// and the last one
	printlist2(list);
}

/*
* prints the elements of the list
* Note! the list is passed as a pointer
*/
void printlist(char* templist[]) {
	
	// in this loop we need the number of elements, 
	// otherwise we do not know when the elements end
	// using \0 is not an option, as we do not know how many strings we have
	for (int n = 0; n < MAX_ELEMENTS; n++) {
		puts(templist[n]);

		// now, what if we make a mistake here and overwrite the string
		templist[n] = "Playing tricks with pointers...";
	}
}

/*
* A better solution to the problem of just printing the list
* Using keyword const
*/
void printlist2(char* const templist[])
{
	// in this loop we need the number of elements, 
	// otherwise we do not know when the elements end
	// using \0 is not an option, as we do not know how many strings we have
	for (int n = 0; n < MAX_ELEMENTS; n++) {
		puts(templist[n]);

		// now, what if we make a mistake here and overwrite the string
		// templist[n] = "TEST";
		// templist = &s; 
	}
}