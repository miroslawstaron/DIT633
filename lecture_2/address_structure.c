/*
* This file contains the example of the structure in C
* An address of a person
*/

#include <stdio.h>

#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1

// defining a struct, which we can do int two ways
// this is the way without using typedef
struct address {
    char lname[20];     // last name
    char fname[20];     // first name
    char *street;       // street address
    int age;            // age
};

// and this is the one with typedef
typedef struct {
    char lname[20];     // last name
    char fname[20];     // first name
    char *street;       // street address
    int age;            // age
} address_type;

typedef struct {
	char lname[20];     // last name
	char fname[20];     // first name
	int age;            // age
} address_type2;

/*
* This example shows how to instantiate the structures
* Please note that the one defined using typedef is used more naturally
* Just like any other type
*/
void address_example() {

    // declaring a variable of type address
    struct address addressInfo;
	addressInfo.street = NULL;              // initializing the variable with NULL will help us avoid problems later
    
    // since the field street is just a pointer, 
	// we need to allocate memory for it
    addressInfo.street = (char*) malloc(20 * sizeof(char));
    
    char* str = malloc(20);

	free(str);               // free the memory    

    // provide first and the last name
	printf("Please provide the first name #1: ");
	scanf("%s", addressInfo.fname);
	
	printf("Please provide the last name #1: ");
	scanf("%s", addressInfo.lname);
    
    // and fill it with the data, by asking the user
    printf("Provide the name of the street: ");
    scanf("%s", addressInfo.street);
	
    // print what we got
	printf("Street: %s\n", addressInfo.street);

    // now, let's do the same, but use the newly defined type
    address_type aInfo2; 

    // and let's copy the data for the street from the previous object
    // NOTE! This is a shallow copy so that the pointer is only being copied, 
    // not the actual data
    aInfo2.street = addressInfo.street;
    
    printf("Street #2: %s\n", aInfo2.street);

    // Let's create the third variable
    // that will point to the same place
    struct address aInfo3 = addressInfo;
	aInfo3.street = malloc(30 * sizeof(char));

    // the name of the street should be this one too
   printf("Street #3: %s\n", aInfo3.street);

    // and what happens if we change the name of the street in one of them?
    puts("Provide the new street for Info 3: ");
    
    scanf("%s", aInfo3.street);

    // and print the result
    printf("Address for the first variable: %s\n", addressInfo.street);
    printf("Address for the second variable: %s\n", aInfo2.street);
    printf("Address for the third variable: %s\n", aInfo3.street);

	free(addressInfo.street);
	free(aInfo3.street);

    // what we can see is that we the strings are copied using deep copy
    // that is because the memory is reserved for them when creating objects
    // and when we copy the objects, the memory is also copied
}