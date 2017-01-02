//
// Created by michele on 7/23/16.
//

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct sorted_array SortedArray;

typedef int (CompareFunction)(const void * const ep_1, const void * const ep_2);

typedef void (fPrintFunction)(const void * const elem_p, FILE * fp);

SortedArray * SortedArray_new(size_t elemSize, fPrintFunction *fprintElem, CompareFunction * compare);

unsigned int SortedArray_length(SortedArray * this);

int SortedArray_add(SortedArray * this, const void * elem);

bool SortedArray_contains(SortedArray * this, const void * elem);

void * SortedArray_get(SortedArray * this, unsigned int i, void * value);

// TODO this function's name sucks, change it
void * SortedArray_getById(SortedArray * this, const void * const elem);

void SortedArray_fprint(SortedArray * this, FILE * fp);

void SortedArray_free(SortedArray ** thisP);

#ifdef __cplusplus
};
#endif

