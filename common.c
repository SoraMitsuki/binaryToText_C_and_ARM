/**
 * DO NOT MODIFY THIS FILE. IT WILL NOT BE COLLECTED
 */

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "common.h"

const unsigned char MAPPING[] = {
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
   'w',
    'x',
    'y',
    'z',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    ' ',
    '\n',
    '.',
    ',',
    '!',
    '?',
    '\"',
    '\'',
    '\\',
    ';',
    ':',
    '[',
    ']',
    '=',
    '+',
    '-',
    '/',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '(',
    ')',
    0x09,
    0x0D
};

int REVERSE_MAPPING[CHAR_MAX];

void createReverseMapping(){
    // Fill the array with -1, to set the reverse mapping to -1 if the
    // character does not exist in the mapping
    memset(REVERSE_MAPPING, -1, CHAR_MAX*sizeof(int));

    // Set the value of the reverse mapping to the index of the character
    size_t i;
    for( i=0; i<MAPPED_CHARS; i++){
        REVERSE_MAPPING[MAPPING[i]] = i;
    }
}