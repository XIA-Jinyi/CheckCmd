#include "check.h"

static const char *msg_dict_arr[] = {
    [RESULT_SUCCESS] "Success.",
    [RESULT_INVALID_PARAM] "Invalid parameter(s).",
    [RESULT_RUNTIME_ERROR] "Runtime error.",
};

const char **msg_dict = msg_dict_arr;
