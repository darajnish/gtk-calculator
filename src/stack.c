
#include <stdlib.h>
#include "stack.h"

ExpStack* stack_exp_new() {
    ExpStack *stack;
    stack = (ExpStack*) malloc(sizeof(ExpStack));

    if (stack == NULL) {
        return NULL;
    }

    stack->cap = 5;
    stack->len = 0;
    stack->data = (ExpStackCell*) malloc(sizeof(ExpStackCell) * stack->cap);

    if (stack->data == NULL) {
        return NULL;
    }

    return stack;
}

ExpStackCell* stack_exp_peek(ExpStack* stack) {
    if (stack == NULL)
        return NULL;

    return &stack->data[stack->len - 1];
}

ExpStackCell* stack_push(ExpStack* stack, ExpStackCell cell) {
    if (stack == NULL)
        return NULL;

    if (stack->len >= stack->cap) {
        stack->data = (ExpStackCell*) realloc(stack->data, sizeof(ExpStackCell) * (stack->cap += 5));
    }

    stack->data [stack->len++] = cell;
    return &stack->data [stack->len - 1];
}

char stack_exp_push_opt(ExpStack* stack, char opt) {
    ExpStackCell *cell;
    ExpStackCell icell = { .type=EXP_OPERATOR, .value={ .opt=opt } };
    cell = stack_push(stack, icell);

    if (cell == NULL) {
        return -1;
    }
    return opt;
}

double stack_exp_push_num(ExpStack* stack, double num) {
    ExpStackCell *cell;
    ExpStackCell icell = { .type=EXP_NUMBER, .value={ .num=num } };
    cell = stack_push(stack, icell);

    if (cell == NULL) {
        return 0.0;
    }
    return num;
}

ExpStackCell* stack_exp_pop(ExpStack* stack) {
    ExpStackCell *cell;

    if (stack == NULL)
        return NULL;

    cell = &stack->data[--stack->len];
    return cell;
}

void stack_exp_free(ExpStack* stack) {
    if (stack == NULL)
        return;

    free(stack->data);
    free(stack);
}


CharStack* stack_char_new() {
    CharStack *stack;
    stack = (CharStack*) malloc(sizeof(CharStack));

    if (stack == NULL) {
        return NULL;
    }

    stack->cap = 5;
    stack->len = 0;
    stack->data = (char*) malloc(sizeof(char) * (stack->cap));

    if (stack->data == NULL) {
        return NULL;
    }

    return stack;
}

char stack_char_peek(CharStack* stack) {
    if (stack == NULL)
        return -1;

    return stack->data[stack->len-1];
}

char stack_char_push(CharStack* stack, char c) {
    if (stack == NULL)
        return -1;

    if (stack->len >= stack->cap) {
        stack->data = (char*) realloc(stack->data, sizeof(char) * (stack->cap += 5));
    }
    stack->data[stack->len++] = c;
    return c;
}

char stack_char_pop(CharStack* stack) {
    if (stack == NULL)
        return -1;

    return stack->data[--stack->len];
}

void stack_char_free(CharStack* stack) {
    if (stack == NULL)
        return;
    
    free(stack->data);
    free(stack);
}

NumStack* stack_num_new() {
    NumStack *stack;
    stack = (NumStack*) malloc(sizeof(NumStack));

    if (stack == NULL) {
        return NULL;
    }

    stack->cap = 5;
    stack->len = 0;
    stack->data = (double*) malloc(sizeof(double) * (stack->cap));

    if (stack->data == NULL) {
        return NULL;
    }

    return stack;
}

double stack_num_peek(NumStack* stack) {
    if (stack == NULL)
        return 0.0;

    return stack->data[stack->len-1];
}

double stack_num_push(NumStack* stack, double num) {
    if (stack == NULL)
        return 0.0;

    if (stack->len >= stack->cap) {
        stack->data = (double*) realloc(stack->data, sizeof(double) * (stack->cap += 5));
    }
    stack->data[stack->len++] = num;
    return num;
}

double stack_num_pop(NumStack* stack) {
    if (stack == NULL)
        return -1;

    return stack->data[--stack->len];
}

void stack_num_free(NumStack* stack) {
    if (stack == NULL)
        return;
    
    free(stack->data);
    free(stack);
}