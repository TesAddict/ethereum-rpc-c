#ifndef JSONRPC_CLIENT_H
#define JSONRPC_CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "jsonrpc_request.h"

int jsonrpc_client_init(const char *hostname, uint port);
int jsonrpc_client_send(jsonrpc_request_t *req);

#endif