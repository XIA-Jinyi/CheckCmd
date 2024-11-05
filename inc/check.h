#pragma once

#ifndef CHECK_H_
#define CHECK_H_

#include "checkcmd.h"

enum {
  RESULT_SUCCESS,
  RESULT_INVALID_PARAM,
  RESULT_RUNTIME_ERROR,
};

extern const char **msg_dict;

#define CHECK(CMD)                                                             \
  CHECKCMD_EXIT(CMD, stderr, RESULT_SUCCESS, msg_dict, (int *)NULL)

#define CHECKIGNORE(CMD)                                                       \
  CHECKCMD_NOEXIT(CMD, stderr, RESULT_SUCCESS, msg_dict, (int *)NULL)

#define CHECKSTORE(CMD, RETVAL_PTR)                                            \
  CHECKCMD_NOEXIT(CMD, stderr, RESULT_SUCCESS, msg_dict, RETVAL_PTR)

#endif // CHECK_H_
