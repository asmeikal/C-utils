/**
 * @file
 * @author Michele Laurenti
 * @language c
 */

#include <LineParser.h>
#include <Vector.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include <Debug.h>
#include <StringUtils.h>

#define STRING_SIZE	256
#define LINES_DEFAULT	16
#define LINES_INCREASE	16

#define DEBUG		"lineParser"

/*!
 * @function fileGetLine
 * Returns a pointer to the next line from [fd], or NULL if no more lines
 * are available. The char pointer returned must be manually freed.
 * @param fd
 * The file descriptor from which to read.
 * @return
 * A pointer to a newly allocated string containing the next line of [fd],
 * or NULL.
 */
char *fileGetLine(FILE *fd)
{
	const char * const fname = "fileGetLine";
	char *result, *result_tmp, *ret;
	int size = STRING_SIZE;
	int done;

	result = calloc(size, 1);
	if (NULL == result) {
		Debug_out(DEBUG, "%s: calloc failed.\n", fname);
		return NULL;
	}
	do {

		ret = fgets(result+strlen(result), size-strlen(result), fd);
		if (NULL == ret) {
			free(result);
			if (0 == feof(fd)) {
				Debug_out(DEBUG, "%s: fgets failed.\n", fname);
			}
			return NULL;
		}

		done = StringUtils_endsWith(result, "\n");
		if (!done) {
			Debug_out(DEBUG, "%s: expanding string.\n", fname);
			result_tmp = calloc(size*2, 1);
			if (NULL == result_tmp) {
				Debug_out(DEBUG, "%s: calloc failed.\n", fname);
				free(result);
				return NULL;
			}
			memcpy(result_tmp, result, strlen(result));
			free(result);
			result = result_tmp;
			size = size * 2;
		}
	} while (!done);

	ret = StringUtils_clone(result);
	if (NULL == ret) {
		Debug_out(DEBUG, "%s: StringUtils_clone failed.\n", fname);
		free(result);
		return NULL;
	}
	free(result);
	result = ret;

	Debug_out(DEBUG, "%s", result);

	return result;
}

/*!
 * @function parseLines
 * Opens [file] and reads all lines from it, returning a pointer to a NULL-terminated
 * vector of strings (char pointers), each containing a line. The vector can be freed
 * with Vector_free from Vector.h
 * @param file
 * The filename of the file to be read.
 * @return
 * A pointer to a NULL-terminated vecotr of char pointers, each containing a line, or
 * NULL on failure.
 */
char **parseLines(const char * const file)
{
	const char * const fname = "newParseLine";
	FILE *fd;
	char *line, **result;
	Array *lines;

	/* open file */
	fd = fopen(file, "r");
	if (NULL == fd) {
		Debug_out(DEBUG, "%s: '%s': %s.\n", fname, file, strerror(errno));
		goto error;
	}

	/* create array */
	lines = Array_newString(LINES_DEFAULT, LINES_INCREASE);
	if (NULL == lines) {
		Debug_out(DEBUG, "%s: unable to create new Array.\n", fname);
		goto clean1;
	}

	/* read the file */
	do {
		line = fileGetLine(fd);
		if (NULL != line) {
			Array_add(lines, &line);
		}
	} while (NULL != line);

	/* convert array to vector of (char *) */
	int size = Array_length(lines);
	result = calloc(size+1, sizeof(char *));
	if (NULL == result) {
		Debug_out(DEBUG, "%s: calloc failed.\n", fname);
		goto clean2;
	}
	memcpy(result, Array_as_C_array(lines), size * sizeof(char *));
	result[size] = NULL;
	Array_free(&lines);
	fclose(fd);
	return result;

clean2:	Array_free(&lines);
clean1:	fclose(fd);
error:	return NULL;
}

