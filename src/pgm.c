
#include <stdio.h>
#include <stdlib.h>

#include <LineParser.h>
#include <Vector.h>

#include <Debug.h>
#include <StringUtils.h>

#define DEBUG_PGM	"pgm"

/*!
 * @function pgm_load
 * Loads the pgm image at [filename] into a [width] x [height] unsigned char matrix,
 * and stores the pointer into [img].
 * @param img
 * A pointer to an unsigned char pointer where the image will be stored.
 * @param height
 * A pointer to an int where the n of rows of the image will be stored.
 * @param width
 * A pointer to an int where the n of cols of the image will be stored.
 * @param filename
 * The name of the file to be read.
 * @return
 * 0 on success, non-0 on failure.
 */
int pgm_load(unsigned char ** const img, int * const height, int * const width, const char * const filename)
{
	const char * const fname = "pgm_load";
	if (NULL == img) {
		Debug_out(DEBUG_PGM, "%s: NULL pointer argument.\n", fname);
		goto error1;
	}
	char **lines = parseLines(filename);
	int i = 0, j;
	int l_width, l_height;
	unsigned int tmp;
	/* parse all file lines */
	if (NULL == lines) {
		Debug_out(DEBUG_PGM, "%s: unable to read file '%s'.\n", fname, filename);
		goto error1;
	}
	/* check that first line says P2 */
	if (NULL == lines[i]) {
		Debug_out(DEBUG_PGM, "%s: image ended too early.\n", fname);
		goto error2;
	}
	if (!StringUtils_startsWith(lines[i], "P2")) {
		Debug_out(DEBUG_PGM, "%s: illegal image start: %s.\n", fname, lines[i]);
		goto error2;
	}
	++i;
	/* skip all comment lines */
	while ((NULL != lines[i]) && (StringUtils_startsWith(lines[i], "#"))) {
		/* Comment line */
		Debug_out(DEBUG_PGM, "%s: %s.\n", fname, lines[i]);
		++i;
	}
	if (NULL == lines[i]) {
		Debug_out(DEBUG_PGM, "%s: image ended too early.\n", fname);
		goto error2;
	}
	/* parse width and height */
	if (2 != sscanf(lines[i], "%d %d", &l_width, &l_height)) {
		Debug_out(DEBUG_PGM, "%s: error scanning line %d: %s.\n", fname, i, lines[i]);
		goto error2;
	}
	Debug_out(DEBUG_PGM, "%s: image size is %d x %d.\n", fname, l_width, l_height);
	++i;
	if (NULL == lines[i]) {
		Debug_out(DEBUG_PGM, "%s: image ended too early.\n", fname);
		goto error2;
	}
	/* skip image max value */
	Debug_out(DEBUG_PGM, "%s: image max value is %s.\n", fname, lines[i]);
	++i;
	if (NULL == lines[i]) {
		Debug_out(DEBUG_PGM, "%s: image ended too early.\n", fname);
		goto error2;
	}
	/* allocate image and parse it */
	*img = calloc(l_width * l_height, sizeof(unsigned char));
	if (NULL == img) {
		Debug_out(DEBUG_PGM, "%s: calloc failed.\n", fname);
		goto error2;
	}
	Debug_out(DEBUG_PGM, "%s: Result image buffer allocated.\n", fname);
	for (j = 0; j < l_width * l_height; ++j) {
		if (NULL == lines[i+j]) {
			Debug_out(DEBUG_PGM, "%s: image ended too early.\n", fname);
			goto error3;
		} else if (1 != sscanf(lines[i+j], "%u", &tmp)) {
			Debug_out(DEBUG_PGM, "%s: error scanning line %d: %s.\n", fname, i+j, lines[i+j]);
			goto error3;
		}
		Debug_out(DEBUG_PGM, "%s: Pixel %d is %d.\n", fname, j, tmp);
		(*img)[j] = tmp;
	}
	/* save width and height, and free parsed lines */
	if (NULL != width) {
		*width = l_width;
	}
	if (NULL != height) {
		*height = l_height;
	}
	Vector_free((void **) lines);
	return 0;

error3:
	free(img);
error2:
	Vector_free((void **) lines);
error1:
	return 1;
}

/*!
 * @function pgm_save
 * Saves the buffer at [img], with size [width] x [height], as a pgm image at [filename].
 * @param img
 * The buffer to be saved
 * @param height
 * The height of the image.
 * @param width
 * The width of the image.
 * @param filename
 * The name of the file where the image will be saved.
 * @return
 * 0 on success, non-0 on failure.
 */
int pgm_save(const unsigned char * const img, const int height, const int width, const char * const filename)
{
	const char * const fname = "pgm_save";
	int i;
	/* open file */
	FILE *fp = fopen(filename, "w");
	if (NULL == fp) {
		Debug_out(DEBUG_PGM, "%s: unable to open file '%s'.\n", fname, filename);
		goto error1;
	}
	/* write out */
	if (0 > fprintf(fp, "P2\n")) {
		Debug_out(DEBUG_PGM, "%s: fprintf failed.\n", fname);
		goto error2;
	}
	if (0 > fprintf(fp, "# made with mlutils :-)\n")) {
		Debug_out(DEBUG_PGM, "%s: fprintf failed.\n", fname);
		goto error2;
	}
	if (0 > fprintf(fp, "%d %d\n", width, height)) {
		Debug_out(DEBUG_PGM, "%s: fprintf failed.\n", fname);
		goto error2;
	}
	if (0 > fprintf(fp, "255\n")) {
		Debug_out(DEBUG_PGM, "%s: fprintf failed.\n", fname);
		goto error2;
	}
	for (i = 0; i < height * width; ++i) {
		if (0 > fprintf(fp, "%u\n", img[i])) {
			Debug_out(DEBUG_PGM, "%s: fprintf failed.\n", fname);
			goto error2;
		}
	}

	fclose(fp);
	return 0;

error2:
	fclose(fp);
error1:
	return 1;
}

