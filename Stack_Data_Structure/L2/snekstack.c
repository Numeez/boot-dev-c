#include "snekstack.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

void stack_push(snek_stack_t *stack, void *obj) {
    if (stack->count==stack->capacity){
        void* new_stack_mem = realloc(stack->data,sizeof(void*)*stack->capacity*2);
        if (new_stack_mem==NULL){
            return;
        }else{
        stack->data = new_stack_mem;
        stack->capacity = stack->capacity*2;
        }
    }
    stack->data[stack->count++] = obj;
}

// don't touch below this line

snek_stack_t *stack_new(size_t capacity) {
  snek_stack_t *stack = malloc(sizeof(stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->capacity = capacity;
  stack->data = malloc(stack->capacity * sizeof(void *));
  if (stack->data == NULL) {
    free(stack);
    return NULL;
  }

  return stack;
}
