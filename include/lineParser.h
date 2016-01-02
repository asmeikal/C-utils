#ifndef lineParser_h
#define lineParser_h

/*!
	@header File Line Parser
	@abstract
		Functions to get lines from files.
 
	@author Michele Laurenti
	@language c
 */

#include <stdio.h>
#include <stdlib.h>

/*!
	@function fileGetLine
	@abstract
		Fetches the next line from [fd], without the need to specify its length.
	@warning 
		The pointer returned must be manually freed.

	@param fd
		A valid file descriptor.
	@return
		A pointer to a string containing the next line of [fd].
 */
char *fileGetLine(FILE *fd);

/*!
	@function parseLines
	@abstract
		Opens and reads [file] and returns a vector of strings, one for each line of the file, in order.
	@warning
		The vector returned should be manually freed with Vector_free.
	@param file
		The name of the file to open.
 */
char **parseLines(const char * const file);


#endif /* lineParser_h */
