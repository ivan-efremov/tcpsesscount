/**
 * @file array_unique.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_unique.h"


int array_unique_init(struct array_unique* array, size_t n)
{
    n += 4ul;
    n &= ~3ul;
    array->data = calloc(n, sizeof(uint64_t));
    array->size = 0ul;
    array->nalloc = n;
    return array->data == NULL ? -1 : 0;
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

size_t array_unique_lower_bound(struct array_unique* array, uint64_t i64)
{
    size_t start = 0ul;
    size_t step = 0ul;
    ssize_t count = array->size;
    while(count > 0l) {
        size_t i = start;
        step = count / 2l;
        i += step;
        if(*(array->data + i) < i64) {
            start = ++i;
            count -= step + 1ul;
        } else {
            count = step;
        }
    }
    return start;
}

int array_unique_push(struct array_unique* array, uint64_t i64)
{
    size_t i;
    if(array->nalloc < (array->size + 1ul)) {
        array->nalloc *= 2ul;
        array->data = realloc(array->data, sizeof(uint64_t) * array->nalloc);
        if(array->data == NULL) {
            return -1;
        }
    }
    i = array_unique_lower_bound(array, i64);
    while((i < array->size) && (i64 > *(array->data + i))) ++i;
    if(i < array->size) {
        if(i64 == *(array->data + i)) {
            return 0;
        }
        memcpy(array->data + i + 1ul, array->data + i, (array->size - i) * sizeof(uint64_t));
    }
    *(array->data + i) = i64;
    array->size += 1ul;
    return 1;
}

int array_unique_erase(struct array_unique* array, uint64_t i64)
{
    size_t i = array_unique_lower_bound(array, i64);
    while((i < array->size) && (i64 > *(array->data + i))) ++i;
    if((i < array->size) && (i64 == *(array->data + i))) {
        memcpy(array->data + i, array->data + i + 1ul, (array->size - i - 1ul) * sizeof(uint64_t));
        array->size -= 1;
        *(array->data + array->size) = 0ul;
        return 1;
    }
    return 0;
}

uint64_t array_unique_get(struct array_unique* array, int index)
{
    return ((size_t)index < array->size) ? *(array->data + (size_t)index) : 0ul;
}

void array_unique_print(struct array_unique* array)
{
    uint64_t* d;
    for(d = array->data; d != (array->data + array->size); ++d) {
        printf("%lu ", *d);
    }
    printf("\n");
}
