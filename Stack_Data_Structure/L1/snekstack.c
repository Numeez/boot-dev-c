#include "snekstack.h"
#include <stdlib.h>

snek_stack_t *stack_new(size_t capacity) {

    snek_stack_t* s = malloc(sizeof(snek_stack_t));
    if (s==NULL){
        return NULL;
    }
    void* data = malloc(sizeof(void*)*capacity);
    if (data==NULL){
        free(s);
        return NULL;
    }   
    s->count = 0;
    s->capacity = capacity;
    s->data = data;
    return s;

}
