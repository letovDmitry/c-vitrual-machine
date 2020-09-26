#include "type.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct Stack {
    vtype_t value_type;
    value_t stack_buffer;

    size_t size;
    size_t index;
} Stack;

static void _clean_stack(Stack* stack);
static void _stack_insert(Stack* stack, size_t index, void* value);

extern Stack* create_stack(size_t size, vtype_t value_type) {
    switch (value_type) {
    case DECIMAL_TYPE:
        break;
    case REAL_TYPE:
        break;
    case STRING_TYPE:
        break;
    default:
        fprintf(stderr, "%s\n", "type error: type not found");
        return NULL;
    }

    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->stack_buffer = (value_t*)malloc(sizeof(value_t)*size);
    stack->size = size;
    stack->index = 0;
    return stack;
}

extern void clean_stack(Stack* stack) {
    _clean_stack(stack);
    free(stack->stack_buffer);
    free(stack);
}

static void _stack_insert(Stack* stack, size_t index, void* value) {
    if (index >= stack->size) {
        fprintf(stderr, "%s\n", "stack error: index is greater than stack size");
        return;
    }

    switch(stack->value_type) {
        case DECIMAL_TYPE:
            stack->stack_buffer[index].decimal = (int32_t)(intptr_t)value;
            break;
        case REAL_TYPE:
            stack->stack_buffer[index].real = *(double*)value;
            free((double*)value);
            break;
        case STRING_TYPE: {
            size_t size = strlen((char*)value);
            stack->stack_buffer[index].string = (char*)malloc(sizeof(char) * size + 1);
            strcpy(stack->stack_buffer[index].string, (char*)value);
            }
            break;
        default: ;
    }
}

extern void stack_push(Stack* stack, void* value){
    _stack_insert(stack, stack->index, value);
    stack->index += 1;
}

extern void stack_pop(Stack* stack){
    if(stack->index == 0) {
        fprintf(stderr, "%s\n", "stack error: stack overflow");
        value_t nill = {
            .decimal = 0,
        };

        return nill;
    }

    stack->index -= 1;

    return stack->stack_buffer[stack->index];
}

extern value_t stack_get(Stack* stack, size_t index) {
    if (index >= stack->size) {
        fprintf(stderr, "%s\n", "stack error: index is greater than stack size");
        value_t nill = {
            .decimal = 0,
        };

        return nill;
    }
    return stack->stack_buffer[index];
}

extern void set_stack(Stack* stack, size_t index, void* value) {
    _stack_insert(stack, index, value);
}

static void _clean_stack(Stack* stack) {
    switch(stack->value_type) {
        case STRING_TYPE:
            for(size_t i = 0; i < stack->index; ++i) {
                free(stack->stack_buffer[i].string);
            }
            break;
        default: ;
    }
}