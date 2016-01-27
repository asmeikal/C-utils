#ifndef __PGM_H
#define __PGM_H

int pgm_load(unsigned char ** const img, int * const height, int * const width, const char * const filename);
int pgm_save(const unsigned char * const img, const int height, const int width, const char * const filename);

#endif

