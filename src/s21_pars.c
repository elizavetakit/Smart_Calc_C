#include "s21_pars.h"

int CheckPriorOperators(char elem) {
    int priorityOper;
    if (elem == ')') {
        priorityOper = 0;
    } else if (elem == '(') {
        priorityOper = 1;
    } else if (elem == '+' || elem == '-') {
        priorityOper = 2;
    } else if (elem == '*' || elem == '/') {
        priorityOper = 3;
    } else if (elem == '%') {
        priorityOper = 4;
    } else if (elem == 'l' || elem == 'c' || elem == 's') {
        priorityOper = 5;
    } else if (elem == '^') {
        priorityOper = 6;
    } else if (elem == 'L' || elem == 'l' || elem == 'S' || elem == 'T' ||
               elem == 'C' || elem == 'A' || elem == 't' || elem == 's' ||
               elem == 'c') {
        priorityOper = 7;
    } else {
        priorityOper = -1;
    }
    return priorityOper;
}

double ResultOperators(struct stackChar *stkSym, struct stackDouble *stkNum,
                     int countNum) {
    double stackNumSecond;
    char stackSymbol = s21_popChar(stkSym);
    double stackNumFirst = s21_popDouble(stkNum);
    double result;
    if (stackSymbol == '-') {
        stackNumSecond = s21_popDouble(stkNum);
        result = stackNumSecond - stackNumFirst;
    } else if (stackSymbol == '*') {
        stackNumSecond = s21_popDouble(stkNum);
        result = stackNumSecond * stackNumFirst;
    } else if (stackSymbol == '/') {
        stackNumSecond = s21_popDouble(stkNum);
        result = stackNumSecond / stackNumFirst;
    } else if (stackSymbol == '+') {
        stackNumSecond = s21_popDouble(stkNum);
        result = stackNumFirst + stackNumSecond;
    } else if (stackSymbol == '^') {
        stackNumSecond = s21_popDouble(stkNum);
        result = pow(stackNumSecond, stackNumFirst);
    } else if (stackSymbol == '%') {
        stackNumSecond = s21_popDouble(stkNum);
        result = fmod(stackNumSecond, stackNumFirst);
    } else if (stackSymbol == 'L') {
        result = log10(stackNumFirst);
    } else if (stackSymbol == 'l') {
        result = log(stackNumFirst);
    } else if (stackSymbol == 'S') {
        result = sqrt(stackNumFirst);
    } else if (stackSymbol == 'T') {
        result = atan(stackNumFirst);
    } else if (stackSymbol == 'C') {
        result = acosl(stackNumFirst);
    } else if (stackSymbol == 'A') {
        result = asin(stackNumFirst);
    } else if (stackSymbol == 't') {
        result = tan(stackNumFirst);
    } else if (stackSymbol == 's') {
        result = sin(stackNumFirst);
    } else if (stackSymbol == 'c') {
        result = cos(stackNumFirst);
    }
    s21_pushDouble(stkNum, result);
    return result;
}

double StackCleanupSym(struct stackChar *stkSym, struct stackDouble *stkNum,
                     int countNum) {
    double result;
    while ((stkSym->top) > 0) {
        if (CheckPriorOperators(stkSym->elem[stkSym->top]) >= 1 ||
            CheckPriorOperators(stkSym->elem[stkSym->top]) <= 7) {
            if (CheckPriorOperators(stkSym->elem[stkSym->top]) == 0) {
                while (CheckPriorOperators(stkSym->elem[stkSym->top]) == 1) {
                    result = ResultOperators(stkSym, stkNum, countNum);
                }
                s21_popChar(stkSym);
            } else if (CheckPriorOperators(stkSym->elem[stkSym->top - 1]) <
                       CheckPriorOperators(stkSym->elem[stkSym->top - 2])) {
                result = ResultOperators(stkSym, stkNum, countNum);
            } else if (CheckPriorOperators(stkSym->elem[stkSym->top]) ==
                       CheckPriorOperators(stkSym->elem[stkSym->top])) {
                result = ResultOperators(stkSym, stkNum, countNum);
            }
        }
    }
    return result;
}

int CheckFunctions(struct stackChar *stkSym, char *elem, int i) {
    if (elem[i] >= 'a' && elem[i] <= 'z') {
        if (!strncmp("log(", elem + i, 3)) {
            i += 3;
            s21_pushChar(stkSym, 'L');
        } else if (!strncmp("ln(", elem + i, 2)) {
            i += 2;
            s21_pushChar(stkSym, 'l');
        } else if (!strncmp("sqrt(", elem + i, 4)) {
            i += 4;
            s21_pushChar(stkSym, 'S');
        } else if (!strncmp("atan(", elem + i, 4)) {
            i += 4;
            s21_pushChar(stkSym, 'T');
        } else if (!strncmp("acos(", elem + i, 4)) {
            i += 4;
            s21_pushChar(stkSym, 'C');
        } else if (!strncmp("asin(", elem + i, 4)) {
            i += 4;
            s21_pushChar(stkSym, 'A');
        } else if (!strncmp("tan(", elem + i, 3)) {
            i += 3;
            s21_pushChar(stkSym, 't');
        } else if (!strncmp("sin(", elem + i, 3)) {
            i += 3;
            s21_pushChar(stkSym, 's');
        } else if (!strncmp("cos(", elem + i, 3)) {
            i += 3;
            s21_pushChar(stkSym, 'c');
        }
    }
    return i;
}

void ProcessPrior(struct stackChar *stkSym, struct stackDouble *stkNum,
                  int countNum, char *elem, int i) {
    if (CheckPriorOperators(elem[i]) >= 0 ||
        CheckPriorOperators(elem[i]) <= 7) {
        if (CheckPriorOperators(elem[i]) == 0) {
            while (CheckPriorOperators(stkSym->elem[stkSym->top - 1]) != 1) {
                ResultOperators(stkSym, stkNum, countNum);
            }
            s21_popChar(stkSym);
        } else if (CheckPriorOperators(elem[i]) <
                       CheckPriorOperators(stkSym->elem[stkSym->top - 1]) &&
                   CheckPriorOperators(elem[i]) != 1) {
            ResultOperators(stkSym, stkNum, countNum);
            s21_pushChar(stkSym, elem[i]);
        } else if (CheckPriorOperators(elem[i]) ==
                       CheckPriorOperators(stkSym->elem[stkSym->top - 1]) &&
                   CheckPriorOperators(elem[i]) != 1) {
            ResultOperators(stkSym, stkNum, countNum);
            s21_pushChar(stkSym, elem[i]);
        } else {
            s21_pushChar(stkSym, elem[i]);
        }
    }
}

int CheckRepeatedOperators(char *elem, int i) {
    int flag = 0;
    if (elem[i] == '*' || elem[i] == '/' || elem[i] == '%' || elem[i] == '^') {
        if (elem[i + 1] == '*' || elem[i + 1] == '/' || elem[i + 1] == '%' ||
            elem[i + 1] == '^') {
            flag = 1;
        }
    }
    return flag;
}

int UnarOper(int unar, char *elem, int i) {
    if (elem[i] == '-' && !('0' <= elem[i - 1] && elem[i - 1] <= '9') &&
        elem[i - 1] != ')') {
        unar = 1;
    } else if (elem[i] == '+' && !('0' <= elem[i - 1] && elem[i - 1] <= '9') &&
               elem[i - 1] != ')') {
        unar = -1;
    }
    return unar;
}

double mainFunc(char *elem) {
 struct stackChar *stkSym;
    struct stackDouble *stkNum;
    double result;
    int sizeArg = 0, unar = 0, countNum = 0, flag = 0;
    sizeArg = strlen(elem);
    stkSym = (struct stackChar *)malloc(sizeof(struct stackChar));
    s21_initChar(stkSym);
    stkNum = (struct stackDouble *)malloc(sizeof(struct stackDouble));
    s21_initDouble(stkNum);
    for (int i = 0; i < sizeArg; i++) {
        flag = CheckRepeatedOperators(elem, i);
        if (flag == 1) {
            result = s21_NAN;
        }
        i = CheckFunctions(stkSym, elem, i);
        double number = 0.0;
        unar = UnarOper(unar, elem, i);
        if ('0' <= elem[i] && elem[i] <= '9') {
            while ('0' <= elem[i] && elem[i] <= '9') {
                number *= 10;
                number += elem[i] - '0';
                i++;
            }
            if (elem[i] == '.') {
                i++;
                double number_2 = 0.0, multiplayer = 1.0;
                while ('0' <= elem[i] && elem[i] <= '9') {
                    number_2 +=
                        (double)(elem[i] - '0') / powl(10.0, multiplayer);
                    multiplayer++;
                    i++;
                }
                number += number_2;
            }
            if (unar == 1) {
                number *= -1.0;
            }
            i--;
            s21_pushDouble(stkNum, number);
            countNum++;
        } else if (unar == 0 && flag == 0) {
            if (CheckPriorOperators(elem[i]) >= 0 ||
                CheckPriorOperators(elem[i]) <= 7) {
                if (CheckPriorOperators(elem[i]) == 0) {
                    while (CheckPriorOperators(stkSym->elem[stkSym->top - 1]) !=
                           1) {
                        result = ResultOperators(stkSym, stkNum, countNum);
                    }
                    s21_popChar(stkSym);
                } else if (CheckPriorOperators(elem[i]) <
                               CheckPriorOperators(
                                   stkSym->elem[stkSym->top - 1]) &&
                           CheckPriorOperators(elem[i]) != 1) {
                    result = ResultOperators(stkSym, stkNum, countNum);
                    s21_pushChar(stkSym, elem[i]);
                } else if (CheckPriorOperators(elem[i]) ==
                               CheckPriorOperators(
                                   stkSym->elem[stkSym->top - 1]) &&
                           CheckPriorOperators(elem[i]) != 1) {
                    result = ResultOperators(stkSym, stkNum, countNum);
                    s21_pushChar(stkSym, elem[i]);
                } else {
                    s21_pushChar(stkSym, elem[i]);
                }
            }
        }
    }
    unar = 0;
    result = StackCleanupSym(stkSym, stkNum, countNum);
    free(stkSym);
    free(stkNum);
    return result;
}


// void main(int argc, char *argv[]) {
//     double loh = mainFunc("1+2");
//     // struct stackChar *stkSym;
//     // struct stackDouble *stkNum;
//     // char *elem;
//     // double result;
//     // int sizeArg, unar, countNum, flag = 0;
//     // for (int i = 1; i < argc; i++) {
//     //     sizeArg = strlen(argv[i]);
//     // }
//     // elem = (char *)malloc(sizeArg * sizeof(char));
//     // for (int i = 1; i < argc; i++) {
//     //     strcpy(elem, argv[i]);
//     // }
//     // stkSym = (struct stackChar *)malloc(sizeof(struct stackChar));
//     // s21_initChar(stkSym);
//     // stkNum = (struct stackDouble *)malloc(sizeof(struct stackDouble));
//     // s21_initDouble(stkNum);
//     // for (int i = 0; i < sizeArg; i++) {
//     //     flag = CheckRepeatedOperators(elem, i);
//     //     if (flag == 1) {
//     //         result = s21_NAN;
//     //     }
//     //     i = CheckFunctions(stkSym, elem, i);
//     //     double number = 0.0;
//     //     unar = UnarOper(unar, elem, i);
//     //     if ('0' <= elem[i] && elem[i] <= '9') {
//     //         while ('0' <= elem[i] && elem[i] <= '9') {
//     //             number *= 10;
//     //             number += elem[i] - '0';
//     //             i++;
//     //         }
//     //         if (elem[i] == '.') {
//     //             i++;
//     //             double number_2 = 0.0, multiplayer = 1.0;
//     //             while ('0' <= elem[i] && elem[i] <= '9') {
//     //                 number_2 +=
//     //                     (double)(elem[i] - '0') / powl(10.0, multiplayer);
//     //                 multiplayer++;
//     //                 i++;
//     //             }
//     //             number += number_2;
//     //         }
//     //         if (unar == 1) {
//     //             number *= -1.0;
//     //         }
//     //         i--;
//     //         s21_pushDouble(stkNum, number);
//     //         countNum++;
//     //     } else if (unar == 0 && flag == 0) {
//     //         if (CheckPriorOperators(elem[i]) >= 0 ||
//     //             CheckPriorOperators(elem[i]) <= 7) {
//     //             if (CheckPriorOperators(elem[i]) == 0) {
//     //                 while (CheckPriorOperators(stkSym->elem[stkSym->top - 1]) !=
//     //                        1) {
//     //                     ResultOperators(stkSym, stkNum, countNum);
//     //                 }
//     //                 s21_popChar(stkSym);
//     //             } else if (CheckPriorOperators(elem[i]) <
//     //                            CheckPriorOperators(
//     //                                stkSym->elem[stkSym->top - 1]) &&
//     //                        CheckPriorOperators(elem[i]) != 1) {
//     //                 ResultOperators(stkSym, stkNum, countNum);
//     //                 s21_pushChar(stkSym, elem[i]);
//     //             } else if (CheckPriorOperators(elem[i]) ==
//     //                            CheckPriorOperators(
//     //                                stkSym->elem[stkSym->top - 1]) &&
//     //                        CheckPriorOperators(elem[i]) != 1) {
//     //                 ResultOperators(stkSym, stkNum, countNum);
//     //                 s21_pushChar(stkSym, elem[i]);
//     //             } else {
//     //                 s21_pushChar(stkSym, elem[i]);
//     //             }
//     //         }
//     //     }
//     // }
//     // unar = 0;
//     // StackCleanupSym(stkSym, stkNum, countNum);
//     // free(stkSym);
//     // free(stkNum);
//     // free(elem);
// }