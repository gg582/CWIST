#ifndef __CWIST_CORE_MEM_ALLOC_H__
#define __CWIST_CORE_MEM_ALLOC_H__

#include <stddef.h>

/**
 * @brief Allocate zeroed memory tracked by libttak.
 */
void *cwist_alloc(size_t size);

/**
 * @brief Allocate zeroed memory for count elements.
 */
void *cwist_alloc_array(size_t count, size_t elem_size);

/**
 * @brief Resize an existing allocation (libttak tracked).
 */
void *cwist_realloc(void *ptr, size_t new_size);

/**
 * @brief Duplicate a string using libttak-backed storage.
 */
char *cwist_strdup(const char *src);

/**
 * @brief Duplicate up to n bytes of a string (libttak-backed).
 */
char *cwist_strndup(const char *src, size_t n);

/**
 * @brief Free memory obtained via cwist_alloc/cwist_strdup/etc.
 */
void cwist_free(void *ptr);

#endif
