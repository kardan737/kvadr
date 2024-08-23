//#define NDEBUG

#include <cstdlib>
#include <cassert>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string>
#include <ctype.h>

enum ErrorType
    {
    ERROR_SOLVE = 1,
    ERROR_EOF   = 1,
    };

enum CountRoots
    {
    ROOTS_INF = -1,
    ROOTS_NO  =  0,
    ROOTS_1   =  1,
    ROOTS_2   =  2,
    };

enum Options
    {
    NONE         = 0,
    VERIFICATION = 1,
    SOLUTION     = 2,
    EXIT         = 3,
    };

struct Coeff
    {
    double a, b, c;
    };

struct TestData
    {
    int nTest;
    double a, b, c;
    double x1Exp, x2Exp;
    int nRootsExp;
    };

int InputCoeff(Coeff* coef);
CountRoots SolveEquation(Coeff* coef, double* x1, double* x2);
CountRoots linear(double b, double c, double* x1);
int OutputSolve(int out_solver, double x1, double x2);

int Compare(double x, double y);
int RunAllTests();
int RunTest(TestData* VData);
int CleanBuffer();

// Doxygen docs
//
// argc argv -- аргументы командной строки
// ./solve.exe --tests
// ./solve.exe
int main()
    {
    setlocale(LC_ALL, "Rus");
    bool play_prog = true;
    while (play_prog == true)
        {
        printf("\nпроверка или решение собственного уравнения?    \n"
               "если проверка введите 1                         \n"    // tests (t)
               "если собственное введите 2                      \n"
               "если хотите закончить работу программы введите 3\n");  // solve (s)

        Options option = 0;                 // enum
        scanf("%d", &option);
        switch(option)
            {
            case VERIFICATION:
                RunAllTests();
                break;
            case SOLUTION:
                {
                Coeff coef = {NAN, NAN, NAN};
                int r = InputCoeff(&coef);

                if (r == 1)
                    return 0;

                double x1 = NAN, x2 = NAN;

                CountRoots out_solver = SolveEquation(&coef, &x1, &x2);

                OutputSolve(out_solver, x1, x2);
                break;
                }
            case EXIT:
                play_prog = false;
                break;
            case NONE:
            default: printf("ошибка выбора");
                return 1;
            }
        }
    }
int InputCoeff(Coeff* coef)
    {

    assert (coef != nullptr);

    printf("введи коэфы a, b, c \n");

    bool correct_input = false;
    while(correct_input == false)
        {
        int inlong = scanf("%lg %lg %lg", &coef->a, &coef->b, &coef->c);

        if ((inlong == 3) && getchar() == '\n')
            {
            correct_input = true;
            }
        else
            {
            int resclean = CleanBuffer();

            if (resclean == EOF)
                {
                printf("файл закончился!!!!!");
                return ERROR_EOF;
                }
            else
                {
                printf("ошибка ввода!!!!!\nвведите данные ещё раз\n");
                }
            }
        }

        return 0;
    }

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

CountRoots SolveEquation(Coeff* coef, double* x1, double* x2)
    {
    assert (coef != nullptr);
    assert (isfinite (coef->a));
    assert (isfinite (coef->b));
    assert (isfinite (coef->c));

    assert (x1 != nullptr);
    assert (x2 != nullptr);
    assert (x1 != x2);

    if (Compare(coef->a, 0))
        {
        CountRoots linear_Root = linear(coef->b, coef->c, x1);
        return linear_Root;
        }
    else
        {
        double D = coef->b * coef->b - 4 * coef->a * coef->c;
        if (D < 0)
            {
            return ROOTS_NO;
            }
        else if (Compare(D, 0))
            {
            *x1 = -coef->b / (2 * coef->a);
            return ROOTS_1;
            }
        else
            {
            double sqrt_D = sqrt(D);
            *x1 = (-coef->b - sqrt_D) / (2 * coef->a);
            *x2 = (-coef->b + sqrt_D) / (2 * coef->a);
            return ROOTS_2;
            }
        }
    }

int Compare(double x, double y)
    {
    return (fabs(y - x) < 0.0001);
    }

int RunAllTests()

    {
    struct TestData VData[] = {
        {.nTest = 1, .a = 1, .b = 2, .c = -3, .x1Exp = -3,       .x2Exp = 1,       .nRootsExp =  2},  // D > 0
        {.nTest = 2, .a = 1, .b = 0, .c =  0, .x1Exp =  0,       .x2Exp = NAN,     .nRootsExp =  1},  //b =0, c = 0
        {.nTest = 3, .a = 0, .b = 3, .c =  1, .x1Exp = -1.0/3.0, .x2Exp = NAN,     .nRootsExp =  1},  //a = 0
        {.nTest = 4, .a = 2, .b = 0, .c = -1, .x1Exp = -1.0/2.0, .x2Exp = 1.0/2.0, .nRootsExp =  2},  //b = 0
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
        printf("Test %d fail a = %lg, b = %lg, c = %lg, x1Exp = %lg, x2Exp = %lg, x1 = %lg,"
               "x2 = %lg, nRootsExp = %d, nRoots = %d", VData->nTest, VData->a, VData->b, VData->c, VData->x1Exp, VData->x2Exp,
                x1, x2, VData->nRootsExp, nRoots);
        }
    else
        {
        printf("тест %d успешено пройден\n", VData->nTest);
        }

    return 0;
    }

int CleanBuffer()
    {
    int searcher_EOF = 0;
    while ((searcher_EOF = getchar()) != '\n')
        {
        if (searcher_EOF == EOF)
            {
            return EOF;
            }
        }
    return 0;
    }

CountRoots linear(double b, double c, double* x1)
    {
    assert (x1 != nullptr);
    if (Compare(b, 0))
        {
        return (Compare(c, 0)) ? ROOTS_INF : ROOTS_NO;
        }
    else
        {
        *x1 = -c / b;
        return ROOTS_1;
        }
    }
