#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_pars.h"

struct stackChar {
    char *elem;
    int top;
};

struct stackDouble {
    double *elemDouble;
    int topDouble;
};

void s21_initChar(struct stackChar *stk);
void s21_pushChar(struct stackChar *stk, char str);
char s21_popChar(struct stackChar *stk);
int s21_isEmptyChar(struct stackChar *stk);

void s21_initDouble(struct stackDouble *stk);
void s21_pushDouble(struct stackDouble *stk, double str);
double s21_popDouble(struct stackDouble *stk);
int s21_isEmptyDouble(struct stackDouble *stk);

#endif  // SRC_S21_STACK_H_