#include "s21_stack.h"

void s21_initChar(struct stackChar *stk) {
    stk->top = 0;
    stk->elem = (char *)calloc(255, sizeof(char));
}

void s21_pushChar(struct stackChar *stk, char str) {
    stk->elem[stk->top++] = str;
}

char s21_popChar(struct stackChar *stk) {
    char elem;
    if ((stk->top) > 0) {
        elem = stk->elem[--stk->top];
        // stk->elem[stk->top + 1] = 0;
        return elem;
    }
}

char s21_checkPopSym(struct stackChar *stk_check) {
    char elem;
    if ((stk_check->top) > 0) {
        elem = stk_check->elem[--stk_check->top];
        return elem;
    }
}

int s21_isEmptyChar(struct stackChar *stk) {
    if (stk->top == 0)
        return 1;
    else
        return 0;
}

void s21_initDouble(struct stackDouble *stk) {
    stk->topDouble = 0;
    stk->elemDouble = (double *)calloc(255, sizeof(double));
}

void s21_pushDouble(struct stackDouble *stk, double str) {
    stk->elemDouble[stk->topDouble++] = str;
}

double s21_popDouble(struct stackDouble *stk) {
    double elem;
    if ((stk->topDouble) > 0) {
        elem = stk->elemDouble[--stk->topDouble];
        return elem;
    } else {
        return 0;
    }
}

int s21_isEmptyDouble(struct stackDouble *stk) { return (stk->topDouble == 0); }
