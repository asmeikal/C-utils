#include <MLUtils.h>

#include <stdlib.h>
#include <stdio.h>

void full_print(const char *msg, const size_t size)
{
	size_t i;
	for(i = 0; i < size; ++i) {
		if(((i) % 16) == 0) {
			fprintf(stderr, "\n");
			fprintf(stderr, "[%p] ", msg+i);
		}
		fprintf(stderr, "%02X ", (unsigned char) msg[i]);
		if(((i+1) % 4) == 0) {
			fprintf(stderr, " ");
		}
	}
	fprintf(stderr, "\n");
}

