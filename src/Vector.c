/**
 * @file
 * @author Michele Laurenti
 * @language c
 */

#include "Vector.h"

#include <Debug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define DEBUG_VECTOR	"Vector_utilities"

/**
 * @function Vector_free
 */
void Vector_free(void **vector)
{
	const char * const fname = "Vector_free";
	if (NULL != vector) {
		void **start = vector;
		while (NULL != *vector) {
			free(*vector);
			++vector;
		}
		free(start);
	} else {
		Debug_out(DEBUG_VECTOR, "%s: NULL pointer argument.\n", fname);
	}
}

/**
 * @function Vector_length
 */
int Vector_length(void **vector)
{
	const char * const fname = "Vector_length";
	if (NULL != vector) {
		int len = 0;
		while (NULL != *vector) {
			++len;
			++vector;
		}
		return len;
	} else {
		Debug_out(DEBUG_VECTOR, "%s: NULL pointer argument.\n", fname);
		return -1;
	}
}

/**
 * @function Vector_printString
 */
void Vector_printString(void **vector)
{
	const char * const fname = "Vector_printString";
	if (NULL != vector) {
		int i = 0, j;
		j = ((int) log10(Vector_length(vector))) + 2;
		printf("\n");
		while (NULL != *vector) {
			++i;
			printf("%-*d|\t%s", j, i, (char *) *vector);
			++vector;
		}
		printf("\n");
	} else {
		Debug_out(DEBUG_VECTOR, "%s: NULL pointer argument.\n", fname);
	}
}

