//#define NDEBUG

#include <cstdlib>
#include <cassert>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#include "equation.h"
#include "int_out.h"
#include "tests.h"


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
        printf("\nпроверка или решение собственного уравнения?     \n"
               "если проверка введите test                         \n"
               "если собственное введите solve                     \n"
               "если хотите закончить работу программы введите exit\n");

        int option = 0;

        char slovo[5];
        scanf("%s", slovo);

        if (strcmp(slovo, "test") == 0)
            option = VERIFICATION;
        else if (strcmp(slovo, "solve") == 0)
            option = SOLUTION;
        else if (strcmp(slovo, "exit") == 0)
            option = EXIT;

        switch(option)
            {
            case VERIFICATION:
                RunAllTests();
                break;
            case SOLUTION:
                {
                Coeff coef = {NAN, NAN, NAN};
                int meet_EOF = InputCoeff(&coef);

                if (meet_EOF == ERROR_EOF)
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

