#ifndef EXTLIB_STACK_H_
#define EXTLIB_STACK_H_

#include "type.h"
#include <stddef.h>

typedef struct Stack Stack;

extern Stack *create_stack(size_t size, vtype_t value_type);
extern void clean_stack(Stack *stack);
extern void stack_push(Stack* stack, void *value);
extern value_t stack_get(Stack *stack, size_t index);
extern void stack_pop(Stack* stack);
extern void set_stack(Stack *stack, size_t index, void* value);

#endif