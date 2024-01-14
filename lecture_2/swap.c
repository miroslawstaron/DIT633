// here we include the declarations
// in the strict sense, this is not needed in this program
// as we only have one function
// but if we had many, then we do not have to worry about 
// keeping track which function is declared where
#include "function_declaration.h"
#include <stdio.h>


/*
* Here is the definition of the function
* Note! both parameters are ints
*/
int swap_int(int left, int right)
{
	int temp;	// temporary variable

	// here is where the swapping takes place
	temp = left;
	left = right;
	right = temp;

	// we return the left variable just for fun
	return left;
}

/*
* Here is the definition of the function
* Note! both parameters are pointers
* Otherwise the swap will not work!
*/
int swap(int *left, int* right)
{
	unsigned char one_byte = 0x10; 
	one_byte++;

	int temp;	// temporary variable

	printf("Address value: %d\n", left);

	// here is where the swapping takes place
	temp = *left;
	*left = *right;
	*right = temp;

	// we return the left variable just for fun
	return *left;
}

/*
* This function demostrates swapping between two variables
* Note! this uses pointers
*/
void swap_example()
{
	int a = 12; // left for swapping
	int b = 13; // right for swapping

	int c = a;
	int d = b;

	swap(&a, &b);
	printf("a: %d, b: %d\n", a, b);

	char *pX = malloc(10 * sizeof(char)); 
	
	printf("The value of pX is: %d\n", pX);
	printf("The value of pX is: %d\n", (char *)pX);
	
	
	// *pX = (char*)malloc(10 * sizeof(char));

	// this is a pointer to a function
	// that function takes two arguments int *
	// and returns an integer

	// int swap(int* left, int* right)
	int (*foo)(int*, int*);
	
	// this is a very different than the line above
	// because it means that foo is a function that takes two pointers as arguments
	// and returns a pointer to an int
	// int* foo(int*, int*);

	// now, let's assign that pointer to swap 
	// note the signature
	foo = &swap;

	pX = foo; 

	// note that we use pointers, which are passed by value
	// the values of the pointers point to the place in memory (stack)
	// where a and b are stored
	int rSwap = foo(&a, &b);

	char result = *((char*)foo);

	printf("pX: %c\n", result);

	// print variables
	printf("Left: %d, right: %d\n", a, b);

	int lSwap = swap(&c, &d);

	printf("Left: %d, right: %d\n", a, b);
}

