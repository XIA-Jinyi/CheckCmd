#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "check.h"

#define THREAD_NUM (3)

int func_a() {
  return RESULT_RUNTIME_ERROR;  // Error occurs here.
}

int func_b() {
  CHECKIGNORE(func_a());
  return RESULT_SUCCESS;
}

void *func_thread(void *ptr) {
  CHECKIGNORE(func_b());
  return NULL;
}

int main() {
  pthread_t threads[THREAD_NUM];
  for (int i = 0; i < THREAD_NUM; i++) {
    if (pthread_create(threads + i, NULL, func_thread, NULL))
      exit(EXIT_FAILURE);
  }
  for (int i = 0; i < THREAD_NUM; i++) {
    pthread_join(threads[i], NULL);
  }
  return 0;
}
