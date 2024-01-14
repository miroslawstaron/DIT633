/*
* This program demonstrates the use of pointers to the structures
* Note! There is a specific version of the pointer to dynamically allocated structures
*/
#include <stdio.h>

// definition of the structure of a person
// Note! I introduce the hungarian notation here
// You can find more information about it here: https://en.wikipedia.org/wiki/Hungarian_notation
typedef struct {
	int iAge;				// age of the person
	char strName[20];		// name of the person			
} sPerson;

typedef struct {
	int iAge;				// age of the person
	char strName[20];		// name of the person
	char strAddress[33];	// address
} sCompletePerson;

void dynamic_person_example()
{
	// declaring the variable
	sPerson* pPerson; 

	// now, we need to create the space in memory for that person
	pPerson = malloc(sizeof(sPerson));

	// let's print the person's name
	printf("Person's name is: %s", (*pPerson).strName);

	// Note! I use -> instead of (*pPerson).strName
	// the notation is equivalent
	printf("Person's name is: %s", pPerson->strName);

	// let's fill in the name with something useful
	puts("What's the name? ");
	gets(pPerson->strName, 20);

	printf("What's the age? ");
	scanf("%d", &pPerson->iAge);

	// version #2, which works, but can lead to severe errors!
	// this scanf will put the value into the first 32 bits of the struct pPerson
	// which happens to be age in our case
	// but it would not work if we had the name of the person first
	//
	// so, it is allowed, but do not use it
	//scanf("%d", pPerson);

	// and let's print the person's name
	printf("Person's name is: %s, and age: %d", pPerson->strName, pPerson->iAge);

	// and we free the memory after we are done with the person
	free(pPerson);
}

/*
* This function demonstrates the dynamic casting
* of places in memory, and getting only the parts of the struct
*/
void dynamic_person_casting()
{
	sCompletePerson* pPerson1;
	sPerson* pPerson1ShortVersion;

	pPerson1 = malloc(sizeof(sCompletePerson));

	// setting the name of the person
	// we need to use the strcpy as we need to copy between the stack ("Name") and the heap
	strcpy(pPerson1->strName, "Name");
	strcpy(pPerson1->strAddress, "Johnny's street 12");
	pPerson1->iAge = 21;

	printf("pPerson1: %s\n", pPerson1->strName);

	// now let's do casting
	pPerson1ShortVersion = (sPerson*)pPerson1;

	printf("pPersonShortVersion: %s\n", pPerson1ShortVersion->strName);
	char* pPointer = &pPerson1ShortVersion->strName[20];
	printf("pPersonShortVersion address: %s\n", pPointer);

	// Let's see how this looks like in memory
	// let's put a breakpoint on line 87 and add a watch

	// now, here we need to be very careful, as we only have one copy
	// of the person
	free(pPointer);
	

	// the following is legal and compile, but
	// will leave "strAddress" in the memory as pPerson1ShorterVersion 
	// does not have that field
	// free(pPerson1ShortVersion)

	// but this is not allowed
	// because the "common" part of the variable has already been freed
	// free(pPerson1); free(pPerson1ShortVersion); 
}