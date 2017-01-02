#include <SortedArray.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#include <float.h>
#include <math.h>

#include <Debug.h>
#include <Array.h>
#include <RndGen.h>

#define MID_POINT(x, y)			(((x) + (y)) / 2)

#define DEFAULT_CAPACITY		4
#define DEFAULT_CAPACITY_INCREMENT	4

struct sorted_array
{
	Array * array;
	CompareFunction * compare;
};

unsigned int SortedArray_insertionPoint(SortedArray * this, const void * elem);

/* function definition */

SortedArray * SortedArray_new(size_t elemSize, fPrintFunction *fprintElem, CompareFunction * compare)
{
	const char * const fname = "SortedArray_new";

	Debug_assert(DEBUG_ALWAYS, NULL != compare, "%s: NULL == compare\n", fname);

	SortedArray * new = NULL;

	new = calloc(1, sizeof(*new));
	Debug_assert(DEBUG_ALWAYS, NULL != new, "%s: NULL == new\n", fname);

	new->array = Array_new(DEFAULT_CAPACITY, elemSize, DEFAULT_CAPACITY_INCREMENT, fprintElem, compare);
	Debug_assert(DEBUG_ALWAYS, NULL != new->array, "%s: NULL == new->array\n", fname);

	new->compare = compare;

	return new;
}

unsigned int SortedArray_insertionPoint(SortedArray * this, const void * elem)
{
	const char * const fname = "SortedArray_binarySearch";

	Debug_assert(DEBUG_ALWAYS, NULL != this, "%s: NULL == this\n", fname);
	Debug_assert(DEBUG_ALWAYS, NULL != elem, "%s: NULL == elem\n", fname);

	unsigned int lower = 0;
	unsigned int upper = Array_length(this->array);
	unsigned int mid = MID_POINT(lower, upper);

	const void * elem_p = NULL;
	int cmp = -1;

	while (lower < upper) {
		elem_p = Array_elemPtr(this->array, mid);
		cmp = this->compare(elem, elem_p);
		if (0 == cmp) {
			break;
		} else if (0 < cmp) {
			lower = mid + 1;
		} else {
			upper = mid;
		}
		mid = MID_POINT(lower, upper);
	}

	return mid;
}

bool SortedArray_contains(SortedArray * this, const void * elem)
{
	const char * const fname = "SortedArray_contains";

	Debug_assert(DEBUG_ALWAYS, NULL != this, "%s: NULL == this\n", fname);
	Debug_assert(DEBUG_ALWAYS, NULL != elem, "%s: NULL == elem\n", fname);

	unsigned int i = SortedArray_insertionPoint(this, elem);
	Debug_out(DEBUG_ALWAYS, "%s: insertion point is %" PRIu32 "\n", fname, i);

	if (i >= Array_length(this->array)) {
		Debug_out(DEBUG_ALWAYS, "%s: insertion point is beyond array bounds\n", fname);
		return false;
	} else {
		const void * elem_p = Array_elemPtr(this->array, i);
		Debug_out(DEBUG_ALWAYS, "%s: retrieved element at %p\n", fname, elem_p);

		return this->compare(elem, elem_p) == 0 ? true : false;
	}
}

int SortedArray_add(SortedArray * this, const void * elem)
{
	const char * const fname = "SortedArray_add";

	Debug_assert(DEBUG_ALWAYS, NULL != this, "%s: NULL == this\n", fname);
	Debug_assert(DEBUG_ALWAYS, NULL != elem, "%s: NULL == elem\n", fname);

	unsigned int i = SortedArray_insertionPoint(this, elem);

	const void * elem_p = Array_elemPtr(this->array, i);

	if (i >= Array_length(this->array)) {
		Array_add(this->array, elem);
		return 2;
	} else {
		if (0 == this->compare(elem, elem_p)) {
			return 0;
		} else {
			Array_add(this->array, elem);
			for (unsigned int j = Array_length(this->array) - 1; j > i; --j) {
				Array_swap(this->array, j, j-1);
			}
			return 1;
		}
	}
}

void SortedArray_free(SortedArray ** thisP)
{
	if (NULL == thisP) return;
	SortedArray * this = *thisP;
	if (NULL == this) return;
	Array_free(&(this->array));
	free(this);
	*thisP = NULL;
}

void SortedArray_fprint(SortedArray * this, FILE * fp)
{
	const char * const fname = "SortedArray_fprint";
	Debug_assert(DEBUG_ALWAYS, NULL != this, "%s: NULL == this\n", fname);
	Array_fprint(this->array, fp);
}
unsigned int SortedArray_length(SortedArray * this)
{
	const char * const fname = "SortedArray_length";
	Debug_assert(DEBUG_ALWAYS, NULL != this, "%s: NULL == this\n", fname);
	return Array_length(this->array);
}

void * SortedArray_get(SortedArray * this, unsigned int i, void * value)
{
	const char * const fname = "SortedArray_get";
	Debug_assert(DEBUG_ALWAYS, NULL != this, "%s: NULL == this\n", fname);
	return Array_get(this->array, i, value);
}

void * SortedArray_getById(SortedArray * this, const void * const elem)
{
	const char * const fname = "SortedArray_getById";

	Debug_assert(DEBUG_ALWAYS, NULL != this, "%s: NULL == this\n", fname);
	Debug_assert(DEBUG_ALWAYS, NULL != elem, "%s: NULL == elem\n", fname);

	unsigned int i = SortedArray_insertionPoint(this, elem);
	Debug_out(DEBUG_ALWAYS, "%s: insertion point is %" PRIu32 "\n", fname, i);

	if (i >= Array_length(this->array)) {
		Debug_out(DEBUG_ALWAYS, "%s: insertion point is beyond array bounds\n", fname);
		return NULL;
	} else {
		const void * elem_p = Array_elemPtr(this->array, i);
		Debug_assert(DEBUG_ALWAYS, NULL != elem_p, "%s: NULL == elem_p\n", fname);
		int cmp = this->compare(elem, elem_p);

		if (0 == cmp) {
			void * result = NULL;
			Array_get(this->array, i, &result);
			return result;
		} else {
			return NULL;
		}
	}
}
