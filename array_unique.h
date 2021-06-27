/**
 * @file array_unique.h
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

/**
 * @short Массив уникальных значений
 */
struct array_unique {
    uint64_t* data;
    size_t    size;
    size_t    nalloc;
};


/**
 * @short 
 */
extern int    array_unique_init(struct array_unique* array, size_t n);
extern void   array_unique_destroy(struct array_unique* array);
extern size_t array_unique_size(struct array_unique* array);
extern int    array_unique_push(struct array_unique* array, uint64_t i64);
extern int    array_unique_erase(struct array_unique* array, uint64_t i64);
