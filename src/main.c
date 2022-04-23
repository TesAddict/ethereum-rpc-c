#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "ethrpc.h"

int main() {
    ethrpc_t *ethrpc = ethrpc_init("http://127.0.0.1", 8545);
    long long balance = eth_getBalance(ethrpc,"0x2E0dB60545D9A97F583fD9A47B5DFff0345a9d9F", "latest");
    printf("Balance: %lld\n", balance);
    ethrpc_free(&ethrpc);
    return 0;
}