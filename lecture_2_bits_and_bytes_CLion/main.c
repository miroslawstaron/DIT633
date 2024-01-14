#include <stdio.h>

/*
 * This program demonstrates how to work with bits and bytes in DIT632.
 * The goal is to demonstrate how we can do bit arithmetic and what bits are bytes are
 *
 * For this demo, we will need the following:
 * - understand what #define preprocessor directive does - from lecture 1
 * - know what a bit and a byte are - from the Java programming course
 * - know how to use formatting strings for printf - from lecture 1
 * - know that everything in C start from 0, not from 1
 * - a good thing is to have the ASCII table at hand: https://www.asciitable.com/
 *
 * (c) Miroslaw Staron, 2022
 * DIT632, Lecture 2
 */

/*
 * Basics:
 * 1 byte = 8 bits
 * We usually use hexadecimal numbers for bytes and binary for bits
 * we denote a hexadecimal number by writing 0x before the number,
 * for example:
 *      0x00 == decimal 0
 *      0x01 == decimal 1
 *      0x0A == decimal 10
 *      0x10 == decimal 16
 *
 * we use 0b to denote binary numbers,
 * for example:
 *      0b00000000 == decimal 0
 *      0b00000001 == decimal 1
 *
 * 0x00 == 0 0 0 0 0 0 0 0 == 0b00000000 == decimal 0
 * 0x01 == 0 0 0 0 0 0 0 1 == 0b00000001 == decimal 1
 * 0x02 == 0 0 0 0 0 0 1 0 == 0b00000010 == decimal 2
 * 0x0F == 0 0 0 0 1 1 1 1 == 0b00001111 == decimal 15
 */

// bit1 is the value of the first bit in a byte
// the first bit is the same as 2^0= 1 - two to the power of zero (first bit)
// this value is sometimes called a mask
// a mask can be used to check if a particular bit is set
// a bit is set if its value == 1
#define bit1 1

// bit2 is the value of the second bit
// the value is 2 = 2^1 - two to the power of 1 (second bit)
#define bit2 2

// bit3 is the value of the third bit
// the value is 2^2 = 4
#define bit3 4
#define bit4 8
#define bit5 16
#define bit6 32
#define bit7 64
#define bit8 128

// to make things easier, let's define our own type
// here, we defined a new type - byte
// that type is the same as unsigned char
typedef unsigned char byte;

// we could also do it more "brute force" using define
// #define byte unsigned char


/**
 * Main function for the program.
 * @param argc - number of program arguments
 * @param argv - array of strings with program arguments, idexed from 0
 * @returns - 0 if ok, positive integer if there is an error code
 */
int main(int argc, char * argv[]) {

    // Hello world!
    // a good practice is to print something at the beginning of the program
    // so that we know that we start.
    printf("Welcome to the binary numbers demonstration! \n");

    // there is no bit or byte type in C
    // We use char as the type for one byte, for example
    // please note that I am using keyword "unsigned" here
    // this means that I want the compiler to treat this variable
    // as pure byte, not in U2 binary conding system
    unsigned char one_byte;

    // when we assign the value, however, we need to convert the type
    // for example like this:
    one_byte = (char) 20;

    // we can also print it directly as a value
    // please note that we use %d as the formatting string here
    printf("This is the value of one_byte %d\n", one_byte);

    // TODO: change that to %c and see what happens

    // decimal 20 == 0x14 == 0b00010100
    // this means that bit 3 should be set to 1
    // and bit number 5 should be set to 1
    // so, let's check if that is the case
    unsigned char another_byte = 0b00010100;

    // let's check if that is the case
    if (one_byte == another_byte)
        printf("Comparing bytes: Both bytes have the same number! \n");

    // Let's do the same with the #define
    if (one_byte == (bit3 + bit5))
        printf("Comparing a byte to two bits: Both bytes have the same number! \n");

    // now, about bit masking
    // the expression in this statement
    // means that we check whether one_byte has bits 3 and 5 set to 1
    // and all the rest of the bits set to 0
    if (one_byte == (bit3 | bit5))
        printf("Comparing a byte to a mask: Both bytes have the same number! \n");

    // so, if we can mask a bit, we can also set it, right?
    unsigned char bit_8_is_set = 0b00000000 | bit8;

    // let's see what we get:
    printf("Value of the 8th bit is: %d\n", bit_8_is_set);

    // we can also un-set it == clear it
    unsigned char bit_8_is_not_set = 0b11111111 & ~bit8;

    // let's see what we get:
    printf("Value of the 8th bit cleared is: %d\n", bit_8_is_not_set);

    // Finally, let's shift some bits around in a byte
    // let's say we have number 1
    // let's use hexadecimal notation to make it more interesting
    byte number_one = 0x01; // == 0b00000001

    // let's see what we get:
    printf("Value of number_one is: %d\n", number_one);

    // now, let's shift the bits of that number to the left
    number_one = number_one << 1;

    // let's see what we get:
    // 0b00000001 << 1 == 0b00000010
    printf("Value of number_one after shifting bits is: %d\n", number_one);

    // let's do that one more time:
    // 0b00000010 << 1 == 0b00000100
    number_one = number_one << 1;

    // let's see what we get:
    printf("Value of number_one after shifting bits one more time is: %d\n", number_one);

    // how about we shift it 6 bits to the left
    // we should get: 0b00000100 << 6 = 0b100000000
    number_one = number_one << 6;

    // let's see what we get
    printf("Value of number_one after shifting 6 more bits is: %d\n", number_one);

    // wrong, we get 0....


    // printf to say goodbye
    printf("%s\n", "That's all for this demo, thank you for watching!");

    // return 0 == correct execution
    // since we do not have any fail safety (no user input)
    // then we do not have any other option - if the code compiles then it executes
    return 0;
}
