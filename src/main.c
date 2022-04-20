#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "jsonrpc_request.h"
#include "jsonrpc_response.h"
#include "jsonrpc_client.h"

int main() {
    jsonrpc_client_init("http://127.0.0.1", 8545);
    jsonrpc_request_t *req = jsonrpc_request_init();
    jsonrpc_request_set_method(req, "eth_getBalance");
    jsonrpc_request_append_param(req, "0x2E0dB60545D9A97F583fD9A47B5DFff0345a9d9F");
    jsonrpc_request_append_param(req, "latest");
    jsonrpc_response_t *resp = jsonrpc_client_send(req);
    printf("%s\n", resp->result[0]);
    jsonrpc_request_free(&req);
    jsonrpc_response_free(&resp);
    jsonrpc_client_free();
    return 0;
}