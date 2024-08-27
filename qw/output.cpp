#include <stdio.h>
#include "equation.h"
#include "int_out.h"
#include "tests.h"

// enum      // enum
int OutputSolve(int out_solver, double x1, double x2)
    {
    switch(out_solver)
        {
        case ROOTS_NO:
            printf("%s������ ���%s\n", GREEN, RESET);
            break;
        case ROOTS_1:
            printf("%s���� ������ x=%lg%s\n", GREEN, x1, RESET);
            break;
        case ROOTS_2:
            printf("%s��� ����� x1=%lg � x2=%lg%s\n", GREEN, x1, x2, RESET);
            break;
        case ROOTS_INF:
            printf("%s��� ������ �� ����� �����%s\n", GREEN, RESET);
            break;
        default: printf("%serror%s\n", RED, RESET);
            return ERROR_SOLVE;
        }
    return 0;
    }
