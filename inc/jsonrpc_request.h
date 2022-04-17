#ifndef JSONRPC_STRING_H
#define JSONRPC_STRING_H

#define PARAMS_SZ_INIT 16
#define METHOD_SZ_INIT 256

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *method;
    size_t method_sz;
    char **params;
    size_t params_sz;
    int id;
} jsonrpc_request_t;

jsonrpc_request_t* jsonrpc_request_init();
void jsonrpc_request_free(jsonrpc_request_t **req);
int jsonrpc_request_set_method(jsonrpc_request_t *req, const char *method);
int jsonrpc_request_append_param(jsonrpc_request_t *req, const char *param);
void jsonrpc_request_clear_params(jsonrpc_request_t *req);
void jsonrpc_request_print(jsonrpc_request_t *req);
char* jsonrpc_request_to_jsonstr(jsonrpc_request_t *req);

#endif