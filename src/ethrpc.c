#include "ethrpc.h"

ethrpc_t *ethrpc_init(const char *hostname, int port) {
    ethrpc_t *ethrpc = malloc(sizeof *ethrpc);
    if (ethrpc == NULL) {
        fprintf(stderr, "Failed to alloc() ethrpc.\n");
    }
    ethrpc->curl = jsonrpc_client_init(hostname, port);
    if (ethrpc->curl == NULL) return NULL;
    ethrpc->request = jsonrpc_request_init();
    if (ethrpc->request == NULL) return NULL;
    return ethrpc;
}

void ethrpc_free(ethrpc_t **ethrpc) {
    jsonrpc_request_free(&((*ethrpc)->request));
    jsonrpc_client_free(((*ethrpc)->curl));
    free(*ethrpc);
    (*ethrpc) = NULL;
}

long long eth_getBalance(ethrpc_t *ethrpc, const char *address, const char *block) {
    if (ethrpc->request == NULL || ethrpc->curl == NULL) return 0;
    jsonrpc_request_set_method(ethrpc->request, "eth_getBalance");
    jsonrpc_request_append_param(ethrpc->request, address);
    jsonrpc_request_append_param(ethrpc->request, block);
    jsonrpc_response_t *resp = jsonrpc_client_send(ethrpc->curl, ethrpc->request);
    if (resp == NULL || resp->result_sz != 1) {
        jsonrpc_request_clear_params(ethrpc->request);
        return 0;
    }
    long long balance = strtoll(resp->result[0], NULL, 16);
    jsonrpc_response_free(&resp);
    return balance;
}