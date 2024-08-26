#include <math.h>
#include <cassert>
#include "equation.h"
#include "int_out.h"
#include "tests.h"

CountRoots SolveLinear(double b, double c, double* x1)  // SolveLinear
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

int Compare(double x, double y)
    {
    return (fabs(y - x) < 0.0001);              //todo   // const // погрешность // error
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
        CountRoots linear_Root = SolveLinear(coef->b, coef->c, x1);
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

