/*
 * Name: Jiaqi Fan
 * PID: A12584051
 * UserID: SoraMitsuki
 *
 * Name: Xuanru Zhu
 * PID: 91064234
 * UserID: Aaron12138
 */


/**
 * ALL FUNCTION IMPLEMENTATIONS AND HELPER FUNCTIONS FOR ENCODER WILL BE IN THIS FILE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "common.h"
#include "encoder.h"

/**
 *
 * This function takes a char c as input and returns a (6 character) array
 * that represents the 6 digit code for that character. This code is simply
 * the index of the char in the MAPPING array (represented in binary). 
 * You should use the REVERSE\_MAPPING array in this function to get 
 * the binary code for the character. REVERSE\_MAPPING array MUST be 
 * initialized with createReverseMapping(), prior to calling this function.
 *
 * @param c The input character to encode
 * @returns a six character array which encodes the index into ASCII binary
 */
char* encodeChar(char c){
  int size = 6; //make  size 6 which is the lenght of the array
  createReverseMapping(); //call createReverseMapping
  char * code = malloc(size); //malloc the size for pointer
  int index = REVERSE_MAPPING[c];  //store into the mapping
  int mask = 0x1;
  int temp = 0;
  int i = 0;
  for(i = (size - 1); i >= 0; i--){ //loop through the 6 character
    temp = mask & index;
    code[i] = temp + '0'; //store them 1 by 1 into array
    index >>= 1; 
  }
  return code; //return the array
}

/**
 * Takes a char c and int bit (should be either 0 or 1) and int index as input. 
 * Sets the bit at input index of c to be the input bit and returns the result.
 * The 0 index refers to the LSB, so for example, index 2 should 
 * set the 3rd least significant bit.
 * 
 * @param c the char to implant a bit into
 * @param bit the bit value to implant (0 or 1)
 * @param index the index to implant the bit into (0 is LSB)
 * @returns the char with bit b implanted into the input index
 */
char implantBit(char c, int bit, int index){
  int mask = 1; // make a mask 1
  bit <<= index; // shift the bit by index
  mask <<= index; // shift the mask
  mask = ~mask; // reverse the mask
  c = c & mask; // bit and to make bit clear
  c = c | bit; // put the bit in there
  return c;
}

/**
 * Takes a FILE handle in as input (corresponding to a regular ASCII
 * text file) and reads the file, char by char. Encodes each char into
 * a 6 character "binary" char array (by calling encodeChar).  The
 * resulting character arrays should be written to the output file
 * handle out
 *
 * @param in The input text file to read
 * @param out The output file, in ASCII encoded "binary"
 */
void textToBinary(FILE *in, FILE *out){
  int size = 6; // this is the size to write
  char * c; //make a array
  char read; // this is the char store the input read
  while(1){
    fread(&read, 1, 1, in); //read one byte each time
    if(feof(in)){
      break; //break when read all the input
    } 
    c = encodeChar(read); //convert the char into code
    fwrite(c, 1, size, out); //write 1 byte each and 6 one set in output file 
    free(c);
  }
}

/**
 * Takes a FILE handle in as input (corresponding to a
 * "binary" encoded file) and reads the file 1 char at a time. Each
 * char read will be an ASCII '0' or ASCII '1', and either 0 or 1 
 * will be implanted into randomized chars generated by rand()%256.
 *
 * If ASCII '0', then implant 0 into the bit at the input index 
 * of a randomized char . If ASCII '1', then implant 1 into the bit at 
 * the input index of the randomized char (by calling implantBit). 
 * Write the result into the output file handle out 
 * (Note: The least significant bit is in index 0)
 *
 * @param in The input file handle to read (ASCII encoded binary)
 * @param out The output file to write to
 * @param index the index of the bit where binary values should be implanted (0 is LSB)
 */
void binaryToCode(FILE *in, FILE *out, int index){
  srand(1); //DO NOT REMOVE OR EDIT THIS LINE OF CODE
  char random; // this char store the ramdon variable
  char c; // this char store the read input
  while(1){
    random = (char)rand()%256; //generate a random char
    fread(&c, 1, 1, in); // read from input
    if(feof(in)){
      break; //break when done reading
    }
    if(c == '0'){ //if the read input is 0 
      random = implantBit(random, 0, index); //write 0 into the random char at index position
    }
    else if(c == '1'){ //if it is 1
      random = implantBit(random, 1, index);
    }
    fwrite(&random, 1, 1, out); //write the new char into the output file
  } 
}

/**
 * Reads in a file from the specified input path and outputs a a binary encoding to
 * specified bin path and a fully encoded version to specified output path. 
 * This should simply open the necessary files and call the above helper 
 * functions in the correct sequence, and close the necessary files.
 *
 * @param input the path to the input file
 * @param bin the path to the encoded ASCII binary output file
 * @param output the path to the encoded output file 
 * @param index The index of the bit where binary values should be implanted (0 is LSB)
*/
void encodeFile(char* input, char* bin, char* output, int index){
  FILE *inFile, *binFile, *outFile; //create file for param
  inFile = fopen(input, "rb");
  binFile = fopen(bin, "wb");
  outFile = fopen(output, "wb");
  if(inFile == NULL || binFile == NULL || outFile == NULL){
    return; //do a null check for all the files
  }
  textToBinary(inFile, binFile); //call the testToBinary to convert
  fclose(inFile); // close the reading
  fclose(binFile);
  binFile = fopen(bin, "rb");  //open the bin and read the bin
  if(binFile == NULL){
    return;
  }
  binaryToCode(binFile, outFile, index); // call binaryToCode
  fclose(binFile); //close writer
  fclose(outFile);
}