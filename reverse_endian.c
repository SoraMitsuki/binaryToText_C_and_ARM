/*
 * Name: Jiaqi Fan
 * PID: A12584051
 * UserID: SoraMitsuki
 *
 * Name: Xuanru Zhu
 * PID: A91064234
 * UserID: Aaron12138
 */

#include <stdio.h>
#include <stdlib.h>
#include "warmup.h"

int main(int argc, char** argv){
     /* Your main code for reversing endian-ness goes here*/
  if(argc != 3){ // if argument is not 3 then return -1
    return -1;
  }
  FILE *inFile, *outFile;
  int nextInt;
  size_t size = 1;
  size_t count = 4;
  inFile = fopen(argv[1], "rb"); // open the iniule in read mode
  outFile = fopen(argv[2], "wb"); // open the outfile in write mode
  while(1){
    if(fread(&nextInt, size, count, inFile) != count) //read 1 byte each time and 4 times
      break;
    nextInt = reorder_bytes(nextInt); // call the reorder method 
    fwrite(&nextInt, size, count, outFile); // write to the file 
  }
  fclose(inFile); //close
  fclose(outFile);
}
