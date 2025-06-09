
#include <stddef.h>

typedef struct Stack {
  size_t count;
  size_t capacity;
  void **data;
} snek_stack_t;

snek_stack_t *stack_new(size_t capacity);
