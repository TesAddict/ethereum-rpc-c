#include "json.h"
#include <assert.h>

int test_json_add_inline() {
    json_t *root = json_init(OBJECT, NULL, NULL);
    json_t *param_array = json_init(ARRAY, "params", NULL);
    json_add_deeper(param_array, json_init(OBJECT, NULL, NULL));
    json_add_deeper(param_array->deeper, json_init(STRING, "from", "0x0"));
    json_add_next(param_array->deeper->deeper, json_init(STRING, "to", "0x0"));
    json_add_next(param_array->deeper->deeper, json_init(STRING, "gas", "0x0"));
    json_add_next(param_array->deeper->deeper, json_init(STRING, "value", "0x0"));
    json_add_next(param_array->deeper->deeper, json_init(STRING, "data", "0x0"));
    json_add_next(param_array, json_init(STRING, "jsonrpc", "2.0"));
    json_add_deeper(root, param_array);
    json_to_str(root);
    return 0;
}