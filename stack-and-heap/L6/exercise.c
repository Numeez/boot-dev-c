#include <stdio.h>
#include <stdlib.h>
#include "exercise.h"

int *allocate_scalar_array(int size, int multiplier) {
    if (size>=1024*1024*100){
        return NULL;
    }
    int* mem_int = (int*)malloc(size*sizeof(int));
    if (mem_int==NULL){
        return NULL;
    }
    for(int i=0;i<size;i++){
        mem_int[i] = i*multiplier;
    }

    return mem_int;
}
