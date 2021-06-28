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

int array_unique_push(struct array_unique* array, uint64_t i64)
{
    uint64_t data = 0ul;
    size_t n = 0ul, s = array->size, i = 0ul;
    if(array->nalloc < (array->size + 1)) {
        array->nalloc *= 2ul;
        array->data = realloc(array->data, sizeof(uint64_t) * array->nalloc);
        if(array->data == NULL) {
            return -1;
        }
    }
    while(n <= s) {
        i = n + (s - n) / 2ul;
        if(i >= array->size) {
            i = 0ul;
            break;
        }
        data = *(array->data + i);
        if(data < i64) {
            n = i + 1ul;
        } else if(data > i64) {
            s = i - 1ul;
        } else {
            return 0;
        }
    }
    while((i < array->size) && (i64 > *(array->data + i))) ++i;
    memcpy(array->data + i + 1ul, array->data + i, (array->size - i) * sizeof(uint64_t));
    *(array->data + i) = i64;
    array->size += 1ul;
    return 1;
}

int array_unique_erase(struct array_unique* array, uint64_t i64)
{
    uint64_t data = ~0ul;
    size_t n = 0ul, s = array->size, i = 0ul;
    while(n < s) {
        i = n + (s - n) / 2ul;
        data = *(array->data + i);
        if(data < i64) {
            n = i + 1ul;
        } else if(data > i64) {
            s = i - 1ul;
        } else {
            break;
        }
    }
    if(i64 == data) {
        memcpy(array->data + i, array->data + i + 1ul, (array->size - i - 1) * sizeof(uint64_t));
        array->size -= 1;
        *(array->data + array->size) = 0ul;
        return 0;
    }
    return -1;
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
