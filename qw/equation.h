struct Coeff
    {
    double a, b, c;
    };

enum CountRoots
    {
    ROOTS_INF = -1,
    ROOTS_NO  =  0,
    ROOTS_1   =  1,
    ROOTS_2   =  2,
    };

int Compare(double x, double y);
CountRoots SolveEquation(Coeff* coef, double* x1, double* x2);
CountRoots SolveLinear(double b, double c, double* x1);
