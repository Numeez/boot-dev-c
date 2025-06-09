#include "snekstack.h"
#include "stdlib.h"
#include <string.h>

void stack_push_multiple_types(snek_stack_t *s) {
    float* float_data = malloc(sizeof(float));
    char* char_content = "Sneklang is blazingly slow!";
    char* char_data = malloc(sizeof(char)*strlen(char_content)+1);
    *float_data = 3.14;
    strcpy(char_content,char_data);
    stack_push(s,float_data);
    stack_push(s,char_data);

}
