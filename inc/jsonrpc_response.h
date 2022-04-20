#ifndef _JSONRPC_RESPONSE_H_
#define _JSONRPC_RESPONSE_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char **result;
    size_t result_sz;
} jsonrpc_response_t;

jsonrpc_response_t *jsonrpc_response_init(const char *json);
void jsonrpc_response_free(jsonrpc_response_t **resp);

#endif