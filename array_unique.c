/**
 * @file array_unique.c
 */

#include <stdlib.h>
#include "array_unique.h"


int array_unique_init(struct array_unique* array, size_t n)
{
	array->data = calloc(n, sizeof(uint64_t));
	array->size = 0ul;
	array->nalloc = n;
	return 0;
}

void array_unique_destroy(struct array_unique* array)
{
	free(array->data);
	array->data = NULL;
	array->size = 0ul;
	array->nalloc = 0ul;
}

size_t array_unique_size(struct array_unique* array)
{
	return array->size;
}

int array_unique_push(struct array_unique* array, uint64_t i64)
{
	return 0;
}

int array_unique_erase(struct array_unique* array, uint64_t i64)
{
	return 0;
}
