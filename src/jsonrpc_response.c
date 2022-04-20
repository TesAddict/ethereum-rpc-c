#include "jsonrpc_response.h" 

static const char *TARGET_TOKEN_BEGIN = "\"result\":\"";
static const char *TARGET_TOKEN_END   = "\"}";

jsonrpc_response_t *jsonrpc_response_init(const char *json) {
   char *begin = strstr(json, TARGET_TOKEN_BEGIN);
   if (begin == NULL) return NULL;
   char *end   = strstr(begin, TARGET_TOKEN_END);
   if (end == NULL) return NULL;
   jsonrpc_response_t *resp = malloc(sizeof *resp);
   if (resp == NULL) {
      fprintf(stderr, "Failed to alloc() for jsonrpc_response_t.\n");
      return NULL;
   }
   resp->result = calloc(1, sizeof(char *));
   resp->result[0] = malloc((end - begin + strlen(TARGET_TOKEN_BEGIN)) * sizeof(char));
   if (resp->result == NULL) {
      fprintf(stderr, "Failed to alloc() for jsonrpc_response_t->result.\n");
      jsonrpc_response_free(&resp);
      return NULL;
   }
   strncpy(resp->result[0], 
           begin+strlen(TARGET_TOKEN_BEGIN), 
           end-begin-strlen(TARGET_TOKEN_BEGIN));
   resp->result_sz = 1;
   return resp;
}

void jsonrpc_response_free(jsonrpc_response_t **resp) {
   if ((*resp) == NULL) return;
   for (int i = 0; i < (*resp)->result_sz; ++i) {
      free((*resp)->result[i]);
   }
   free(*resp);
   (*resp) = NULL;
}