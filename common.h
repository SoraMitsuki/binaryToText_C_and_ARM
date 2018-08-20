/**
 * DO NOT MODIFY THIS FILE. IT WILL NOT BE COLLECTED
 */

#pragma once

extern const unsigned char MAPPING[];
extern int REVERSE_MAPPING[];

/**
 * Creates a mapping from the character table MAPPING to integer
 * indices. Useful for the encoder phase. Call this once to initialize
 * the reverse mapping, which can be accessed in the global variable
 * REVERSE_MAPPING.
 */
void createReverseMapping();

#define MAPPED_CHARS 64