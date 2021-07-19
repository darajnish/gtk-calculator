
#ifndef CALKUC_STACK_H
#define CALKUC_STACK_H

typedef enum {
    EXP_OPERATOR = 'c',
    EXP_NUMBER = 'n'
} ExpValType;

typedef union {
    char opt;
    double num;
} ExpStackVal;

typedef struct {
    ExpValType type;
    ExpStackVal value;
} ExpStackCell;

typedef struct {
    int cap;
    int len;
    ExpStackCell *data;
} ExpStack;

ExpStack* stack_exp_new();
ExpStackCell* stack_exp_peek(ExpStack*);
char stack_exp_push_opt(ExpStack*, char);
double stack_exp_push_num(ExpStack*, double);
ExpStackCell* stack_exp_pop();
void stack_exp_free(ExpStack*);

typedef struct {
    int cap;
    int len;
    char *data;
} CharStack;

CharStack* stack_char_new();
char stack_char_peek(CharStack*);
char stack_char_push(CharStack*, char);
char stack_char_pop(CharStack*);
void stack_char_free(CharStack*);

typedef struct {
    int cap;
    int len;
    double *data;
} NumStack;

NumStack* stack_num_new();
double stack_num_peek(NumStack*);
double stack_num_push(NumStack*, double);
double stack_num_pop(NumStack*);
void stack_num_free(NumStack*);

#endif