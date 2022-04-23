#ifndef _ETH_RPC_H_
#define _ETH_RPC_H_

#include <stdint.h>
#include <stdlib.h>

#include "jsonrpc_request.h"
#include "jsonrpc_response.h"
#include "jsonrpc_client.h"

typedef struct {
    CURL *curl;
    jsonrpc_request_t *request;
} ethrpc_t;

ethrpc_t *ethrpc_init(const char *hostname, int port);
void ethrpc_free(ethrpc_t **ethrpc);
long long eth_getBalance(ethrpc_t *ethrpc, const char *address, const char *block); 



#endif