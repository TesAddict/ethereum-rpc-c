#include "json.h"

json_t *json_init(json_type_t type, const char *key, void *value) {
    json_t *json = malloc(sizeof *json);
    if (json == NULL) {
        fprintf(stderr, "json_init(): malloc() for json_t has failed.\n");
        return NULL;
    }
    if (key != NULL) {
        json->key = malloc((strlen(key) + 1) * sizeof(char));
        strcpy(json->key, key);
    } else {
        json->key = NULL;
    }
    json->type = type;
    switch (type) {
        case BOOLEAN:
        case STRING:
        case NUMBER:
            if (value == NULL || key == NULL) {
                free(json->key);
                free(json);
                fprintf(stderr, "json_init(): NULL key or value for BOOLEAN, STRING or NUMBER.\n");
                return NULL;
            }
            json->value = malloc((strlen((char *)value) + 1) * sizeof(char));
            strcpy(json->value, value);
            break;
        case OBJECT:
        case ARRAY:
            json->value = NULL;
            break;
    }
    json->next = NULL;
    json->deeper = NULL;
    return json;
}

int json_add_next(json_t *root, json_t *next) {
    if (next == NULL) {
        fprintf(stderr, "json_add_next(): can not add NULL json_t next.\n");
        return -1;
    }
    while(root->next != NULL) root = root->next;
    root->next = next;
    return 0;
}

int json_add_deeper(json_t *root, json_t *deeper) {
    if (deeper == NULL) {
        fprintf(stderr, "json_add_deeper(): can not add NULL json_t deeper.\n");
        return -1;
    }
    if (root->type != OBJECT && root->type != ARRAY) {
        fprintf(stderr, "json_add_deeper() only OBJECT or ARRAY root types can have nodes added deeper.\n");
        return -1;
    }
    root->deeper = deeper;
    return 0;
}

void json_to_str(json_t *root) {
    if (root == NULL) return;
    switch(root->type) {
        case STRING:
        case NUMBER:
        case BOOLEAN:
            if (root->next != NULL) {
                printf("\"%s\":\"%s\",", root->key, (char *)root->value);
            } else {
                printf("\"%s\":\"%s\"", root->key, (char *)root->value);
            }
            break;
        case OBJECT:
            if (root->key != NULL) {
                printf("\"%s\":{", root->key);
            } else {
                printf("{");
            }
            break;
        case ARRAY:
            if (root->key != NULL) {
                printf("\"%s\":[", root->key);
            } else {
                printf("[");
            }
            break;
    }
    json_to_str(root->deeper);
    switch(root->type) {
        case OBJECT:
            if (root->next != NULL) {
                printf("},");
            } else {
                printf("}");
            }
            break;
        case ARRAY:
            if (root->next != NULL) {
                printf("],");
            } else {
                printf("]");
            }
            break;
    }
    json_to_str(root->next);
}