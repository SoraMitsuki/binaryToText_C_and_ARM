/*
 * Name: Jiaqi Fan
 * PID: A12584051
 * UserID: SoraMitsuki
 *
 * Name: Xuanru Zhu
 * PID: 91064234
 * UserID: Aaron12138
 */
#include <stdio.h>
#include <stdlib.h>
#include "warmup.h"

unsigned int *char_freqs(FILE *fp){
   /* Your code goes here*/
  if(fp == NULL){
    return NULL;
  }
  int *array = malloc(MAX_CHAR * sizeof(int)); // malloc the space for array
  int index = fgetc(fp); //read the first char
  while(1){
    if(feof(fp)){ //check for the end of file
      break;
    }
    array[index] += 1; //increase the position
    index = fgetc(fp); //get the new index
    
  }
  fclose(fp); //close
  return array;
  
}
  

int reorder_bytes(int num){
   /* Your code goes here*/
  int mask = 0xFF; //create a mask
  int final = (num & mask) << 24; //get the last digit and put in the front
  mask <<= 8; // shift the mask
  final = ((num & mask) << 8) | final; // add on the second element
  mask <<= 8;
  final = ((num & mask) >> 8) | final; //repeat
  mask <<= 8;
  final = ((unsigned)(num & mask) >> 24) | final; //make it unsigned to prevent negative number
  return final;
  
}
