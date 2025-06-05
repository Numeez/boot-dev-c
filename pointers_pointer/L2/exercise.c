#include <stdlib.h>

#include "exercise.h"

token_t** create_token_pointer_array(token_t* tokens, size_t count) {
  token_t** token_pointers = malloc(count * sizeof(token_t*));
  if (token_pointers == NULL) {
    exit(1);
  }
  for (size_t i = 0; i < count; ++i) {
    token_t* new_mem = malloc(sizeof(token_t));
    token_pointers[i] = new_mem;
    token_t old_token = tokens[i];
    new_mem->column = old_token.column;
    new_mem->line =  old_token.line;
    new_mem->literal = old_token.literal;

  }
  return token_pointers;
}
