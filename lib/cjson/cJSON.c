#include "cJSON.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *cjson_strdup(const char *value) {
    size_t len = value ? strlen(value) : 0;
    char *out = (char *)malloc(len + 1);
    if (!out) return NULL;
    if (value) {
        memcpy(out, value, len);
    }
    out[len] = '\0';
    return out;
}

cJSON *cJSON_CreateObject(void) {
    cJSON *object = (cJSON *)malloc(sizeof(cJSON));
    if (!object) return NULL;
    object->item.key = NULL;
    object->item.value = NULL;
    return object;
}

void cJSON_AddStringToObject(cJSON *object, const char *key, const char *value) {
    if (!object) return;
    free(object->item.key);
    free(object->item.value);
    object->item.key = cjson_strdup(key);
    object->item.value = cjson_strdup(value);
}

char *cJSON_Print(const cJSON *object) {
    if (!object || !object->item.key || !object->item.value) {
        return cjson_strdup("{}");
    }

    size_t key_len = strlen(object->item.key);
    size_t value_len = strlen(object->item.value);
    size_t total_len = key_len + value_len + 6;
    char *out = (char *)malloc(total_len);
    if (!out) return NULL;

    snprintf(out, total_len, "{\"%s\":\"%s\"}", object->item.key, object->item.value);
    return out;
}

void cJSON_Delete(cJSON *object) {
    if (!object) return;
    free(object->item.key);
    free(object->item.value);
    free(object);
}
