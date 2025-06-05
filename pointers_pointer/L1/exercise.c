#include "stdlib.h"

#include "exercise.h"

void allocate_int(int **pointer_pointer, int value) {
    int* new_ptr = (int*)malloc(sizeof(int));
    *pointer_pointer = new_ptr;
    **pointer_pointer = value;
}
