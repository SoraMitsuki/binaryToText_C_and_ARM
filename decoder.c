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
 * ALL IMPLEMENTATIONS AND HELPER FUNCTIONS FOR DECODER WILL BE IN THIS FILE.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "decoder.h"
/**
 * Takes a char c and int index as input. 
 * Extracts the bit at the input index from the char c. The 0 index
 * refers to the LSB, so for example, index 2 should extract the 3rd
 * least significant bit.
 *
 * @param c the char to extract a bit from
 * @param index the index of the bit to extract
 * @returns the value of the bit at index in c
 */
int extractBit(char c, int index){
  int mask = 1; //make a mask
  int result = 0;
  mask <<= index;  // shife the mask by index
  result =(unsigned) (mask & c) >> index; // use bit and to obtain the bit
  return result;
}

/**
 * Takes a 6 character array b as input and returns the corresponding
 * char from MAPPING that is indexed by the binary ASCII string b.
 * For example, if b = "010101", then the char that is mapped to it is 
 * in MAPPING, index 1*16 + 1*4 + 1*1 = 21.
 *
 * @param b a pointer to a 6 character array, with ASCII '1's and '0's
 * @returns the corresponding character from MAPPING
 */
char decodeChar(char *b){
  int index = 0; 
  int compute = 0;
  int i = 0; //index for loop 
  int c = 0;  //use to count the power
  for(i = 5; i >= 0; i--){
    if(b[i] == '1'){ // if the position is 1 then do the multiplcation
      compute = 1 << c; // calculate the index
      index += compute;
    }
    c++;
  }
  return MAPPING[index];
}

/**
 * Takes a FILE handle in as input (corresponding to
 * an encoded file) and reads the file, char by char. The
 * bit at the input index of each char is extracted (by calling
 * extractBit). The least significant bit is in index 0.
 *
 * For each character, if the extracted bit is 0, output ASCII '0' to
 * the output file. If the extracted bit is 1, output ASCII
 * '1' to the output file.
 *
 * @param in the input file handle to read from
 * @param out the output file to write the extracted ASCII binary into
 * @param index the index of the bit to extract from each char
*/
void codeToBinary(FILE *in, FILE *out, int index){
  char read;
  char c = '0'; // temp variable need to write into output
  char j = '1';
  int extract;
  while(1){
    fread(&read, 1, 1, in); //read input file into read
    if(feof(in)){
      break;
    }
    extract = extractBit(read, index); //extract into bits
    if(extract == 0){
      fwrite(&c, 1, 1, out); // if the extracted bit is 0 write into output file
    }
    else if(extract == 1){
      fwrite(&j, 1, 1, out); // write 1 into output file
    }
  }
}

/**
 * Takes a FILE handle in as input (corresponding to a
 * "binary" decoded file) and reads the file, 6 chars at a
 * time. Each 6 chars (all ASCII 0's and 1's) should be read into a
 * char array and decoded into its corresponding char (by calling
 * decodeChar). The resulting chars would be output to the FILE handle
 * pointed to by out.
 *
 * @param in the input file, encoded as ASCII '1's and '0's
 * @Param out the decoded output file (ASCII)
 */

void binaryToText(FILE *in, FILE *out){
  int size = 6;
  char * array = malloc(size);
  char result;
  while(1){
    fread(array, 1, size, in); //read the inout file into array
    if(feof(in)){
      break;
    }
    result = decodeChar(array); //decode the array
    fwrite(&result, 1, 1, out);  //write into output file
  }
  free(array);
}

/**
 * Reads in a file from the specified input path and outputs a a binary decoding to
 * specified bin path and a fully decoded version to specified output path.
 * This should simply open the necessary files, call the above helper functions
 * in the correct sequence, and close the necessary files.
 *
 * @param input the path to the input file
 * @param bin the path to the decoded ASCII binary output file
 * @param output the path to the decoded output file
 * @param index The index of the bit from which binary values should be extracted
 */
void decodeFile(char* input, char* bin, char* output, int index){
  FILE *inFile, *binFile, *outFile;
  inFile = fopen(input, "r"); // open the infile in read mode
  binFile = fopen(bin, "wb"); // open in read + write mode
  outFile = fopen(output, "wb"); //open in read + write mode
  if(inFile == NULL || binFile == NULL || outFile == NULL){ 
    return; //do a null check for the files
  }
  codeToBinary(inFile, binFile, index); //call code to binary
  fclose(inFile);
  fclose(binFile);
  binFile = fopen(bin, "rb");
  if(binFile == NULL){  //check the binfile is null or not
    return;
  }
//rewind(binFile);
//fseek(binFile, 0, SEEK_SET);
  binaryToText(binFile, outFile); //call binary to text
  fclose(binFile); //close all files
  fclose(outFile); 
}
