#ifndef _JSON_H_
#define _JSON_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    STRING,
    NUMBER,
    OBJECT,
    ARRAY,
    BOOLEAN
} json_type_t;

typedef struct json_t {
    char *key;
    void *value;
    struct json_t *next;
    struct json_t *deeper;
    json_type_t type;
} json_t;

json_t *json_init(json_type_t type, const char *key, void *value);
int json_add_next(json_t *root, json_t *next);
int json_add_deeper(json_t *root, json_t *deeper);
void json_to_str(json_t *root);
#endif