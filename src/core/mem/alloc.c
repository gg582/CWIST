#include <cwist/core/mem/alloc.h>
#include <ttak/mem/mem.h>
#include <ttak/timing/timing.h>
#include <cjson/cJSON.h>
#include <string.h>
#include <limits.h>

static inline uint64_t cwist_mem_now(void) {
    return ttak_get_tick_count();
}

void *cwist_alloc(size_t size) {
    size_t actual = size ? size : 1;
    return ttak_mem_alloc_safe(actual,
                               __TTAK_UNSAFE_MEM_FOREVER__,
                               cwist_mem_now(),
                               false,
                               false,
                               true,
                               true,
                               TTAK_MEM_DEFAULT);
}

void *cwist_alloc_array(size_t count, size_t elem_size) {
    if (count == 0 || elem_size == 0) {
        return cwist_alloc(1);
    }
    if (elem_size > SIZE_MAX / count) {
        return NULL;
    }
    return cwist_alloc(count * elem_size);
}

void *cwist_realloc(void *ptr, size_t new_size) {
    size_t actual = new_size ? new_size : 1;
    if (!ptr) {
        return cwist_alloc(actual);
    }
    return ttak_mem_realloc_safe(ptr,
                                 actual,
                                 __TTAK_UNSAFE_MEM_FOREVER__,
                                 cwist_mem_now(),
                                 true,
                                 TTAK_MEM_DEFAULT);
}

char *cwist_strdup(const char *src) {
    if (!src) return NULL;
    size_t len = strlen(src);
    char *dst = (char *)cwist_alloc(len + 1);
    if (!dst) return NULL;
    memcpy(dst, src, len + 1);
    return dst;
}

static size_t cwist_strnlen(const char *src, size_t max_len) {
    size_t len = 0;
    while (len < max_len && src[len]) {
        len++;
    }
    return len;
}

char *cwist_strndup(const char *src, size_t n) {
    if (!src) return NULL;
    size_t len = cwist_strnlen(src, n);
    char *dst = (char *)cwist_alloc(len + 1);
    if (!dst) return NULL;
    memcpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}

void cwist_free(void *ptr) {
    if (ptr) {
        ttak_mem_free(ptr);
    }
}

static void *cwist_cjson_malloc(size_t size) {
    return cwist_alloc(size);
}

static void cwist_cjson_free(void *ptr) {
    cwist_free(ptr);
}

__attribute__((constructor))
static void cwist_install_cjson_hooks(void) {
    cJSON_Hooks hooks = {
        .malloc_fn = cwist_cjson_malloc,
        .free_fn = cwist_cjson_free
    };
    cJSON_InitHooks(&hooks);
}
