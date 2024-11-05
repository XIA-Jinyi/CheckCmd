#pragma once

#ifndef CHECKCMD_H_
#define CHECKCMD_H_

#include <assert.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

enum {
  CHECKCMD_MODE_DEFAULT = 0,
  CHECKCMD_MODE_NOEXIT = 1,
  CHECKCMD_MODE_SILENT = 2,
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

size_t checkcmd_trace_into(const char *func, const char *file, int line);
size_t checkcmd_trace_out();
size_t checkcmd_trace_log(FILE *out, const char **msg_dict, int ret);

#define CHECKCMD_CHECKTYPE(expr, type)                                         \
  _Static_assert(_Generic((expr), type: 1, default: 0),                        \
                 "Type mismatch: `" #expr "` is not of type `" #type "`")

#ifdef __cplusplus
}
#endif // __cplusplus

#define CHECKCMD_EXPAND(CMD, FILE_OUT, EXPECTED, MSG_DICT, RETVAL_PTR, MODE)   \
  do {                                                                         \
    CHECKCMD_CHECKTYPE(CMD, int);                                              \
    CHECKCMD_CHECKTYPE(FILE_OUT, FILE *);                                      \
    CHECKCMD_CHECKTYPE(EXPECTED, int);                                         \
    CHECKCMD_CHECKTYPE(MSG_DICT, const char **);                               \
    CHECKCMD_CHECKTYPE(RETVAL_PTR, int *);                                     \
    CHECKCMD_CHECKTYPE(MODE, int);                                             \
    checkcmd_trace_into(__func__, __FILE__, __LINE__);                         \
    int ret = CMD;                                                             \
    if (ret != (EXPECTED)) {                                                   \
      if (!((MODE) & CHECKCMD_MODE_SILENT)) {                                  \
        checkcmd_trace_log(FILE_OUT, MSG_DICT, ret);                           \
      }                                                                        \
      if (!((MODE) & CHECKCMD_MODE_NOEXIT)) {                                  \
        exit(EXIT_FAILURE);                                                    \
      }                                                                        \
    }                                                                          \
    checkcmd_trace_out();                                                      \
    if (RETVAL_PTR) {                                                          \
      *(int *)(RETVAL_PTR) = ret;                                              \
    }                                                                          \
  } while (0)

#define CHECKCMD_EXIT(CMD, FILE_OUT, EXPECTED, MSG_DICT, RETVAL_PTR)           \
  CHECKCMD_EXPAND(CMD, FILE_OUT, EXPECTED, MSG_DICT, RETVAL_PTR,               \
                  CHECKCMD_MODE_DEFAULT)

#define CHECKCMD_NOEXIT(CMD, FILE_OUT, EXPECTED, MSG_DICT, RETVAL_PTR)         \
  CHECKCMD_EXPAND(CMD, FILE_OUT, EXPECTED, MSG_DICT, RETVAL_PTR,               \
                  CHECKCMD_MODE_NOEXIT)

#endif // CHECKCMD_H_
