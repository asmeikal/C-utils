//
//  lineParser.h
//  openCL
//
//  Created by Michele Laurenti on 21/12/15.
//
//

#ifndef lineParser_h
#define lineParser_h


char **parseLines(const char * const file);
void freeLines(char **lines);
void printLines(char **lines);
int countLines(char **lines);


#endif /* lineParser_h */
