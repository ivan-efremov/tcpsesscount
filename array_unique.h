/**
 * @file array_unique.h
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

/**
 * @short Массив уникальных значений.
 */
struct array_unique {
    uint64_t* data;
    size_t    size;
    size_t    nalloc;
};

#define ARRAY_ITEM_NOT_FOUND (~0ULL)

/**
 * @short Методы массива.
 */
extern int      array_unique_init(struct array_unique* array, size_t n);
extern void     array_unique_destroy(struct array_unique* array);
extern size_t   array_unique_size(struct array_unique* array);
extern size_t   array_unique_lower_bound(struct array_unique* array, uint64_t i64);
extern int      array_unique_push(struct array_unique* array, uint64_t i64);
extern int      array_unique_erase(struct array_unique* array, uint64_t i64);
extern uint64_t array_unique_get(struct array_unique* array, int index);
extern void     array_unique_print(struct array_unique* array);
