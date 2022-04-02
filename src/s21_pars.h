#ifndef SRC_S21_PARS_H_
#define SRC_S21_PARS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s21_INFINITY 1.0 / 0.0
#define s21_NAN 0.0 / 0.0

#include "s21_stack.h"

int CheckPriorOperators(char elem);
double ResultOperators(struct stackChar *stkSym, struct stackDouble *stkNum,
                     int countNum);
double StackCleanupSym(struct stackChar *stkSym, struct stackDouble *stkNum,
                     int countNum);
int CheckFunctions(struct stackChar *stkSym, char *elem, int i);
void ProcessPrior(struct stackChar *stkSym, struct stackDouble *stkNum,
                  int countNum, char *elem, int i);
int CheckRepeatedOperators(char *elem, int i);
int UnarOper(int unar, char *elem, int i);
double mainFunc(char *elem);

#endif  // SRC_S21_PARS_H_