#include <stdio.h>
#include <stdlib.h>
#include "exercise.h"

char *get_full_greeting(char *greeting, char *name, int size) {
    char* mem_heap = (char*)malloc(size*sizeof(char));
  snprintf(mem_heap,size, "%s %s", greeting, name);
  return mem_heap;
}
