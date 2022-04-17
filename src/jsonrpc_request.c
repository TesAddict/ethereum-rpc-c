#include "jsonrpc_request.h"

jsonrpc_request_t* jsonrpc_request_init() {
    jsonrpc_request_t *req = malloc(sizeof *req);
    req->method = malloc(METHOD_SZ_INIT * sizeof(char));
    req->method_sz = METHOD_SZ_INIT;
    req->params = calloc(PARAMS_SZ_INIT, sizeof(char *));
    req->params_sz = PARAMS_SZ_INIT;
    req->id = 1;
    if (req->params == NULL || req->method == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for jsonrpc_request_t.\n");
        jsonrpc_request_free(&req);
        return NULL;
    }
    return req;
}

void jsonrpc_request_free(jsonrpc_request_t **req) {
    free((*req)->method);
    (*req)->method = NULL;
    (*req)->method_sz = 0;
    for (size_t i = 0; i < (*req)->params_sz; ++i) {
        free((*req)->params[i]);
    }
    free((*req)->params);
    (*req)->params = NULL;
    (*req)->params_sz = 0;
    (*req)->id = 0;
    free((*req));
    (*req) = NULL;
}

int jsonrpc_request_set_method(jsonrpc_request_t *req, const char *method) {
    if (req == NULL || method == NULL) return -1;
    size_t n_method_len = strlen(method);
    if (n_method_len > req->method_sz) {
        free(req->method);
        req->method = malloc((n_method_len+1)*sizeof(char));
        if (req->method == NULL) {
            fprintf(stderr, "Failed to allocate memory for jsonrpc_request_t:method.\n");
            return -1;
        }
    }
    strcpy(req->method, method);
    req->method_sz = n_method_len;
    return 0;
}

static size_t parlen(jsonrpc_request_t *req) {
    size_t params_len = 0;
    for (size_t i = 0; i < req->params_sz; ++i) {
        if (req->params[i] == NULL) break;
        params_len++;
    }
    return params_len;
}

int jsonrpc_request_append_param(jsonrpc_request_t *req, const char *param) {
    if (req == NULL || param == NULL || req->params == NULL) return -1;
    size_t param_idx = parlen(req);
    if (param_idx == req->params_sz) {
        char **temp = realloc(req->params, req->params_sz * 2 * sizeof(char *));
        if (temp == NULL) {
            fprintf(stderr, "Failed to reallocate memory for jsonrpc_request_t:params.\n");
            return -1;
        }
        req->params = temp;
        req->params_sz *= 2;
        for (size_t i = param_idx; i < req->params_sz; ++i)
        {
            req->params[i] = NULL;
       }
    }
    req->params[param_idx] = malloc((strlen(param)+1)*sizeof(char));
    if (req->params[param_idx] == NULL) {
        fprintf(stderr, "Failed to allocate memory for jsonrpc_request_t:params.\n");
        return -1;
    }
    strcpy(req->params[param_idx], param);
    return 0;
}

void jsonrpc_request_clear_params(jsonrpc_request_t *req) {
    if (req == NULL || req->params == NULL) return;
    for (size_t i = 0; i < req->params_sz; ++i) {
        free(req->params[i]);
        req->params[i] = NULL;
    }
}

void jsonrpc_request_print(jsonrpc_request_t *req) {
    if (req == NULL) {
        printf("jsonrpc_request_t is NULL.\n");
        return;
    }
    if (req->method != NULL) 
        printf("method: %s\n", req->method);
    if (req->params != NULL && req->params[0] != NULL) {
        printf("params: \n");
        for (int i = 0; i < parlen(req); ++i) {
            printf("%d : %s\n", i, req->params[i]);
        }
    }
    printf("id: %d\n", req->id);
}

static size_t jsonrpc_request_t_size(jsonrpc_request_t *req) {
    if (req == NULL || req->method == NULL || req->params == NULL) return 0;
    size_t sz = 0;
    sz += strlen(req->method);
    for (int i = 0; i < parlen(req); ++i) {
        sz += strlen(req->params[i]) + 3;
    }
    int n = req->id;
    while(n != 0) {
        n = n / 10;
        sz++;
    }
    return sz;
}

char* jsonrpc_request_to_jsonstr(jsonrpc_request_t *req) {
    size_t req_sz = jsonrpc_request_t_size(req);
    if (req_sz == 0) return NULL;
    char *jsonstr = malloc((50+req_sz)*sizeof(char));
    char *first = "{\"jsonrpc\":\"2.0\",\"method\":\"";
    size_t idx = 0;
    strcpy(jsonstr, first);
    idx += strlen(first);
    strcpy(jsonstr+idx, req->method);
    idx += strlen(req->method);
    char *second = "\",\"params\":[";
    strcpy(jsonstr+idx, second);
    idx += strlen(second);
    for (size_t i = 0; i < parlen(req); ++i) {
        jsonstr[idx++] = '\"';
        strcpy(jsonstr+idx, req->params[i]);
        idx += strlen(req->params[i]);
        jsonstr[idx++] = '\"';
        if (i == parlen(req)-1) break;
        jsonstr[idx++] = ',';
    }
    char *third = "],\"id\":\"";
    strcpy(jsonstr+idx, third);
    idx += strlen(third);
    sprintf(jsonstr+idx, "%d", req->id);
    int n = req->id;
    while (n != 0) {
        n = n / 10;
        idx++;
    }
    // ID goes here.
    char *fourth = "\"}";
    strcpy(jsonstr+idx, fourth);
    return jsonstr;
}