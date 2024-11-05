#include "checkcmd.h"
#include <pthread.h>
#include <deque>

using namespace std;

typedef struct {
  const char *func;
  const char *file;
  int line;
} checkcmd_info_t;

typedef deque<checkcmd_info_t> trace_data_t, *ptrace_data_t;

static pthread_key_t trace_data_key;

static void trace_data_cleanup(void *data) {
  delete static_cast<ptrace_data_t>(data);
}

static inline ptrace_data_t trace_data_get() {
  ptrace_data_t trace_data = static_cast<ptrace_data_t>(pthread_getspecific(trace_data_key));
  if (!trace_data) {
    trace_data = new trace_data_t;
    pthread_setspecific(trace_data_key, static_cast<void *>(trace_data));
  }
  return trace_data;
}

static void checkcmd_init() __attribute__((constructor));
static void checkcmd_init() {
  pthread_key_create(&trace_data_key, trace_data_cleanup);
}

static void checkcmd_abort() __attribute__((destructor));
static void checkcmd_abort() {
  pthread_key_delete(trace_data_key);
}

size_t checkcmd_trace_into(const char *func, const char *file, int line) {
  ptrace_data_t trace_data = trace_data_get();
  trace_data->push_front({func, file, line});
  return trace_data->size();
}

size_t checkcmd_trace_out() {
  ptrace_data_t trace_data = trace_data_get();
  trace_data->pop_front();
  return trace_data->size();
}

size_t checkcmd_trace_log(FILE *out, const char **msg_dict, int ret) {
  ptrace_data_t trace_data = trace_data_get();
  flockfile(out);
  fprintf(out, "[Thread %lu] Unexpected result (%d)", (unsigned long)pthread_self(), ret);
  if (msg_dict) {
    fprintf(out, ": %s", msg_dict[ret]);
  }
  fputc('\n', out);
  for (const checkcmd_info_t &info : *trace_data) {
    fprintf(out, "\t- in `%s` (%s:%d)\n", info.func, info.file, info.line);
  }
  funlockfile(out);
  return trace_data->size();
}
