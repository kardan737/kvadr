//#include "tests.h"
//#include "solver.h"
//#include "compare.h"
#include <stdio.h>
#include <cassert>
#include <math.h>

#include "equation.h"
#include "int_out.h"
#include "tests.h"

CountRoots SolveEquation(Coeff* coef, double* x1, double* x2);

int Compare(double x, double y);

int RunTest(TestData* VData)
    {

    assert (VData != nullptr);
    assert (isfinite (VData->a));
    assert (isfinite (VData->b));
    assert (isfinite (VData->c));
    //assert (isfinite (VData->x1Exp));
    //assert (isfinite (VData->x2Exp));
    assert (isfinite (VData->nTest));
    assert (isfinite (VData->nRootsExp));

    double x1 = NAN, x2 = NAN;
    Coeff coef = {VData->a, VData->b, VData->c};
    int nRoots = SolveEquation(&coef, &x1, &x2);

    if (   !Compare(x1, VData->x1Exp)
        && !Compare(x2, VData->x2Exp)
        && !Compare(nRoots, VData->nRootsExp))
        {
        printf("%sTest %d fail a = %lg, b = %lg, c = %lg, x1Exp = %lg, x2Exp = %lg, x1 = %lg,"
               "x2 = %lg, nRootsExp = %d, nRoots = %d%s\n", RED, VData->nTest, VData->a, VData->b, VData->c, VData->x1Exp, VData->x2Exp,
                x1, x2, VData->nRootsExp, nRoots, RESET);
        }
    else
        {
        printf("%sтест %d успешено пройден%s\n", GREEN, VData->nTest, RESET);
        }

    return 0;
    }

int RunAllTests()
    {
    struct TestData VData[] = {
        {.nTest = 1, .a = 1, .b = 2, .c = -3, .x1Exp = -3,       .x2Exp = 1,       .nRootsExp =  2},  // D > 0
        {.nTest = 2, .a = 1, .b = 0, .c =  0, .x1Exp =  0,       .x2Exp = NAN,     .nRootsExp =  1},  //b =0, c = 0
        {.nTest = 3, .a = 0, .b = 3, .c =  1, .x1Exp = -1.0/3,   .x2Exp = NAN,     .nRootsExp =  1},  //a = 0
        {.nTest = 4, .a = 2, .b = 0, .c = -1, .x1Exp = -1.0/2,   .x2Exp = 1.0/2.0, .nRootsExp =  2},  //b = 0
        {.nTest = 5, .a = 1, .b = 3, .c =  0, .x1Exp = -3,       .x2Exp = 0,       .nRootsExp =  2},  //c = 0
        {.nTest = 6, .a = 0, .b = 0, .c =  1, .x1Exp = NAN,      .x2Exp = NAN,     .nRootsExp =  0},  //a = 0, b = 0
        {.nTest = 7, .a = 0, .b = 3, .c =  0, .x1Exp =  0,       .x2Exp = NAN,     .nRootsExp =  1},  //a = 0, c = 0
        {.nTest = 8, .a = 1, .b = 2, .c =  3, .x1Exp = NAN,      .x2Exp = NAN,     .nRootsExp =  0},  //D < 0
        {.nTest = 9, .a = 0, .b = 0, .c =  0, .x1Exp = NAN,      .x2Exp = NAN,     .nRootsExp = -1}}; //a = 0, b = 0, c = 0

    for (int i = 0; i < 9; i++)
        {
        RunTest(&VData[i]);
        }

    return 0;
    }
