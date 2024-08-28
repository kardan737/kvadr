#include <stdio.h>
#include <cassert>

#include "equation.h"
#include "int_out.h"
#include "tests.h"

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

int InputCoeff(Coeff* coef)
    {

    assert (coef != nullptr);

    printf("введи коэфы a, b, c \n");

    bool correct_input = false;
    while(correct_input == false)
        {
        int inlong = scanf("%lg %lg %lg", &coef->a, &coef->b, &coef->c);

        if ((inlong == 3) && getchar() == '\n')
            correct_input = true;

        else
            {
            int resclean = CleanBuffer();

            if (resclean == EOF)
                {
                printf("%sфайл закончился!!!!!%s", RED, RESET);
                return ERROR_EOF;
                }

            else
                printf("%sошибка ввода!!!!!\nвведите данные ещё раз%s\n", RED, RESET);
            }
        }

        return 0;
    }
