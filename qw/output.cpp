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
            printf("корней нет\n");
            break;
        case ROOTS_1:
            printf("один корень x=%lg\n", x1);
            break;
        case ROOTS_2:
            printf("два корня x1=%lg и x2=%lg\n", x1, x2);
            break;
        case ROOTS_INF:
            printf("тут корней уж очень много\n");
            break;
        default: printf("error\n");
            return ERROR_SOLVE;
        }
    return 0;
    }
