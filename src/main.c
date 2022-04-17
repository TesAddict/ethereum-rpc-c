#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "jsonrpc_request.h"
#include "jsonrpc_client.h"

int main() {
    jsonrpc_client_init("http://127.0.0.1", 8545);
    jsonrpc_request_t *req = jsonrpc_request_init();
    jsonrpc_request_set_method(req, "eth_getBalance");
    jsonrpc_request_append_param(req, "0x641E55c3e7bbBC356192a162B65fFDE8AEF4A41C");
    jsonrpc_request_append_param(req, "latest");
    jsonrpc_client_send(req);
    jsonrpc_request_free(&req);
    return 0;
}