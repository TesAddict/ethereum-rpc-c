#ifndef JSONRPC_CLIENT_H
#define JSONRPC_CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "jsonrpc_request.h"
#include "jsonrpc_response.h"

CURL *jsonrpc_client_init(const char *hostname, uint port);
void jsonrpc_client_free(CURL *curl);
jsonrpc_response_t  *jsonrpc_client_send(CURL *curl, jsonrpc_request_t *req);

#endif