#include "jsonrpc_client.h"

static CURL *curl;

struct string {
    char *ptr;
    size_t len;
};

static size_t write_callback(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t len = size*nmemb;
  s->ptr = malloc(len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr, ptr, size*nmemb);
  s->ptr[len] = '\0';
  s->len = len;
  return size*nmemb;
}

int jsonrpc_client_init(const char *hostname, uint port) {
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, hostname);
        curl_easy_setopt(curl, CURLOPT_PORT, port);
    }
}

int jsonrpc_client_send(jsonrpc_request_t *req) {
  struct string s;
  char *jsonstr = jsonrpc_request_to_jsonstr(req);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonstr);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) return -1;
  free(jsonstr);
  printf("%s\n", s.ptr);
  return 0;
}