//
//  lineParser_test.c
//  openCL
//
//  Created by Michele Laurenti on 21/12/15.
//
//

#include <LineParser.h>
#include <Vector.h>

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char **lines;
	/* non existent file */
	printf("Provo con file non esistente.\n");
	lines = parseLines("lineParser_files/nonesiste.txt");
	if (NULL != lines) {
		printf("Il file non dovrebbe esistere.\n");
		Vector_printString((void **) lines);
		return EXIT_FAILURE;
	}
	Vector_free((void **) lines);
	printf("\n");

	/* file with line longer that 256 */
//	printf("Provo con file con riga troppo lunga.\n");
//	lines = parseLines("lineParser_files/longlines.txt");
//	if (NULL != lines) {
//		printf("La riga dovrebbe essere troppo lunga!\n");
//		printLines(lines);
//		return EXIT_FAILURE;
//	}
//	Vector_free(lines);
//	printf("\n");

	/* empty file */
	printf("Provo con file vuoto.\n");
	lines = parseLines("lineParser_files/vuoto.txt");
	if (NULL == lines) {
		printf("Errore apertura.\n");
		return EXIT_FAILURE;
	}
	printf("We have %d lines!\n", Vector_length((void **) lines));
	Vector_printString((void **) lines);
	Vector_free((void **) lines);
	printf("\n");

	/* huge file */
//	printf("Provo con file enorme.\n");
//	lines = parseLines("lineParser_files/huge.txt");
//	if (NULL == lines) {
//		printf("Errore apertura.\n");
//		return EXIT_FAILURE;
//	}
//	printf("We have %d lines!\n", Vector_length((void **) lines));
//	//printLines(lines);
//	Vector_free((void **) lines);
//	printf("\n");

	/* normal file */
	printf("Provo con file sciallo.\n");
	lines = parseLines("lineParser_files/prova.txt");
	if (NULL == lines) {
		printf("Errore apertura.\n");
		return EXIT_FAILURE;
	}
	printf("We have %d lines!\n", Vector_length((void **) lines));
	Vector_printString((void **) lines);
	Vector_free((void **) lines);
	printf("\n");

	return 0;
}
