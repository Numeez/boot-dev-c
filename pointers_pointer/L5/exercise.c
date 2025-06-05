#include<stdio.h>
#include "exercise.h"
void swap_strings(char **a, char **b) {
    char* temp = *a;
     *a = *b;
    *b = temp;
}
