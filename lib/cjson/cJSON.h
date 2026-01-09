#ifndef cjson_cjson_h
#define cjson_cjson_h

#include <stddef.h>

typedef struct cjson_item {
    char *key;
    char *value;
} cjson_item;

typedef struct cjson_root {
    cjson_item item;
} cjson_root;

typedef cjson_root cJSON;

cJSON *cJSON_CreateObject(void);
void cJSON_AddStringToObject(cJSON *object, const char *key, const char *value);
char *cJSON_Print(const cJSON *object);
void cJSON_Delete(cJSON *object);

#endif
